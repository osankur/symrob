#ifndef CEGAREMPTINESS_HH
#define CEGAREMPTINESS_HH

#include <list>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "syntax/ta.hh"

#include <chrono>
#include "algorithms/algorithms.hh"
#include "algorithms/algorithms-options.hh"
#include "algorithms/emptiness.hh"
#include "algorithms/cegar_stats.hh"
#include "base/ptr.hh"
#include "base/stats.hh"
#include "graph/graph.hh"
#include "graph/nodescmp.hh"
#include "graph/pw.hh"
#include "graph/stats.hh"
#include "semantics/semantics.hh"
#include "semantics/zg.hh"
#include "syntax/system.hh"
#include "syntax/system_builder.hh"


namespace algorithms {

  namespace cegaremptiness {



    /*!
    \class asg_propagate_t
    \brief Propagation edge information
    \tparam NODE : type of nodes
   */
    template <class NODE>
    class asg_propagate_t {
    public:
      /*!
      \brief Constructor
      \param to : node to update
      \param vedge : vedge to propagate along
      \pre vedge is an outgoing edge of node "to" (propagation goes backward
      vedge to update node "to") (not checked)
      \post this stores a pointer to node "to" and a shared pointer to vedge
     */
      asg_propagate_t(NODE * to, syntax::vedge_t const & vedge)
        : to(to), vedge(vedge)
      {}

      /*!
      \brief Destructor
    */
      // IMPLEMENTATION NOTE: do not delete node "to"
      ~asg_propagate_t() = default;

      /*!
      \brief Equality predicate
      \param p : propagation edge to check
      \return True if this is equal to p, false otherwise
     */
      bool operator == (asg_propagate_t<NODE> const & p) const {
        return ( (to == p.to) &&
                 (vedge == p.vedge) );
      }

      NODE * to;              /*!< Node to update */
      syntax::vedge_t vedge;  /*!< Propagate backward along vedge */
    };



    /*!
    \class asg_node_t
    \brief Node type that stores the relations needed by the ASG (see asg_t
    below)
    \param NODE : type of nodes, should derive from asg_node_t
  */
    template <class NODE>
    class asg_node_t {

      /* static_assert( std::is_base_of( asg_node_t<NODE>, NODE ) ); */

    public:
      /*!
      \brief Constructor
      \post The node is uncovered, has no parent and does not propagate to any
      node
    */
      asg_node_t() : covering_node(nullptr),
        has_parent(false),
        has_propagator(false){
      }

      /*!
      \brief Destructor
    */
      // IMPLEMENTATION NOTE: do not delete any node!
      virtual ~asg_node_t() = default;

      /*!
      \brief Covered predicate
      \return True if the node is covered, false otherwise
    */
      bool covered() const {
        return ( covering_node != nullptr );
      }



      /*!
      \brief Accessor
      \return edge to parent node if any
      \pre The node has a parent node
      \throw std::logic_error: if the node has no parent edge
     */
      asg_propagate_t<NODE> const & parent() const {
        if ( ! has_parent )
          throw std::logic_error("*** asg_node_t::parent: node does not have "
                                 "a parent node");
        assert( ! propagate.empty() ); // must contain the parent edge
        return ( propagate.front() );
      }

      bool is_ancestor(NODE * n) const {
        if (n == this)
          return true;
        if ( ! n->has_parent )
          return false;
        else {
            return is_ancestor(n->parent().to);
          }
      }


      /*!
      \brief Checks if an edge is to parent node
      \return True if the edge points to parent node, false otherwise
     */
      bool to_parent(asg_propagate_t<NODE> const & p) const {
        return ( has_parent && ( p == propagate.front() ) );
      }


      /*!< Covering node (nullptr if the node is not covered) */
      NODE * covering_node;
      /*!< Covered nodes (empty if no covered node) */
      std::list< NODE * > covered_nodes;

      std::vector< NODE * > children;
      /*!< Nodes to update when node is updated. FIRST ONE IS TO PARENT NODE IF
      has_parent */
      std::list< asg_propagate_t<NODE> > propagate;
      /*!< Whether the node has a parent node */
      bool has_parent;
      /*!< Whether some node propagates to this node */
      bool has_propagator;

    };



    /*!
    \class asg_t
    \brief Adaptive Simulation Graph (ASG)

    Adaptive Simulation Graph is used by emptiness algorithms that computes
    clock bounds on-the-fly (see Herbreteau et al., CAV 2013). The graph is
    used to compute clock bounds for dynamic covering of nodes. It maintains
    two relations: a propagation relation (~>) and a covering relation (<<).

    The propagation relation ~> is used to propagate the dynamic clock bounds
    that are discovered while exploring the zone graph. Hence, n ~> n' means
    that the bounds in node n' need to be updated whenever the bounds in n
    are updated. When, n << n', n is dynamically covered by n'. This means
    that the zone in node n is included in the aLU-abstraction of the zone
    in n' with respect to the dynamic bounds in n'. We say that n is a
    tentative node.

    The following invariants need to be maintained on the ASG for
    completeness and termination of the algorithms:

    (G1) there is a node n = (q0,Z0,LU) that corresponds to the initial
    node of the zone graph

    (G2) if a node n = (q,Z,LU) is not tentative, then for every transition
    (q,Z) -> (q',Z') in the zone graph, there is a node n' = (q',Z'',L'U')
    such that n' ~> n (n' propagates backward to n) and Z' is included in
    Z''. That is, the node n' is (q',Z',L'U') itself or a bigger reachable
    node.

    (G3) if a node n = (q,Z,LU) is tentative, then there should be a
    non-tentative node n' = (q',Z',L'U') such that q = q' and Z is included
    in aL'U'(Z'). Then, we have n << n', in other words is n is dynamically
    covered by n' and n' is the covering node of n.

    The two relations ~> and << are stored directly in the nodes (see
    asg_node_t above). More precisely:
    - the covering relation n << n' is stored in both n (covering_node) and
    in n' (covered_nodes).
    - the propagation relation n ~> n' is only stored in node n.
    Notice that node n has to propagate to all nodes n' such that either
    n ~> n' or n' << n.

    \tparam NODE : type of node, should inherit from asg_node_t
   */
    template <class NODE>
    class asg_t {

      /* static_assert( std::is_base_of( asg_node_t<NODE>, NODE ) ); */

    public:
      /*!
      \brief Adds a covering edge to the ASG
      \param node : the covered node
      \param covering_node : the covering node
      \pre node is uncovered (checked by assertion)
      \post node << covering_node has been added to the ASG
     */
      void cover(NODE * node, NODE * covering_node) {
        assert(node != nullptr);
        assert(covering_node != nullptr);
        assert(node->covering_node == nullptr);

        node->covering_node = covering_node;
        covering_node->covered_nodes.push_back(node);
        for (NODE* covered: node->covered_nodes) {
            covering_node->covered_nodes.push_back(covered);
            covered->covering_node = covering_node;
          }
        node->covered_nodes.clear();
        assert(node->covered_nodes.empty());
      }


      /*!
      \brief Removes a covering edge from the ASG
      \param node : the node to uncover
      \pre node is covered (checked by assertion)
      \post node << node->covering_node has been removed from the ASG
      \warning iterators on node->covered_nodes are invalidated by this
      function
     */
      void uncover(NODE * node) {
        assert( node != nullptr );
        assert( node->covering_node != nullptr );

        node->covering_node->covered_nodes.remove(node);
        node->covering_node = nullptr;
      }

      /*!
      \brief Adds a child-to-parent edge to the ASG
      \param child : child node
      \param parent : parent node
      \param vedge : propagation vedge
      \pre child node does not have any parent edge yet
      \post the edge: child -- vedge --> parent has been added to the ASG
      \throw std::logic_error: when node child already has a parent edge
     */
      void add_parent_edge(NODE * child, NODE * parent,
                           syntax::vedge_t const & vedge) {
        assert( child != nullptr );
        assert( parent != nullptr );

        if ( child->has_parent )
          throw std::logic_error("*** asg_t::add_parent_edge: child node "
                                 "already has a parent node.");

        // IMPLEMENTATION NOTE: parent edge must be first in propagation list
        child->propagate.push_front( asg_propagate_t<NODE>(parent, vedge) );
        child->has_parent = true;

        parent->has_propagator = true;
      }


      /*!
      \brief Replaces a node by another one in the ASG
      \param node : node to remove
      \param substitute : replacement node
      \param dynamic_uncovered_nodes : vector of nodes
      \pre the zone in substitute contains the zone in node and the bounds in
      substitute are smaller than the bounds in node. node and substitute
      are not the same node (checked by assertion). The nodes that should
      propagate to subtitute are computed by the algorithm
      \post the ASG has been updated as follows:
      . all propagation edge node ~> n have been replaced by substitute ~> n
      . EDGES n ~> node HAVE NOT BEEN TRANSFORMED INTO n ~> substitute AS WE
      CANNOT ACCESS THEM, hence the requirement that the propagations to
      substitute are determined by the algorithm. Notice that this is
      convenient since the bounds in substitute are expected to be better
      than the bounds in node (bigger zone).
      . if node was dynamically covered, it has been uncovered
      . all the nodes dynamically covered by node have been uncovered and
      added to dynamic_uncovered_nodes
      \warning Iterators on node->covered_nodes are invalidated
     */
      void replace(NODE * node, NODE * substitute,
                   std::vector<NODE *> & dynamic_uncovered_nodes) {
        assert( node != nullptr );
        assert( substitute != nullptr );
        assert( node != substitute );
        assert( (* node->zone()) <= (* substitute->zone()) );

        // IMPLEMENTATION NOTE: no need to update has_propagator flags
        // IMPLEMENTATION NOTE: thanks to splice, parent node of substitute
        // is still the first one in its propagation list
        substitute->propagate.splice( substitute->propagate.end(),
                                      node->propagate );
        // IMPLEMENTATION NOTE: node->propagate->clear() is useless thanks
        // to splice() above

        if ( node->covered() )
          uncover(node);

        for (NODE * n : node->covered_nodes) {
            // IMPLEMENTATION NOTE: uncover() cannot be used here as it would
            // invalidate the iterator on node->covered_nodes
            n->covering_node = nullptr;
            // IMPLEMENTATION NOTE: one could think of covering n by substitute.
            // However, if substitute is unexpanded, this would break the
            // invariant that unexpanded node cannot dynamically cover any node
            dynamic_uncovered_nodes.push_back(n);
          }
        node->covered_nodes.clear();
      }
    };

    /*!
    \class node_t
    \brief Nodes for on-the-fly bounds generic algorithm. Notice that clock
    bounds are not stored here: they are added by specialized algorithms
    \tparam NODE : type of nodes defined in specialized algorithms, should
    inherit from node_t
  */
    template <class NODE>
    class node_t : public graph::pw_node_t,
        public graph::state_node_t<semantics::zg::state_t>,
        public asg_node_t<NODE> {
    public:
      /*!
      \brief Constructor
      \post The node is active and has not been expanded
    */
      node_t() : active(true), expanded(false), in_past(false) {
      }


      /*!
      \brief Destructor
    */
      virtual ~node_t() = default;


      /*!
      \brief Deactivate the node. In some situation, a node should be
      deleted but some unknown nodes still propagate to it. So it is kept as
      an inactive node
      \post The memory pointed to by the node has been released but the node
      itself has not been deleted
    */
      void deactivate() {
        if (this->semantics::zg::state_t::_zone != nullptr)
          delete this->semantics::zg::state_t::_zone;
        this->semantics::zg::state_t::_zone = nullptr;
        this->covering_node = nullptr;
        this->covered_nodes.clear();
        this->propagate.clear();
        this->has_parent = false;
        active = false;
      }
      //virtual static void init(syntax::model_t* model) = 0;
      //virtual void init_abstraction() = 0;
      //virtual bool abstract() = 0;

      //virtual symbolic::zone_t* abstract_zone() = 0;
      //virtual void add_interpolant( raw_t* cc,
      //                        syntax::vedge_t const & vedge) = 0;


      /*!
      \brief Output the node
      \param os : output stream
      \post The search number and underlying state have been output to os
    */
      virtual void output(std::ostream & os) const {
        this->graph::state_node_t<semantics::zg::state_t>::output(os);
      }


      /*!< Active flag */
      bool active;
      /*!< Expanded flag */
      bool expanded;

      bool in_past;
    };




    /*!
    \brief Predicate over nodes that ensures acyclicity of covering
    relations

    The algorithm implements dynamic covering of nodes. To that purpose, a
    covering relation is maintained. This relation must be acyclic for
    completeness of the algorithm. This predicate ensures that only the
    nodes that have not been expanded can be covered, and only the nodes
    that have been expanded can be covering. Since no node can be both
    covered and covering, the relation is acyclic (it further checks that
    a node cannot be covered by itself).

    \tparam NODE : type of nodes. It should derive from node_t.
    \param n1 : first node to compare
    \param n2 : second node to compare
    \return True if adding (n1, n2) to the covering relation would still make
    it acyclic, false otherwise
  */
    template <class NODE>
    inline bool nodes_acyclic_cover(NODE const * n1, NODE const * n2) {
      return ( graph::nodes_distinct(n1, n2) &&
               (! n1->expanded) &&
               (n2->expanded) );
    }





    template <class NODE>
    class algorithm_t
        : public algorithms::emptiness::algorithm_t,
        public algorithms::zg_algorithm_t,
        public algorithms::graph_output_owner_t {

      /* static_assert( NODE derives from node_t ) */

    public:
      /*!
      \brief Constructor
      \param system_builder : model builder used to build the zone graph
      \param options : algorithm settings
      \param cover : dynamic cover predicate
      \throw std::logic_error : when the search strategy in options is not
      supported
      \throw std::logic_error : when the propagation strategy in options is
      not supported
    */
      algorithm_t(syntax::system_builder_t & system_builder,
                  algorithms::options_t const & options,
                  graph::nodes_binpred_t<NODE> const & cover)
        : algorithms::zg_algorithm_t(system_builder,
                                     _labels,
                                     options.model_flags,
                                     options.semantics_flags),
          algorithms::graph_output_owner_t(* options.os, options.go_flags),
          _algorithm_options(options)
      {
        // Dynamic covering predicate
        //_dyn_cover = [cover] (NODE const * n1, NODE const * n2) {
        //        return nodes_acyclic_cover(n1, n2) && cover(n1, n2);
        //      };

        // Gets PW cover predicate
        _pw_cover = graph::nodes_binpred<NODE>(options.pw_leq_flags,
                                               _model->system_bounds());

        // Defines the type of PW list
        graph::pw_flags_t pw_flags;
        switch (options.search_strategy_flags) {
          case algorithms::options_t::SS_BFS:
            pw_flags = graph::PW_FIFO;
            break;
          case algorithms::options_t::SS_DFS:
            pw_flags = graph::PW_LIFO;
            break;
          case algorithms::options_t::SS_OFS:
            pw_flags = graph::PW_INC;  // oldest = smallest id
            break;
          case algorithms::options_t::SS_YFS:
            pw_flags = graph::PW_DEC;  // youngest = biggest id
            break;
          case algorithms::options_t::SS_BZBFS:
            pw_flags = graph::PW_BZFIFO;
            break;
          case algorithms::options_t::SS_BZDFS:
            pw_flags = graph::PW_BZLIFO;
            break;
          default:
            throw std::logic_error
                ("*** algorithms::otfboundsemptiness::algorithm_t: "
                 "unsupported search strategy");
          }

        // Builds the PW list
        graph::pw_factory_t & f_pw = graph::pw_factory_t::instance();
        _pw = f_pw.new_pw<NODE>(_pw_cover, graph::nodes_lt_id<NODE>, pw_flags);
        assert( _pw != nullptr );


      }
      //    symbolic::zone_t * concrete(NODE& node) {
      //      if (node.has_parent) return _zg->(*(node.parent().to), node.parent().vedge, node);
      //      else return _zg->concrete_initial(node);
      //    }


      /*!
      \brief Destructor
    */
      virtual ~algorithm_t() {
        delete _pw;
      }
    protected:
      /*!
      \brief Emptiness check
      \return True if no accepting state is reachable, false otherwise
    */
      virtual bool  emptiness_check() {
        NODE * current = nullptr,           // Node under consideration
            * next = nullptr,                 // Next node to consider
            * covering_node = nullptr;        // Covering node
        std::vector<NODE *> covered_nodes;  // Covered nodes
        std::vector<NODE *> succs;          // Successor nodes
        bool empty = true;                  // Verdict
        unsigned snumber = 0;               // Search number
        int FileCounter =0;
        double avg_node_creation=0;
        long max_node_creation=0;
        // Initialization
        this->_go->start();
        this->_go->title("Reachability tree");
        _stats.initialize();
        std::function<void(NODE *)> f = &NODE::abstract;
        // Insert initial node
        current = new NODE();
        assert(current != nullptr);

        NODE::init(_model);
        _zg->initial(*current);
        current->init_abstraction();
        if (current->status() == graph::STATE_STATUS_OK)
          {
            _pw->insert_function(current, covering_node, covered_nodes,f);
            assert( covering_node == nullptr );  // PW list empty before insert
            assert( covered_nodes.empty() );

            ++ _stats.nodes_count;
            current->id = _stats.nodes_count;
          } else {
            delete current;
          }

        // Explore reachable state-space
        while ( ! _pw->wempty() ) {
            // Pick next node
            current = _pw->wnext();
            assert(current->covering_node==nullptr);

            if (current->snumber == 0) { // Not visited yet
                ++ snumber;
                current->snumber = snumber;
                this->_go->node(*current);
              }
            dump();

            ++ _stats.visited_nodes_count;
            // refine if current node is accepting
            if ( current->accepting(this->accepting_labels()) ) {

                if (refine(*current))
                  {
                    empty = false;
                    break;
                  }
              }
            else {
                on_expand_node(*current);
                current->in_past = true;
                for (auto r = _zg->outgoing_edges(*current); ! r.at_end();
                     r.advance())
                  {

                    syntax::vedge_t const & vedge = r.current();

                    next = new NODE();
                    assert(next != nullptr);
                    //assert(next->expanded = false);
                    _zg->next(*current, vedge, *next);
                    // Ignore nodes obtained from edges disabled wrt vloc or layout
                    if ( (next->status() != graph::STATE_STATUS_OK) ) {
                        delete next;
                        continue;
                      }

                    next->init_abstraction();
                    // Updates ASG and stores successor node
                    ++ _stats.nodes_count;
                    next->id = _stats.nodes_count;
                    this->_go->edge(*current, *next);

                    _asg.add_parent_edge(next, current, vedge);

                    succs.push_back(next);
                  }

                // Pushes all successor nodes to PW list, updates ASG wrt nodes that
                // are statically covered
                // IMPLEMENTATION NOTE: this is done after all successors have been
                // computed to avoid deactivating nodes needed for successor
                // computation (i.e. node current)
                current->children.swap(succs);

                insert_nodes_pw(current->children);

                succs.clear();

              }
            //printFile(FileCounter);
          }
        // Check
        if (_algorithm_options.check_flag)
          check();
        // Output stats, etc.
        // NODE::print_stats();
        _stats.avg_refine = _stats.avg_refine / _stats.refinement_count;
        stats(_algorithm_options.stats_level);
        dump();

        // Done
        this->_go->end();

        _pw->clear_and_delete();

        for (NODE * n : _inactive_nodes) {
            delete n;
          }
        _inactive_nodes.clear();
        //printFile(FileCounter);

        return empty;
      }


      /*!
      \brief Inserts nodes in the passed-waiting list, updating ASG wrt
      static covering
      \param nodes : nodes to insert
      \pre nodes are all active and not in the passed-waiting list yet
      (checked by assertion)
      \post for each node n from nodes:
      . if n is statically uncovered, it has been added in the passed
      waiting list. All the nodes statically covered by n have been removed
      from the passed waiting list, replaced by n in the ASG
      . if n is statically covered, it has not been inserted in the passed
      waiting list, n has been replaced by its covering node in the ASG, n
      has been deleted and propagation has been scheduled for invariants
     */
      void insert_nodes_pw(std::vector<NODE *> & nodes) {
        std::function<void(NODE *)> f = &NODE::abstract;

        for (NODE * node : nodes) {
            std::vector<NODE *> covered_nodes;
            NODE * covering_node;

            assert(  node->status() != graph::STATE_STATUS_EMPTY_ZONE );
            assert( ! _pw->pfind(node) );
            assert( ! _pw->wfind(node) );

            covered_nodes.clear();
            if ( _pw->insert_function(node, covering_node, covered_nodes, f) ) {
                assert( covering_node == nullptr );
                for (NODE * n : covered_nodes) {
                    // display deactivated nodes that have not been displayed yet
                    if (n->snumber == 0)
                      this->_go->node(*n);
                    _asg.cover(n,node);
                  }
              }
            else {
                assert( covered_nodes.empty() );

                // node has not been displayed yet and it will be destroyed
                this->_go->node(*node);

                _asg.cover(node,covering_node);

              }
          }


      }

      /**
       * @brief insert_nodes_covered For each node in nodes, if node is in past,
       *  then add it to passed only (if not covered), otherwise add it to both wait and passed (if not covered).
       *  These are nodes that were previously covered, so this function is used to add
       *  them back.
       * @param nodes
       */
      void reinsert_covered_nodes(std::vector<NODE *> & nodes) {
        std::function<bool(NODE *,NODE *)> compare = [this] (NODE * n1,NODE * n2) {std::cout<<"compared";
                                                                                   return (n1->in_past||!n2->in_past);};
        std::sort (nodes.begin(),nodes.end(), compare);std::cout<<"sorted \n";
        std::function<void(NODE *)> f = &NODE::abstract;

        //std::function<void(NODE *)> f = [this] (NODE * n) {_czg->update( *n);};

        for (NODE * node : nodes) {
            assert(  node->status() != graph::STATE_STATUS_EMPTY_ZONE );
            //_zg->next(node->parent.to);
            assert( node->active );
            std::vector<NODE *> covered_nodes;
            NODE * covering_node;
            if (node->in_past) {
                if ( _pw->insert_passed_function(node, covering_node, covered_nodes, f) ) {
                    assert( covering_node == nullptr );

                    for (NODE * n : covered_nodes) {
                        // display deactivated nodes that have not been displayed yet
                        if (n->snumber == 0)
                          this->_go->node(*n);
                        _asg.cover(n,node);
                      }
                  }
                else {
                    assert( covered_nodes.empty() );
                    // node has not been displayed yet and it will be destroyed
                    this->_go->node(*node);
                    _asg.cover(node,covering_node);
                  }
              }
            else {
                if ( _pw->insert_function(node, covering_node, covered_nodes, f) ) {
                    assert( covering_node == nullptr );

                    for (NODE * n : covered_nodes) {
                        // display deactivated nodes that have not been displayed yet
                        if (n->snumber == 0)
                          this->_go->node(*n);
                        _asg.cover(n,node);
                      }
                  }
                else {
                    assert( covered_nodes.empty() );

                    // node has not been displayed yet and it will be destroyed
                    this->_go->node(*node);

                    _asg.cover(node,covering_node);
                  }}
          }


      }



      /*!
      \brief Updates the bounds in a node when it is expanded (immediately
      before its outgoing edges are expanded)
      \param node : node to consider
      \param pdata : propagation data
      \pre node has status graph::STATE_STATUS_OK
      \post Flag expanded in node has been set to true
     */
      virtual void on_expand_node(NODE & node) {
        node.expanded = true;
      }
      bool refine(NODE & n) {
        std::vector<NODE*> uncovered;
        std::vector<NODE*> updated;
        bool result = true;
        bool empty = false;
        unsigned length = 0;
        syntax::vedge_t dummy_transition;

        std::size_t dim = n.zone()->dim();
        raw_t * copy = new raw_t[dim * dim];
        n.zone()->to_dbm(copy);


        refine_rec(n, dummy_transition, copy, result, uncovered, updated, length, empty);
        if (!result) {
            _stats.refinement_count ++;
            _stats.max_refine = std::max(_stats.max_refine, length);
            _stats.avg_refine = _stats.avg_refine + length;

            NODE * to_cut = where_cut(updated, uncovered);
            // We restart exploration from to_cut
            to_cut->in_past = false;
            //uncovered.push_back(to_cut);

            cut(to_cut, uncovered);
            _stats.uncoverings_count = _stats.uncoverings_count + uncovered.size();

            reinsert_covered_nodes(uncovered);

            uncovered.clear();
          }
        delete copy;
        return result;
      }

      /**
       * @brief cut
       * @param n
       * @param uncovered
       * @param erase This is typically set to false at the first call and to true
       * in subsequent calls so that the root node is kept but all subtrees are destroyed
       */
      void cut (NODE* n, std::vector<NODE *> &uncovered, bool erase=false) {
        for (NODE * node : n->children) {
            cut(node, uncovered, true);
          }
        remove_node(n, uncovered, (erase||n->zone()->empty()));
        if (erase) {
            delete n;
            _stats.deleted_count ++;
          }
        else {
            n->children.clear();
            if (n->zone()->empty()) //The node we cut is empty, we want to delete it too
              {
                auto it = std::find(n->parent().to->children.begin(), n->parent().to->children.end(), n);
                if (it != n->parent().to->children.end())
                  {
                    n->parent().to->children.erase(it);
                  }

                delete n;
                _stats.deleted_count ++;
              }

          }
      }

      /**
       * @brief refine_rec
       * @param n Currently visited node on the trace
       * @param transition Edge that leaves node n in the trace (and a dummy edge for the last node of the trace i.e. for the first call to this func)
       * @param conc_pred Concrete predecessor computed upto the current point from the last node of the trace
       * @param genuine whether the cex is genuine; must be set to false initially.
       * @param uncovered container to which all uncovered nodes will be added
       * @param updated container to which the subtrace that was refined will be put
       * @param length ???
       * @param empty set to true if some node becomes empty on the trace after refinement
       * @pre updated is empty
       *
       * Given node n, compute concrete predecessors upwards from n, at each step,
       * intersecting the current predecessor (param. conc_pred) with the abstract zone of the current node,
       * until either this predecessor becomes empty (spurious cex), or a non-empty initial state is reached which confirms the cex.
       * The param result is set to false whenever conc_pred becomes empty (which shows the cex is spurious)
       * Once the cex is found to be spurious, we go back down (by returning recursive calls) and update the nodes
       * by recomputing the successors with the current abstraction.
       * The param empty is also set to true whenever one of these updated nodes is empty.
       *
       * Let the following be the path from init to node n in the zone graph.
       * A_1 -> A_2 -> .... -> A_n
       *
       * Note that some A_i may not be larger than abs(post(A_{i-1})) due to previous refinements
       *
       * We compute C_n=A_n, and C_i = Pre(C_{i+1}) /\ A_i.
       * Let i0 be the smallest index such that C_{i_0} != empty.
       * We apply the following for i>=i0:
       *
       * 1) If i = 1.
       *  1a) if C_1 /\ abs(conc_init) = empty, we just update A_1 to abs(conc_init)
       *  1b) otherwise, we check if C_1 /\ conc_init != empty, in which case the cex is confirmed
       *  1c)                     otherwise we refine with interpolant(C_1, conc_init)
       * 2) If i>1.
       *  2a) If Some A_{j} with j < i just became empty, then we set A_i = empty as well
       *  2b) Otherwise let A_i = post(A_{i-1}).
       *    2ba) If abs(A_i) /\ C_i = empty, then nothing to do
       *    2bb) Otherwise, we refine abs by interpolant(A_i, C_i). And set A_i = abs'(A_i) with this new abstraction.
       *
       * When this returns, updated contains the subtrace that starts from the
       * first node of the trace that was refined, until either the end or the
       * first node that was empty.
       *
       */


      void refine_rec (NODE & n, const syntax::vedge_t & transition, raw_t * conc_pred, bool &genuine, std::vector<NODE *> &uncovered, std::vector<NODE *> &updated, unsigned &length, bool& empty ){
        std::size_t dim = n.zone()->dim();
        raw_t * tmp = new raw_t[dim * dim];
        n.zone()->to_dbm(tmp);
        // conc_pred := conc_pred /\ n.zone()
        dbm_intersection(conc_pred, tmp, dim);
        if (dbm_isEmpty(conc_pred, dim))
          {
            // We stop the recursive call here
            // We need to refine starting from the successor of this node
            genuine=false;
          } else {
            if (n.has_parent)
              { //Not root
                asg_propagate_t<NODE> parent = n.parent();

                // tmp := pre(tmp, parent.vedge)
                dbm_copy(tmp, conc_pred, dim);
                _zg->pre(*(parent.to), tmp, parent.vedge, n);
                length++;
                refine_rec(*(parent.to), parent.vedge, tmp, genuine, uncovered, updated, length, empty);
                if (empty)
                  { // one of the parents has been set to empty
                    // Set the current node to empty zone
                    symbolic::zone_t * empty_zone = n._zone->copy();
                    empty_zone->set_empty();
                    delete n._zone;
                    n._zone = empty_zone;
                    remove_node(&n, uncovered, empty);

                  }
                else if (!genuine)
                  { //there has been a refinement

                    _zg->next( *(parent.to), parent.vedge, n);


                    if (n.zone()->empty())
                      {
                        empty = true;
                      }
                    else
                      {
                        symbolic::zone_t* abstracted = n.abstract_zone();

                        raw_t * tmp2 = new raw_t[dim * dim];
                        dbm_copy(tmp2,conc_pred,dim);
                        abstracted->to_dbm(tmp);
                        dbm_intersection(conc_pred, tmp, dim);

                        if (dbm_isEmpty(conc_pred, dim))
                          {
                            // Conc predecessor is already separated from (the recomputed) current node
                            // No need to add interpolant
                            delete n.zone();
                            n._zone = abstracted;
                          }
                        else
                          {
                            delete abstracted;

                            n.add_interpolant(conc_pred, transition);

                            n.abstract();
                            n._zone->to_dbm(tmp);
                            assert(dbm_intersection(tmp,tmp2,dim)==FALSE);
                          }

                      }
                    remove_node(&n, uncovered, empty);
                    updated.push_back(&n);
                  }
              }
            else
              {
                _zg->initial(n);
                symbolic::zone_t* abstract_init = n.abstract_zone();
                abstract_init->to_dbm(tmp);
                // Reintersect conc_pred with the updated abstract init state
                dbm_intersection(conc_pred, tmp, dim);
                n.zone()->to_dbm(tmp); // tmp is now the conc_init below
                if (dbm_isEmpty(conc_pred, dim))
                  {
                    delete n.zone();
                    n._zone = abstract_init;

                    remove_node(&n, uncovered, empty);
                    updated.push_back(&n);
                    genuine = false;
                  }
                else
                  {
                    // Does conc_pred intersect conc_init?
                    dbm_intersection(tmp, conc_pred, dim);

                    if (!dbm_isEmpty(tmp, dim))
                      {
                        // genuine counterexample
                        genuine = true;
                      }
                    else
                      {
                        genuine=false;
                        // separating conc_init from conc_pred
                        n.add_interpolant(conc_pred,transition);
                        remove_node(&n,uncovered, empty);
                        updated.push_back(&n);
                      }
                  }
              }
          }

        delete tmp;
      }

      /**
       * @brief update_cover Remove n from the asg tree, and put all covered nodes in uncovered
       * @param n
       * @param uncovered
       * @param erase
       * @return true if node is kept, false if removed
       *
       */
//      bool remove_node (NODE * n, std::vector<NODE *> &uncovered, bool erase) {
//        if (n->covered() && !erase) {

//            return true;
//          }
//        else{
//            std::list<NODE *> new_cover;
//            for (NODE * node : n->covered_nodes) {
//                // if ((erase || !_pw_cover(node,n))){
//                node->covering_node = nullptr;
//                auto it = std::find(uncovered.begin(), uncovered.end(), node);
//                if (it == uncovered.end()){
//                    uncovered.push_back(node);
//                  }
//                //  }
//                //else {
//                //    new_cover.push_back(node);
//                //  }
//              }
//            n->covered_nodes = new_cover;

//            bool in_pw = _pw->pfind(n);

//            bool in_w = _pw->wfind(n);
//            size_t size_before = _pw->psize();
//            _pw->remove(n);

//            size_t size_after = _pw->psize();
//            bool in_pw_after = _pw->pfind(n);
//            if (erase) {
//                if (n->covered()) {
//                    // We uncover n so that no one points to it anymore
//                    _asg.uncover(n);
//                  }

//                // If n was added to uncovered in previous calls, remove it
//                auto it = std::find(uncovered.begin(), uncovered.end(), n);
//                if (it != uncovered.end()){
//                    uncovered.erase(it);
//                  }
//              }

//            return false;
//          }
//      }
      bool remove_node (NODE * n, std::vector<NODE *> &uncovered, bool erase) {

        if (!n->covered()) {
            std::list<NODE *> new_cover;
            for (NODE * node : n->covered_nodes) {
                // if ((erase || !_pw_cover(node,n))){
                assert(!this->_pw->pfind(node));
                node->covering_node = nullptr;
                auto it = std::find(uncovered.begin(), uncovered.end(), node);
                if (it == uncovered.end()){
                    uncovered.push_back(node);
                  }
                //  }
                //else {
                //    new_cover.push_back(node);
                //  }
              }
            n->covered_nodes = new_cover;




            _pw->remove(n);
            if (erase) {
                // If n was added to uncovered in previous calls, remove it
                auto it = std::find(uncovered.begin(), uncovered.end(), n);
                if (it != uncovered.end()){
                    uncovered.erase(it);
                  }
              }
            return false;
          }

        else {
            if (erase) {
                // We uncover n so that no one points to it anymore
                _asg.uncover(n);

                // If n was added to uncovered in previous calls, remove it
                auto it = std::find(uncovered.begin(), uncovered.end(), n);
                if (it != uncovered.end()){
                    uncovered.erase(it);
                  }
                return false;
              }
            else {
                return true;
              }
          }
      }
      bool test_final() {
        unsigned total_nodes =0;
        for (typename graph::pw_t<NODE>::piterator it= _pw->pbegin(); it !=_pw->pend(); it.operator ++()) {
            const NODE* current = *it;
            total_nodes++;
            assert(!current->covered());
            if (current->has_parent) {
                NODE* parent = (current->parent()).to;
                NODE* test = new NODE();
                _zg->next( *(parent), current->parent().vedge, *test);
                assert(_pw_cover(test,current));
                delete test;
              }
            for (NODE * node: (current)->covered_nodes) {
                total_nodes++;
                assert(node->covered_nodes.empty());
                if (node->has_parent) {
                    NODE* parent = (node->parent()).to;
                    NODE* test = new NODE();
                    _zg->next( *(parent), node->parent().vedge, *test);
                    assert(_pw_cover(test,node));
                    delete test;
                  }

              }
          }
        assert(_stats.nodes_count== total_nodes+_stats.deleted_count);
      }


      void print_search_tree(std::ostream& ofs) {
        ofs<<"digraph G { \n";
        for (typename graph::pw_t<NODE>::piterator it= _pw->pbegin(); it !=_pw->pend(); it.operator ++()) {
            const NODE* current = *it;
            ofs<<"ptr"<<current;
            //if (_pw->wfind(current)) {ofs<<" [style =bold  label=\"";}
            //else {
            ofs<<" [style =solid  label=\"";
            //         }

            (current)->vloc()->output(ofs);
            (current)->zone()->output(ofs);
            ofs<<"\"]; \n";
            if (current->has_parent) {
                NODE* parent = (current->parent()).to;
                ofs << "ptr"<<parent <<" -> " <<"ptr"<<current<< " [style = solid];\n";
              }
            for (NODE * node: (current)->covered_nodes) {
                ofs<<"ptr"<<node<<" [style = dotted  label=\"";

                node->vloc()->output(ofs);
                node->zone()->output(ofs);
                ofs<<"\"]; \n";
                //ofs << "ptr"<<node <<" -> " <<"ptr"<<current<< " [style = dotted];\n";

                NODE * covered = node;
                while(covered->has_parent&& covered->covered()) {
                    NODE* parent = covered->parent().to;
                    ofs << "ptr"<<parent <<" -> " <<"ptr"<<covered<< " [style = solid];\n";
                    covered = parent;
                    if (covered->covered()) {
                        ofs<<"ptr"<<covered<<" [style = dotted  label=\"";

                        covered->vloc()->output(ofs);
                        covered->zone()->output(ofs);
                        ofs<<"\"]; \n";
                        //if (covered->covering_node->covered()) {
                        //    ofs << "ptr"<<covered <<" -> " <<"ptr"<<covered->covering_node<< " [style = dotted];\n";}

                        //}
                      }
                  }
              }
          }
        ofs<<"}";
      }

      void printFile(int& i) {
        std::string FileName;
        FileName = "output/" + std::to_string(i) + ".dot"; i++;
        std::ofstream outputFile;
        outputFile.open(FileName);
        print_search_tree(outputFile);

        outputFile.close();
      }
      /*!
      \brief Checks correctness of clock bounds, covering and ASG
      \return True if no bug has been found, false otherwise
      \post All errors have been output to std::cerr
    */
      virtual bool check() {
        unsigned nodes_count = 0, propagate_count = 0, covering_count = 0;
        bool correct = true;

        std::cerr << std::endl << "Checking..." << std::endl;

        // Checks every node active node
        for (auto it = _pw->pbegin(); it != _pw->pend(); ++it) {
            NODE const * node = *it;

            // Checks node is active
            if ( ! node->active ) {
                std::cerr << "Node " << node << " is inactive" << std::endl;
                correct = false;
              }

            // Checks node is either expanded or covered
            if ( ( ! node->expanded) && (node->covering_node == nullptr) ) {
                std::cerr << "Node " << node << " is not expanded nor covered"
                          << std::endl;
                correct = false;
              }

            // Checks node is not both covered and covering
            if ( (node->covering_node != nullptr) &&
                 (! node->covered_nodes.empty()) ) {
                std::cerr << "Node " << node << " is both covered and covering"
                          << std::endl;
                correct = false;
              }

            // Checks covering edge
            if (node->covering_node != nullptr) {
                // Checks covering node is active
                if (! node->covering_node->active) {
                    std::cerr << "Node " << node
                              << " is covered by inactive node "
                              << node->covering_node
                              << std::endl;
                    correct = false;
                  }

                // Checks covering holds
                //	  if ( ! _dyn_cover(node, node->covering_node) ) {
                //	    std::cerr << "Node " << node
                //		      << " is not covered by node " << node->covering_node
                //		      << std::endl;
                //	    correct = false;
                //	  }

                // Checks node is not expanded but its covering node is expanded
                if (node->expanded) {
                    std::cerr << "Node " << node << " is expanded and covered"
                              << std::endl;
                    correct = false;
                  }

                if (! node->covering_node->expanded) {
                    std::cerr << "Node " << node
                              << " is covered by non-expanded node "
                              << node->covering_node
                              << std::endl;
                    correct = false;
                  }


                ++covering_count;
              }

            // Checks propagation edges
            for (asg_propagate_t<NODE> const & p : node->propagate) {
                // Don't check if target node is inactive
                if ( ! p.to->active )
                  continue;

                // Checks that node statically covers the target node
                NODE * next = new NODE();
                assert(next != nullptr);
                _zg->next(* p.to, p.vedge, *next);
                if ( ! (* next->zone() <= * node->zone()) ) {
                    std::cerr << "Node " << node
                              << " does not statically cover successor of node "
                              << p.to << std::endl;
                    correct = false;
                  }
                delete next;
                ++propagate_count;
              }


            ++nodes_count;
          }

        // Done
        if (correct)
          std::cerr << "No bug found" << std::endl;
        else
          std::cerr << "All bugs found have been reported" << std::endl;
        std::cerr << "Checked "
                  << nodes_count << " node(s) "
                  << propagate_count << " propagation edge(s) "
                  << covering_count << " covering edge(s)"
                  << std::endl;
        std::cerr << std::endl;

        return correct;
      }



      /*!
      \brief Outputs stats
      \param level : stats level
      \post Stats of level at most 'level' have been output to std::cout
     */
      void stats(unsigned level) const {
        assert(_pw != nullptr);

        this->algorithms::zg_algorithm_t::stats(level); // display model name 1st
        this->algorithms::emptiness::algorithm_t::stats(level);

        // Nodes number stats
        _stats.output(std::cout, level);

        // Passed waiting list stats
        this->_pw->stats(std::cout, level);

        // Automaton states stats
        graph::stats_states(std::cout, level, _pw->pbegin(), _pw->pend(),
                            [] (NODE const * node) {
          return node;
        } );

        // Zones stats
        graph::stats_zones(std::cout, level, _pw->pbegin(), _pw->pend(),
                           [] (NODE const * node) {
          return node->_zone;
        } );

        // Dynamic covered nodes stats
        graph::stats_dynamic_covered( std::cout, level, _pw->pbegin(),
                                      _pw->pend(),
                                      [] (NODE const * node) {
          return node->covered_nodes.size();
        } );

        // Level 1
        if (level < 1)
          return;

        std::cout << stats::NODES_INACTIVE << _inactive_nodes.size()
                  << std::endl;
      }


      /*!
      \brief Displays the state-space computed by the algorithm
      \post The ASG stored in the PW list has been displayed. Orientation of
      edges corresponds to direction of propagation.
    */
      void dump() const {
        assert( _pw != nullptr );

        if (_algorithm_options.go_flags == graph::OUTPUT_NO)
          return;

        // Displays the state-space from the PW list
        this->_go->layer(graph::L_NEW); // Change to new layer
        this->_go->title("Adaptive Simulation Graphs\n"
                         "Propagation edges: "
                         "plain black=to parent node, "
                         "plain blue=to other nodes, "
                         "dashed blue=to covering node");

        for (auto it = _pw->pbegin(); it != _pw->pend(); ++it) {
            NODE const * node = *it;

            // Dumps node
            this->_go->node(*node);

            // Dumps a covering edge to every covered node
            for (NODE * n : node->covered_nodes)
              this->_go->edge(*node, *n, graph::ET_COVERING);

            // Dumps an edge to every depend node
            for (asg_propagate_t<NODE> const & p : node->propagate)
              if (node->to_parent(p))
                this->_go->edge(*node, * p.to, graph::ET_NORMAL);
              else
                this->_go->edge(*node, * p.to, graph::ET_PROPAGATION);
          }

        this->_go->layer(graph::L_BACKGROUND);
      }

      bool concrete (NODE* n) {
        if (n->has_parent)
          {
            _zg->next( *((n->parent()).to), (n->parent()).vedge, *n);
          }
        else {
            _zg->initial(*n);
          }
        return n->zone()->empty();
      }
      virtual NODE* where_cut(std::vector<NODE*> path, std::vector<NODE *> &uncovered) =0;
      /*!< Passed waiting list */
      graph::pw_t<NODE> * _pw;
      /*!< PW cover predicate */
      graph::nodes_binpred_t<NODE> _pw_cover;
      /*!< Dynamic cover predicate */
      // graph::nodes_binpred_t<NODE> _dyn_cover;
      /*!< Adaptative Simulation Graph (ASG) */
      asg_t<NODE> _asg;
      /*!< Inactive nodes */
      std::vector<NODE *> _inactive_nodes;
      /*!< Statistics */
      stats_t _stats;
      /*!< Algorithm's options */
      algorithms::options_t const & _algorithm_options;

    };
  } // end of namespace otfboundsemptiness

} // end of namespace algorithms

#endif // CEGAREMPTINESS_HH

#ifndef __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_GENERIC_HH__
#define __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_GENERIC_HH__

#include <iostream>
#include <limits>
#include <utility>
#include <vector>

#include "algorithms/algorithms.hh"
#include "algorithms/algorithms-options.hh"
#include "algorithms/emptiness.hh"
#include "algorithms/otfboundsemptiness/otfboundsemptiness-asg.hh"
#include "algorithms/otfboundsemptiness/otfboundsemptiness-plist.hh"
#include "algorithms/otfboundsemptiness/otfboundsemptiness-stats.hh"
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

/*!
  \file otfboundsemptiness-generic.hh
  \brief Generic emptiness algorithms with on-the-fly clock bounds computation
*/

namespace algorithms {

  namespace otfboundsemptiness {

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
      node_t() : active(true), expanded(false) {
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


      /*!
	\brief Clears the bounds
       */
      virtual void clear_bounds() = 0;


      /*!
	\brief Less-than-or-equal predicate on bounds
	\param n : node to compare
	\return True if the bounds in this are smaller than in n, false
	otherwise
      */
      virtual bool leq_bounds(NODE const & n) const = 0;


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



    /*!
      \class pdata_t
      \brief Propagated data for on-the-fly bounds generic algorithm
      \tparam NODE : type of nodes
    */
    template <class NODE>
    class pdata_t : public propagation_list_data_t<NODE> {
    public:
      /*!
	\brief Constructor
       */
      pdata_t() : hops(0) {
      }

      /*!
	\brief Destructor
      */
      virtual ~pdata_t() = default;

      /*!
	\brief Clears the data
	\post from_node, to_node and edge point to nullptr and hops has been
	reset to 0
      */
      virtual void clear() {
	this->propagation_list_data_t<NODE>::clear();
	hops = 0;
      }

      /*!
	\brief Merge pdatas
	\param pdata : data to merge
	\pre pdata and this are compatible (see propagation_list_data_t::merge)
	\post pdata has been merged into this
      */
      void merge(pdata_t<NODE> const & pdata) {
	this->propagation_list_data_t<NODE>::merge(pdata);
	hops = (pdata.hops > hops ? pdata.hops : hops); // Max of hops
      }
      
      /*!
	\brief Tells if data needs to be propagated
	\return True if data needs propagation, false otherwise
       */
      virtual bool needs_propagation() const = 0;

      unsigned hops; /*!< Counts # edges traversed during propagation */
    };


    /*!
      \brief Less-than predicate over pdata for sorted propagation. It
      implements the following order pdata1 < pdata2 if
      . (pdata1.from.id > pdata2.from.id)
      . or from nodes have same id and (pdata1.to.id > pdata2.to.id)
      . or from/to nodes have same id and pdata1.vedge > pdata2.vedge
      The first two conditions is an heuristic to propagate less: we propagate
      in priority from the youngest nodes to the oldest ones, and hope that
      some propagation data will be merged. The third condition guarantees
      that we have a total order.
      \tparam PDATA : type of propagation data. Should inherit from
      pdata_t<NODE>
      \param pdata1 : first data to compare
      \param pdata2 : second data to compare
      \return True if pdata1 < pdata2 for order < described above, false
      otherwise
    */
    template <class PDATA>
    inline bool pdata_lt_id(PDATA const & pdata1, PDATA const & pdata2) {
      // Check from nodes identifiers
      if (pdata1.from->id > pdata2.from->id)
	return true;
      if (pdata1.from->id < pdata2.from->id)
	return false;
      // They are equal, check to nodes id
      if (pdata1.to->id > pdata2.to->id)
	return true;
      if (pdata1.to->id < pdata2.to->id)
	return false;
      // Both are equal, we check vedge (to have a total order)
      return (pdata1.vedge < pdata2.vedge);
    }




    /*!
      \class algorithm_t
      \brief Generic on-the-fly bounds emptiness algorithm

      This algorithm improves on static bounds emptiness algorithm (see
      algorithms::staticboundsemptiness::algorithm_t). It computes and
      propagates bounds on-the-fly, while solving the emptiness problem.
      This "dynamic" bounds are used to avoid exploring nodes that are not
      covered wrt static bounds.

      The algorithm uses both static bounds and dynamic bounds. Static
      bounds are used for extrapolation to guarantee good performances in
      terms of memory consumption. To this purpose, the algorithm uses a
      Passed-waiting list (see graph::pw_t). The dynamic bounds are used to
      check if a node that is going to be explored is covered by a visited
      node (dynamic covering). If this is the case, the node is node explored.
      The dynamic covering test uses optimal aLU-inclusion test.

      Since the algorithm needs to propagate the dynamic bounds, it has to
      maintain an Adaptive Simulation Graph (ASG) (see asg_t). The algorithm
      searches the zone graph for an accepting node and propagates the bounds
      taking into account the transitions and the nodes that are encountered
      during the search. For correctness, it maintains the following
      invariants (see also the invariants on asg_t):

      (I1) if a transition t if disabled from (q,Z) and (q,Z,LU) is a node in
      the adaptive simulation graph, then t must be disabled from aLU(Z) too.
      
      (I2) Post(aLU(Z)) is included in aL'U'(Z') for every two nodes n=(q,Z,LU)
      and  n'=(q',Z',L'U') such that n' ~> n in the ASG (hence, n -> n' in the
      zone graph or to some node statically covered by n')

      (I3) if a node n=(q,Z,LU) is covered by n'=(q',Z',L'U') in the ASG (i.e.
      n << n'), then LU >= L'U'
      
      The algorithm is described by the following pseudo-code:

      MAIN:
      insert initial node n0 in PW
      while (W is not empty) do
        pick a node n from W
	if (n is accepting)
	  return "not empty"
	if (n is covered by n' in P-W, wrt to aLU and dynamic LU-bounds)
	  set n << n' and n' ~> n in ASG
	  copy the bounds from n' to n
          propagate(n)
	else
	  update the bounds in n wrt its invariant and the enabled and disabled
	     edges from n
	  for each transition n -> n' in the zone graph
            add n' ~> n in ASG
	    insert n' in PW
	  propagate(n)
      return "empty"

      PROPAGATE(n):
      for each n' st n ~> n' in ASG do
        if (n' << n) // propagation due to covering
	  if (n' is still covered by n wrt aLU and the dynamic bounds in n)
	    copy the bounds from n to n'
	    propagate(n')
	  else
  	    remove n' << n and n ~> n' from ASG
	    clear the bounds in n'
	    insert n' in W  // only in W as it is already in P
	else
	  let t be the transition that correspond to n ~> n' (i.e. n' -t-> n)
	  update the bounds in n' by propagating the bounds in n backward t
	  propagate(n')

      The way bounds are updated from the outgoing edges and the way they are
      propagated backward a transition are not defined in this algorithm.
      TChecker provides several variants of propagation algorithms that aim
      at keeping the bounds as small as possible while preserving the
      invariants above (see some of the otfboundsemptiness-* files)

      Notice that we check if current node n is covered by some node n' from
      P-W (i.e. P minus W). In other word, only the nodes that have been
      expanded can cover non-expanded nodes. This guarantees that there is no
      cycle in <<, as covered nodes (unexpanded) and covering nodes (expanded)
      form two disjoint sets. This is needed for completeness of the algorithm.
      It is implemented by nodes_acyclic_cover from the expanded flag in
      node_t. This is also needed for termination as otherwise, there
      could be an infinite number of unexpanded covering nodes in the adaptive
      simulation graph. In the end, the algorithm has to maintain the following
      invariant:

      (I4) No node is both covered and covering. This is ensured by: unexpanded
      nodes cannot dynamically cover any node, expanded node are not
      dynamically covered

      The algorithm uses a Passed-Waiting list (see graph::pw_t). It is not
      needed to ensure termination: the test w.r.t. to dynamic bounds is
      sufficient. However, since we use static bounds for the PW list, every
      time a node is covered w.r.t. static bounds, we can safely erase it. This
      allows to save memory (and time) and to scale up to bigger models. The
      PW list has to be instrumented to maintain the invariants by updating
      the relations ~> and << in the ASG as follows:

      1- don't add a node n if it is statically covered by some node n' in P.
      Then, replace n by n' in the ASG and propagate from n' to all nodes that
      depended on n before

      2- otherwise, all the nodes n' that are statically covered by n are
      replaced by n is the ASG. Remove all such node n' from P and W, and add
      n to P and W. Observe that it is not needed to propagate from n to all
      the nodes that depended on such node n' before as n is a new node that
      does not have any bound yet.

      Observe that a node n' removed from P and W in (2) above, becomes
      useless. However, it cannot be deleted as some unknown node may still
      propagate to n'. Indeed, nodes in the ASG only store the left-to-right
      direction of the propagation relation ~> in order to save memory. The
      solution consists in deactivating n' (free as much memory as possible)
      and stop propagation each time it reaches an propagation edge ~> n'
      pointing to n' (as this edge should not exist anymore).

      \tparam NODE : type of nodes. It should derive from node_t.
      \tparam PDATA : type of data propagated to computed the bounds. It
      should derive from pdata_t<NODE>
     */
    template <class NODE, class PDATA>
    class algorithm_t
      : public algorithms::emptiness::algorithm_t,
	public algorithms::zg_algorithm_t,	
	public algorithms::graph_output_owner_t {

      /* static_assert( NODE derives from node_t ) */
      /* static_assert( PDATA derives from pdata_t<NODE> ) */

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
	_dyn_cover = [cover] (NODE const * n1, NODE const * n2) {
	  return nodes_acyclic_cover(n1, n2) && cover(n1, n2);
	};

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

	// Builds the propagation list
	plist_flags_t plist_flags;
	switch (options.propagation_strategy_flags) {
	case algorithms::options_t::PS_FIFO:
	  plist_flags = PLIST_FIFO;
	  break;
	case algorithms::options_t::PS_YFP:
	  plist_flags = PLIST_SORTED;
	  break;
	default:
	  throw std::logic_error
	    ("*** algorithms::otfboundsemptiness::algorithm_t: "
	     "unsupported propagation strategy");
	}
	plist_factory_t & f_plist = plist_factory_t::instance();
	pdata_predicate_t<PDATA> plist_lt = pdata_lt_id<PDATA>;
	_plist = f_plist.new_plist(plist_lt, plist_flags);
      }
      

      /*!
	\brief Destructor
      */
      virtual ~algorithm_t() {
	delete _pw;
	delete _plist;
      }
    protected:
      /*!
	\brief Emptiness check
	\return True if no accepting state is reachable, false otherwise
      */
      virtual bool emptiness_check() {
	NODE * current = nullptr,           // Node under consideration
	  * next = nullptr,                 // Next node to consider  
	  * covering_node = nullptr;        // Covering node
	std::vector<NODE *> covered_nodes;  // Covered nodes
	std::vector<NODE *> succs;          // Successor nodes
	PDATA pdata;                        // Current node's propagation data
	bool empty = true;                  // Verdict
	unsigned snumber = 0;               // Search number

	// Initialization
	this->_go->start();
	this->_go->title("Reachability tree");
	_stats.initialize();

	// Insert initial node
	current = new NODE();
	assert(current != nullptr);

	_zg->initial(*current);

	if (current->status() == graph::STATE_STATUS_OK) {
	  _pw->insert(current, covering_node, covered_nodes);
	  assert( covering_node == nullptr );  // PW list empty before insert
	  assert( covered_nodes.empty() );

	  ++ _stats.nodes_count;
	  current->id = _stats.nodes_count;
	}
	else
	  delete current;

	// Explore reachable state-space
	while ( ! _pw->wempty() ) {
	  // Pick next node
	  current = _pw->wnext();

	  if (current->snumber == 0) { // Not visited yet
	    ++ snumber;
	    current->snumber = snumber;
	    this->_go->node(*current);
	  }
	  dump();
	  
	  // Do not expand current node if dynamically covered. Updates ASG.
	  // Propagates modified datas (given by pdata) from current node
	  if ( _pw->cover(current, covering_node, _dyn_cover) ) {
	    _asg.cover(current, covering_node);
	    insert_copy_propagation(covering_node, current);
	    propagate();
	    continue;
	  }

	  ++ _stats.visited_nodes_count;
	  
	  // Done if current node is accepting
	  if ( current->accepting(this->accepting_labels()) ) {
	    empty = false;
	    break;
	  }

	  // Current node is now expanded (set expanded flag, updates bounds
	  // wrt invariant and outgoing edges, etc). The ASG is updated
	  // accordingly. pdata stores which bounds in node current have been
	  // modified in the process and need to be propagated
	  pdata.clear();

	  on_expand_node(*current, pdata);
	  	
	  for (auto r = _zg->outgoing_edges(*current); ! r.at_end();
	       r.advance()) {
	    syntax::vedge_t const & vedge = r.current();
	    next = new NODE();
	    assert(next != nullptr);

	    _zg->next(*current, vedge, *next);

	    // Ignore nodes obtained from edges disabled wrt vloc or layout
	    if ( (next->status() != graph::STATE_STATUS_OK) &&
		 (next->status() != graph::STATE_STATUS_EMPTY_ZONE) ) {
	      delete next;
	      continue;
	    }

	    // Takes the (enabled or disabled) edge into account for bounds
	    on_expand_edge(*current, *next, vedge, pdata);

	    // Ignore disabled edges for state-space exploration
	    if (next->status() != graph::STATE_STATUS_OK) {
	      delete next;
	      continue;
	    }

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
	  insert_nodes_pw(succs);
	  succs.clear();
	  
	  // Once current node's bounds have been updated, propagate modified
	  // bounds
	  // IMPLEMENTATION NOTE: deactivation occurs first since, if current
	  // has been deactivated, we skip some useless propagation. We choose
	  // to propagate once the ASG has been updated to avoid useless
	  // propagations
	  if ( current->active )
	    insert_all_propagation(current, pdata);
	  propagate();
	}

	// Check
	if (_algorithm_options.check_flag)
	  check();
	
	// Output stats, etc.
	stats(_algorithm_options.stats_level);
	dump();

	// Done
	this->_go->end();
	_pw->clear_and_delete();
	for (NODE * n : _inactive_nodes)
	  delete n;
	_inactive_nodes.clear();

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
	from the passed waiting list, replaced by n in the ASG and deactivated
	. if n is statically covered, it has not been inserted in the passed
	waiting list, n has been replaced by its covering node in the ASG, n
	has been deleted and propagation has been scheduled for invariants
       */
      void insert_nodes_pw(std::vector<NODE *> & nodes) {
	std::vector<NODE *> dynamic_uncovered_nodes, covered_nodes,
	  deactivated_nodes;
	NODE * covering_node;

	  // Pushes all nodes to PW list. Updates ASG and propagates if needed
	  // IMPLEMENTATION NOTE: in the sequel, when a node n' replaces a
	  // node n, we do not modify propagation edges n'' ~> n pointing to n
	  // into propagation edges n'' ~> n' pointing to n'. This is because
	  // as state-space exploration goes on, either the whole subtree of n'
	  // will take place of the subtree of n, or n' will be covered,
	  // providing better propagation edges (that is, with adequate smaller
	  // bounds)
	for (NODE * node : nodes) {
	  assert( node->active );
	  assert( ! _pw->pfind(node) );
	  assert( ! _pw->wfind(node) );

	  covered_nodes.clear();
	  if ( _pw->insert(node, covering_node, covered_nodes) ) {
	    assert( covering_node == nullptr );
	    // node has been inserted. It takes place of all statically
	    // covered_nodes in ASG. Observe we don't need to propagate
	    // from node since as a new node it does not have bounds yet
	    for (NODE * n : covered_nodes) {
	      // display deactivated nodes that have not been displayed yet
	      if (n->snumber == 0)
		this->_go->node(*n);
	      _asg.replace(n, node, dynamic_uncovered_nodes);
	      n->deactivate();
	      deactivated_nodes.push_back(n);
	    }
	  }
	  else {
	    assert( covered_nodes.empty() );

	    // node has not been displayed yet and it will be destroyed
	    this->_go->node(*node);

	    // node has not been inserted, it is replaced by covering_node
	    // in ASG. Propagation from covering_node to all nodes that
	    // depended on node is required. Observe that node does cover
	    // any node as this a new node.
	    for (asg_propagate_t<NODE> & p : node->propagate)
	      insert_edge_propagation(covering_node, p);
	    _asg.replace(node, covering_node, dynamic_uncovered_nodes);
	    delete node;
	  }
	}

	// Push all dynamic uncovered nodes that are still active in the
	// waiting list only (they already belong to the passed list)
	// IMPLEMENTATION NOTE: this must be done once all nodes have been
	// processed since some node n may be both dynamically and statically
	// covered by nodes. Hence, it has been deactivated (static covering)
	// and should not be explored (and pushed in the PW list)
	for (NODE * n : dynamic_uncovered_nodes)
	  if ( n->active )
	    _pw->winsert(n);

	// Delete all deactivated nodes that are not pointed to by any node,
	// and store all others as inactive nodes
	for (NODE * n : deactivated_nodes)
	  if (n->has_propagator)
	    _inactive_nodes.push_back(n);
	  else
	    delete n;
      }


      /*!
	\brief Inserts propagation along an edge in the propagation list
	\param from_node : source node
	\param p : target node and vedge
	\post A PDATA entry with bounds that need to be propagated from node
	"from" to node "p.to" along edge "p.vedge" has been inserted in the
	propagation list
       */
      void insert_edge_propagation(NODE * from,
				   asg_propagate_t<NODE> const & p)
      {
	PDATA d;

	on_propagate_from_node(*from, d);
	if ( ! d.needs_propagation() )  // optimization
	  return;

	make_edge_propagation(d, from, p.to, & p.vedge);
	d.hops = 0;

	_plist->push(d);
      }


      /*!
	\brief Inserts copy propagation in the propagation list
	\param from : source node
	\param to : target node
	\post A PDATA entry with bounds that need to be copied from node
	"from" to node "to" has been inserted in the propagation list
      */
      void insert_copy_propagation(NODE * from, NODE * to) {
	PDATA d;

	on_propagate_from_node(*from, d);
	if ( ! d.needs_propagation() )  // optimization
	  return;

	make_copy_propagation(d, from, to);
	d.hops = 0;

	_plist->push(d);
      }


      /*!
	\brief Inserts propagation to all dependent nodes in the propagation
	list
	\param from : source node
	\param pdata : propagation data
	\pre pdata stores which bounds in node "from" need to be propagated
	\post For every node that depend on node "from", a PDATA entry with
	bounds from pdata have been inserted in the propagation list. The
	entry is either an edge propagation or a copy propagation depending
	on the link between node "from" and the dependent node in the ASG
	(propagate or covered)
       */
      void insert_all_propagation(NODE * from, PDATA const & pdata) {
	PDATA d;

	if ( ! pdata.needs_propagation() ) // optimization
	  return;
	
	for (asg_propagate_t<NODE> const & p : from->propagate) {
	  d = pdata;
	  make_edge_propagation(d, from, p.to, & p.vedge);
	  _plist->push(d);
	}

	for (NODE * n : from->covered_nodes) {
	  d = pdata;
	  make_copy_propagation(d, from, n);
	  _plist->push(d);
	}
      }



      /*!
	\brief Propagates bounds following the propagation list
	\post All propagations in the propagation list have been handled. The
	propagation list is empty.
       */
      void propagate() {
	PDATA pdata;

	while ( ! _plist->empty() ) {
	  // Applies and updates top propagation data
	  pdata = _plist->pop();
	  apply_and_update_pdata(pdata);
	  
	  // pdata now stores the bounds in node pdata.to that need propagation
	  // If no further propagation needed, simply update stats
	  if ( ! pdata.needs_propagation() ) {
	    ++ _stats.prop_threads_count;
	    _stats.max_hops =
	      ( pdata.hops > _stats.max_hops ? pdata.hops : _stats.max_hops );
	    _stats.avg_hops =
	      ( ( _stats.avg_hops * ( _stats.prop_threads_count - 1 ) )
		+ pdata.hops ) / _stats.prop_threads_count;
	    continue;
	  }

	  // Otherwise, the bounds in pdata.to have been updated. Propagation
	  // goes on from pdata.to with bounds given by pdata
	  ++ _stats.updates_count;
	  insert_all_propagation(pdata.to, pdata);
	}
      }



      /*!
	\brief Applies and updates propagation data

	Updates the bounds in "to" node from the bounds in "from" node. The
	propagation data tells which bounds in node "from" need propagation.
	pdata is updated to tell which bounds in node "to" have been updated
	and need propagation.

	Notice that pdata may not be relevant anymore. Indeed, during the
	propagation process, as bounds are updated, nodes are uncovered. Hence
	pdata may require to copy bounds over a covering edge that does not
	exist anymore. pdata is simply ignored in this case.

	Also, inactive nodes need to be taken into account. Recall that an
	inactive node should be considered as inexisting nodes for propagation.
	Hence, is pdata requires to propagate to an inactive node, it is again
	ignored.

	\param pdata : propagation data
	\pre pdata tells which bounds in pdata.from need to be propagated to
	node pdata.to
	\post pdata has been ignored and cleared if it is not relevant anymore.
	Otherwise, the bounds in node pdata.to have been updated from the bounds
	in node pdata.from taking into account the edge pdata.vedge. If
	pdata.vedge is a covering edge, then the bounds have been copied calling
	event on_copy_bounds(). Otherwise, when pdata.vedge is a regular edge,
	the bounds have been propagated backward pdata.vedge calling event
	on_propagate_backward(). Finally, pdata has been updated to reflect
	which bounds in node pdata.to have been modified
       */
      void apply_and_update_pdata(PDATA & pdata) {
	// Stop propagation if pdata is not relevant anymore, that is when
	// it is a copy edge and the covering relation has been updated.
	if ( pdata.is_copy() && ( pdata.to->covering_node != pdata.from ) ) {
	  pdata.clear();
	  return;
	}

	// Stop propagation if pdata points to an inactive node
	if ( ! pdata.to->active ) {
	  pdata.clear();
	  return;
	}

	// If copy propagation (from covering node to covered node), check that
	// covering still holds as bounds in covering node have been modified.
	// If so, copy the bounds, if not, uncover node pdata.to, reset its
	// bounds and puts it back in W list
	if ( pdata.is_copy() ) {
	  assert( pdata.to->covering_node == pdata.from );

	  if ( _dyn_cover(pdata.to, pdata.from) ) { // still covered
	    on_copy_bounds(pdata);
	    ++ pdata.hops;
	  }
	  else {  // not covered anymore
	    _asg.uncover(pdata.to);
	    ++ _stats.uncoverings_count;

	    pdata.to->clear_bounds();

	    assert( _pw->pfind(pdata.to) );
	    if (! _pw->wfind(pdata.to))  // constant time query
	      _pw->winsert(pdata.to);

	    pdata.clear();
	  }

	  return;
	}
	
	// Else, propagation on a regular edge
	on_propagate_backward(pdata);
	++ pdata.hops;
      }


      /*!
	\brief Updates the bounds in a node when it is expanded (immediately
	before its outgoing edges are expanded)
	\param node : node to consider
	\param pdata : propagation data
	\pre node has status graph::STATE_STATUS_OK
	\post Flag expanded in node has been set to true
       */
      virtual void on_expand_node(NODE & node, PDATA & pdata) {
	node.expanded = true;
      }


      /*!
	\brief Updates the bounds in a node when an edge is expanded
	\param src : source node of the edge
	\param tgt : target node of the edge
	\param vedge : the edge that has been expanded
	\param pdata : propagation data
	\pre src has status graph::STATE_STATUS_OK and tgt has status
	graph::STATE_STATUS_OK (edge enabled from src) or
	graph::STATE_EMPTY_ZONE (edge disabled from src)
	\post The bounds in node src have been updated wrt the bounds in tgt
	and the bounds and reset on vedge. pdata has been added all the bounds
	that have been modified in node src
       */
      virtual void on_expand_edge(NODE & src,
				  NODE const & tgt,
				  syntax::vedge_t const & vedge,
				  PDATA & pdata) = 0;


      /*!
	\brief Copies bounds between nodes
	\param pdata : propagation data
	\pre Nodes pdata.from and pdata.to have status graph::STATE_STATUS_OK.
	pdata tells which bounds to copy from node pdata.from to node pdata.to
	\post The bounds in node pdata.from have been copied to the node
	pdata.to, and pdata stores which bounds have been updated in node 
	pdata.to
       */
      virtual void on_copy_bounds(PDATA & pdata) = 0;


      /*!
	\brief Propagates data backward an edge
	\param pdata : propagation data
	\pre pdata.edge is a regular edge, not a copy propagation edge. Node
	pdata.to has been expanded. Nodes pdata.from and pdata.to are active
	(checked by assertion). pdata tells which bounds need to be propagated
	from node pdata.from to node pdata.to
	\post The bounds in node pdata.to have been updated from the bounds
	in node pdata.from taking into account the edge pdata.vedge. pdata has
	been updated to reflect which bounds in node pdata.to have been modified
       */
      virtual void on_propagate_backward(PDATA & pdata) = 0;


      /*!
	\brief Sets propagation data for propagation from a node
	\param node : node from which to propagate
	\param pdata : propagation data
	\post pdata stores all the bounds that need to be propagated starting
	from node
       */
      virtual void on_propagate_from_node(NODE const & node, PDATA & pdata) = 0;


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
	    if ( ! _dyn_cover(node, node->covering_node) ) {
	      std::cerr << "Node " << node
			<< " is not covered by node " << node->covering_node
			<< std::endl;
	      correct = false;
	    }

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

	    // Checks bounds over covering edge
	    correct = correct &&
	      on_check_bounds_covering(*node, * node->covering_node);

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

	    // Checks bounds over propagation edge
	    if ( ! on_check_bounds_propagate(*node, * p.to, p.vedge) )
	      correct = false;

	    ++propagate_count;
	  }

	  // Checks node's bounds are correct wrt other than propagation
	  // (invariant, disabled edges, ...)
	  on_check_bounds_node(*node);

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
	\brief Checks that node bounds are consistent with covering relation
	\param node : covered node
	\param covering_node : covering node
	\return True is the bounds in node and covering_node are consistent
	with the covering relation, false otherwise
	\post If the bounds are inconsistent, a message has been displayed
	on std::cerr
       */
      virtual bool on_check_bounds_covering(NODE const & node,
					    NODE const & covering_node) = 0;


      /*!
	\brief Checks that node bounds are consistent with propagation relation
	\param from : source node
	\param to : target node
	\param vedge : propagation edge
	\return True is the bounds in node "to" are consistent with the bounds
	in node "from" and propagation over "vedge", false otherwise
	\post If the bounds are inconsistent, a message has been displayed
	on std::cerr
       */
      virtual bool on_check_bounds_propagate(NODE const & from,
					     NODE const & to,
					     syntax::vedge_t const & vedge) = 0;


      /*!
	\brief Checks that node bounds are consistent
	\param node : node to check
	\return True is the bounds in node are consistent with invariant and
	disabled edges
	\post If the bounds are inconsistent, a message has been displayed
	on std::cerr
       */
      virtual bool on_check_bounds_node(NODE const & node) = 0;


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


      /*!< Passed waiting list */
      graph::pw_t<NODE> * _pw;
      /*!< PW cover predicate */
      graph::nodes_binpred_t<NODE> _pw_cover;
      /*!< Dynamic cover predicate */
      graph::nodes_binpred_t<NODE> _dyn_cover;
      /*!< Adaptative Simulation Graph (ASG) */
      asg_t<NODE> _asg;
      /*!< Propagation list */
      propagation_list_t<PDATA> * _plist;
      /*!< Inactive nodes */
      std::vector<NODE *> _inactive_nodes;
      /*!< Statistics */
      stats_t _stats;
      /*!< Algorithm's options */
      algorithms::options_t const & _algorithm_options;
    };

  } // end of namespace otfboundsemptiness

} // end of namespace algorithms

#endif // __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_GENERIC_HH__

#ifndef __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_ASG_HH__
#define __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_ASG_HH__

#include <list>
#include <stdexcept>

#include "syntax/ta.hh"

/*!
  \file otfboundsemptiness-asg.hh
  \brief Adaptive Simulation Graph (ASG) for emptiness algorithms with
  on-the-fly clock bounds computation
*/

namespace algorithms {

  namespace otfboundsemptiness {

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
		     has_propagator(false) {
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
	assert( substitute->leq_bounds(*node) );

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

  } // end of namespace otfboundsemptiness

} // end of namespace algorithms

#endif // __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_ASG_HH__

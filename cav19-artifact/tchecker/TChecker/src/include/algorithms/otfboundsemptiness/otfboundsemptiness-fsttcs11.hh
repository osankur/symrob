#ifndef __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_FSTTCS11_HH__
#define __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_FSTTCS11_HH__

#include "algorithms/otfboundsemptiness/otfboundsemptiness-generic.hh"
#include "base/clockset.hh"
#include "graph/nodescmp.hh"
#include "symbolic/clockbounds.hh"
#include "syntax/system_builder.hh"
#include "syntax/ta.hh"

/*!
  \file otfboundsemptiness-lu.hh
  \brief Emptiness algorithms with on-the-fly clock bounds computation,
  specialization to LU bounds and propagation from all edges

  "Using non-convex abstraction for efficient analysis of timed automata",
  F. Herbreteau, D. Kini, B. Srivathsan and I. Walukiewicz, FSTTCS, 2011
*/

namespace algorithms {

  namespace otfboundsemptiness {

    namespace fsttcs11 {

      /*!
	\class node_t 
	\brief Nodes for on-the-fly bounds algorithm specialized for LU
	bounds and propagation from all edges. Provides bounds L and U for the
	node
      */
      class node_t : public algorithms::otfboundsemptiness::node_t<node_t> {
    public:
	/*!
	  \brief Destructor
	*/
      virtual ~node_t();

	/*!
	  \brief Clears the bounds
	  \post L and U have been cleared
	*/
	virtual void clear_bounds();

	/*!
	  \brief Less-than-or-equal predicate on bounds
	  \param n : node to compare
	  \return True if the bounds in this are smaller than in n, false
	  otherwise
	*/
	virtual bool leq_bounds(node_t const & n) const;


	using algorithms::otfboundsemptiness::node_t<node_t>::output;
	
	/*!
	  \brief Output the node
	  \param os : output stream
	  \post The search number, underlying state and node's bounds have been 
	  output to os
	*/
	virtual void output(std::ostream & os) const;

	
	symbolic::clock_bounds_t L, U;  /*!< Node's bounds */
      };
      
    

      /*!
	\class pdata_t
	\brief Propagated data for on-the-fly bounds algorithm specialized for
	LU bounds and propagation from all edges. Provides flags that tell which
	bounds have been modified and need to be propagated.
      */
      class pdata_t : public algorithms::otfboundsemptiness::pdata_t<node_t> {
      public:
	/*!
	  \brief Destructor
	*/
	virtual ~pdata_t();

	/*!
	  \brief see algorithms::otfboundsemptiness::pdata_t::clear
	  \post The flags have been cleared
	*/
	virtual void clear();
	
	/*!
	  \brief Merge pdatas
	  \param pdata : data to merge
	  \pre pdata and this are compatible
	  (see propagation_list_data_t::merge)
	  \post pdata has been merged into this: the modified flags in pdata
	  have been added to this
	*/
	void merge(pdata_t const & pdata);

	/*!
	  \brief see algorithms::otfboundsemptinesspdata_t::needs_propagation
	  \return True if a flag is set, false otherwise
	*/
	virtual bool needs_propagation() const;
	
	
	clock_bitset_t L_modified; /*!< Which L bounds to propagate */
	clock_bitset_t U_modified; /*!< Which U bounds to propagate */
      };
      


      /*!
	\brief Predicate over nodes that checks for aLU covering wrt on-the-fly
	bounds in nodes
	\param n1 : first node to compare
	\param n2 : second node to compare
	\return True if n1 and n2 are equal with respect to state, and the
	zone in n1 is covered by the zone in n2 wrt aLU and on-the-fly LU
	bounds in node n2, false otherwise
      */
      bool nodes_zg_alu_dyn(node_t const * n1, node_t const * n2);


      /*!
	\class algorithm_t
	\brief LU on-the-fly bounds emptiness algorithm
	
	This algorithm is a specialization of the generic bounds propagation
	algorithm (see algorithms::otfboundsemptiness::algorithm_t). It 
	propagates the bounds from every edge that is encountered, both enabled
	and disabled edges according to:
	"Using non-convex approximations for efficient analysis of timed
	automata", F. Herbeteau, D. Kini, B. Srivathsan and I. Walukiewicz,
	FSTTCS, 2011.
      */
      class algorithm_t
	: public algorithms::otfboundsemptiness::algorithm_t<node_t, pdata_t> {
      public:
	/*!
	  \brief Constructor
	  \param system_builder : model builder used to build the zone graph
	  \param options : algorithm settings
	  \pre The guards in the system built by system_builder should not
	  contain any diagonal constraint
	*/
	algorithm_t(syntax::system_builder_t & system_builder,
		    algorithms::options_t const & options);

	/*!
	  \brief Destructor
	*/
	virtual ~algorithm_t();
      protected:
	/*!
	  \brief see algorithms::otfboundsemptiness::algorithm_t::on_expand_node
	  \post The bounds in node have been updated wrt its invariant. All the
	  bounds that have been updated have been added to pdata. Method
	  algorithm_t<node_t, pdata_t>::on_expand_node() has been called
       */
	virtual void on_expand_node(node_t & node, pdata_t & pdata);

	
	/*!
	  \brief see algorithms::otfboundsemptiness::algorithm_t::on_expand_edge
	  \post The bounds in node src are the maximum between the bounds in
	  node tgt (for clocks that are not reset) and the bounds on the guard
	  of edge. All the bounds that have been updated have been added to
	  pdata
	*/
	virtual void on_expand_edge(node_t & src,
				    node_t const & tgt,
				    syntax::vedge_t const & vedge,
				    pdata_t & pdata);
	
	
	/*!
	  \brief see algorithms::otfboundsemptiness::algorithm_t::on_copy_bounds
	  \post The modified bounds in node pdata.from have been copied to
	  pdata.to. All the modified bounds in node pdata.to have been added to
	  pdata
	*/
	virtual void on_copy_bounds(pdata_t & pdata);


      /*!
	\brief see
	algorithms::otfboundsemptiness::algorithm_t::on_propagate_backward
	\post The bounds in node pdata.to are the maximum between the bounds
	in node pdata.from (for clocks that are not reset) and the bounds on
	the guard of edge. All the bounds that have been updated have been
	added to pdata and the bounds that have not been updated have been
	removed
       */
      virtual void on_propagate_backward(pdata_t & pdata);


      /*!
	\brief see
	algorithms::otfboundsemptiness::algorithm_t::on_propagate_from_node
	\post pdata contains all the bounds in node
       */
      virtual void on_propagate_from_node(node_t const & node,
					  pdata_t & pdata);


      /*!
	\brief see
	algorithms::otfboundsemptiness::algorithm_t::on_check_bounds_covering
       */
      virtual bool on_check_bounds_covering(node_t const & node,
					    node_t const & covering_node);


      /*!
	\brief see
	algorithms::otfboundsemptiness::algorithm_t::on_check_bounds_propagate
       */
      virtual bool on_check_bounds_propagate(node_t const & from,
					     node_t const & to,
					     syntax::vedge_t const & vedge);

      /*!
	\brief
	see algorithms::otfboundsemptiness::algorithm_t::on_check_bounds_node
       */
      virtual bool on_check_bounds_node(node_t const & node);
    };

    } // end of namespace fsttcs11

  } // end of namespace otfboundsemptiness

} // end of namespace algorithms

#endif // __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_LU_HH__

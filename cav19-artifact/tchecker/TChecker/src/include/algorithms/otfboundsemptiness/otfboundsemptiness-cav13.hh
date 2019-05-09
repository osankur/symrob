#ifndef __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_CAV13_HH__
#define __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_CAV13_HH__

#include "algorithms/otfboundsemptiness/otfboundsemptiness-generic.hh"
#include "base/clockset.hh"
#include "graph/graph.hh"
#include "graph/graphoutput.hh"
#include "graph/nodescmp.hh"
#include "graph/pw.hh"
#include "semantics/semantics.hh"
#include "semantics/zg.hh"
#include "symbolic/clockbounds.hh"
#include "syntax/system_builder.hh"
#include "syntax/ta.hh"


/*!
  \file otfboundsemptiness-cav13.hh
  \brief Emptiness algorithms with on-the-fly clock bounds computation,
  specialization to LU bounds and propagation from disabled edges only.

  "Lazy Abstraction for Timed Automata", F. Herbreteau, B. Srivathsan and
  I. Walukiewicz, CAV, 2013.
*/

namespace algorithms {

  namespace otfboundsemptiness {

    namespace cav13 {

      /* IMPLEMENTATION NOTE: some of the classes ans methods below are
	 similar to classes and methods for the FSTTCS11 algorithm (see
	 otfboundsemptiness-fsttcs11.hh). The code has been duplicated to
	 allow modifications in one algorithm independently of the other
      */


      /*!
	\class node_t 
	\brief Nodes for on-the-fly bounds propagation algorithm from disabled
	edges only. Provides bounds L and U for the node
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
	\brief Propagated data for on-the-fly bounds propagation algorithm
	from disabled edges only. Provides flags that tell which bounds have
	been modified and need to be propagated
      */
      class pdata_t : public algorithms::otfboundsemptiness::pdata_t<node_t> {
      public:
	/*!
	  \brief Destructor
	*/
	virtual ~pdata_t();

	/*!
	  \brief see algorithms::otfboundsemptiness::pdata_t::clear
	  \post Same as inherited clear method + the flags have been cleared
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
	  \brief see algorithms::otfboundsemptiness::pdata_t::needs_propagation
	  \return True if a flag is set, false otherwise
	*/
	virtual bool needs_propagation() const;
	
	
	/*!< Which L bounds have been modified (hence need propagation) */
	clock_bitset_t L_modified;
	/*!< Which U bounds have been modified (hence need propagation) */
	clock_bitset_t U_modified;
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
	\brief Emptiness algorithm with on-the-fly LU bounds propagation from
	disabled edges only

	This algorithm is a specialization of the generic bounds propagation
	algorithm (see algorithms::otfboundsemptiness::algorithm_t) and a
	refinement of algorithms::otfboundsemptiness::fsttcs11::algorithm_t. 
	It propagates only the bounds discovered from the disabled edges, as
	documented in:
	"Lazy abstractions for timed automata", F. Herbreteau, B. Srivathsan
	and I. Walukiewicz, CAV, 2013.
      */
      class algorithm_t
	: public algorithms::otfboundsemptiness::algorithm_t<node_t, pdata_t> {
      public:
	/*!
	  \brief Constructor
	  \param system_builder : model builder used to build the zone graph
	  \param options : algorithm settings
	  \pre Chosen operational semantics in options is elapsed-last lazy
	  invariant (semantics::SEM_EL_LAZYINV). Chosen zone representation is
	  DBM (semantics::SEM_DBM). The invariants in the system built by
	  system_builder should only contain upper bound clock constraints
	  (x <= c or x < c). The guards in the system should not contain any
	  diagonal constraint
	  \throw std::logic_error : when chosen operational semantics is not the
	  elapsed-last lazy invariant semantics
	  \throw std::logic_error : when chosen symbolic representation for
	  zones is not DBM
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
	\post Method algorithm_t<node_t, pdata_t>::on_expand_node() has
	been called
       */
      virtual void on_expand_node(node_t & node, pdata_t & pdata);

      /*!
	\brief see algorithms::otboundsemptiness::algorithm_t::on_expand_edge
	\post If edge is disabled, the bounds in node src have been updated
	a zone that enables edge cannot be included in the aLU abstraction
	of the zone in node src according to the bounds in node src
	\throw std::logic_error : if the edge is disabled but one cannot
	find a constraint in edge that is disabled (sanity check)
      */
      virtual void on_expand_edge(node_t & src,
				  node_t const & tgt,
				  syntax::vedge_t const & vedge,
				  pdata_t & pdata);

      /*!
	\brief see algorithms::otfboundsemptiness:algorithm_t::on_copy_bounds
	\post The modified bounds in node pdata.from have been copied to
	pdata.to. All the modified bounds in node pdata.to have been added to
	pdata
      */
      virtual void on_copy_bounds(pdata_t & pdata);

      /*!
	\brief see
	algorithms::otfboundsemptiness::algorithm_t::on_propagate_backward
	\post The bounds in node pdata.to have been updated to ensure that
	Post(aLU(Z)) is included in aL'U'(Z') (where L,U,Z are from pdata.to,
	L',U',Z' are from pdata.from and Post is along pdata.vedge). The bounds
	that have been modified have been added to pdata, and the others have
	been removed
	\throw std::logic_error : if some constraint on pdata->edge is
	disabled
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
	algorithms::otfboundsemptiness;;algorithm_t::on_check_bounds_propagate
	\return True is the bounds in node "to" are consistent with the bounds
	in node "from" and propagation over "vedge", false otherwise
	\warning There are several non-deterministic choices for propagation
	of bounds. In general, not all of them are consistent. Only the choice
	made during exploration need to be consistent. This function checks that
	there exists a consistent choice, that may not correspond to the choice
	made by the algorithm.
       */
      virtual bool on_check_bounds_propagate(node_t const & from,
					     node_t const & to,
					     syntax::vedge_t const & vedge);

      /*!
	\brief see
	algorithms::otfboundsemptiness::algorithm_t::on_check_bounds_node
	\warning There are several non-deterministic choices for disabled
	guards in node. In general, not all of them are consistent. Only the
	choice made during exploration need to be consistent. This function
	checks that there exists a consistent choice, that may not correspond to 
	the choice made by the algorithm.
       */
      virtual bool on_check_bounds_node(node_t const & node);


      raw_t * _dbm_pre, * _dbm_middle, * _dbm_post; /*!< DBMs for propagation */
      size_t _dim;                                  /*!< Dimension of DBMs */
    };

    } // end of namespace cav13

  } // end of namespace otfboundsemptiness

} // end of namespace algorithms

#endif // __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_DISABLED_HH__

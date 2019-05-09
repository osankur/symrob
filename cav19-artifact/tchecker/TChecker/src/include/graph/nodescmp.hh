#ifndef __TCHECKER_NODESCMP_HH__
#define __TCHECKER_NODESCMP_HH__

#include <functional>

#include "base/ptr.hh"
#include "base/singleton.hh"
#include "semantics/zg.hh"
#include "syntax/system_bounds.hh"
#include "syntax/ta.hh"

namespace graph {

  /*!
    \brief Binary predicate on nodes
    \tparam NODE : type of nodes
  */
  template <class NODE>
  using nodes_binpred_t = std::function< bool(NODE const *, NODE const *) >;


  /*!
    \brief Binary predicate on nodes that is always false
    \tparam NODE : type of nodes
    \param n1 : first node to check
    \param n2 : second node to check
    \return false
  */
  template <class NODE>
  inline bool nodes_false(NODE const * n1, NODE const * n2) {
    return false;
  }


  /*!
    \brief Binary predicate on nodes that is satisfied if the two nodes are
    distinct
    \tparam NODE : type of nodes
    \param n1 : first node to check
    \param n2 : second node to check
    \return true if n1 is distinct from n2 (distinct adresses), false otherwise
  */
  template <class NODE>
  inline bool nodes_distinct(NODE const * n1, NODE const * n2) {
    return (n1 != n2);
  }


  
  /*!
    \brief Binary predicate on nodes checking less-than relation on identifiers
    \tparam NODE : type of nodes. Is expected to derive from graph::node_t
    \param n1 : first node to check
    \param n2 : second node to check
    \return true if the identifier of n1 is less-than the identifier of
    n2, false otherwise
  */
  template <class NODE>
  inline bool nodes_lt_id(NODE const * n1, NODE const * n2) {
    static_assert( std::is_base_of<graph::node_t, NODE>::value,
		   "*** graph::nodes_lt_id: incompatible node type" );
    return (n1->id < n2->id);
  }



  /*!
    \brief Binary predicate on nodes that checks for equality of underlying
    syntax::state_t
    \tparam NODE : type of nodes. Is expected to derive from syntax::state_t
    \param n1 : first node to check
    \param n2 : second node to check
    \return true if the syntax::state_t in n1 is equal to the syntax::state_t in
    n2, false otherwise
  */
  template <class NODE>
  inline bool nodes_syntax_eq(NODE const * n1, NODE const * n2) {
    static_assert( std::is_base_of<syntax::state_t, NODE>::value,
		   "*** graph::nodes_syntax_eq: incompatible node type" );
    return n1->syntax::state_t::operator==(*n2);
  }


  /*!
    \brief Binary predicate on nodes that checks for equality of zones
    \tparam NODE : type of nodes. Is expected to derive from
    semantics::zg::state_t
    \param n1 : first node to check
    \param n2 : second node to check
    \return true if the zone in n1 is equal to the zone in n2, false otherwise
  */
  template <class NODE>
  inline bool nodes_zone_eq(NODE const * n1, NODE const * n2) {
    static_assert( std::is_base_of<semantics::zg::state_t, NODE>::value,
		   "*** graph::nodes_zone_eq: incompatible node type" );
    return ( * n1->zone() == * n2->zone() );
  }



  /*!
    \brief Binary predicate on nodes that checks for equality of nodes
    \tparam NODE : type of nodes. Is expected to derive from
    semantics::zg::state_t
    \param n1 : first node to check
    \param n2 : second node to check
    \return true if n1 and n2 are distinct, and there underlying syntax::state_t
    are equal, and their zones are equal, false otherwise
  */
  template <class NODE>
  inline bool nodes_zg_eq(NODE const * n1, NODE const * n2) {
    static_assert( std::is_base_of<semantics::zg::state_t, NODE>::value,
		   "*** graph::nodes_zg_eq: incompatible node type" );
    return ( nodes_distinct<NODE>(n1, n2) &&
	     nodes_syntax_eq<NODE>(n1, n2) &&
	     nodes_zone_eq<NODE>(n1, n2) );
  }



  /*!
    \brief Binary predicate on nodes that checks for inclusion of zones
    \tparam NODE : type of nodes. Is expected to derive from
    semantics::zg::state_t
    \param n1 : first node to check
    \param n2 : second node to check
    \return true if the zone in n1 is included into the zone in n2, false
    otherwise
  */
  template <class NODE>
  inline bool nodes_zone_leq(NODE const * n1, NODE const * n2) {
    return ( * n1->zone() <= * n2->zone() );
  }



  /*!
    \brief Binary predicate on nodes that checks for node covering wrt zone
    inclusion
    \tparam NODE : type of nodes. Is expected to derive from
    semantics::zg::state_t
    \param n1 : first node to check
    \param n2 : second node to check
    \return true if n1 and n2 are distinct, and there underlying syntax::state_t
    are equal, and the zone in n1 is included in the zone in n2, false otherwise
  */
  template <class NODE>
  inline bool nodes_zg_leq(NODE const * n1, NODE const * n2) {
    static_assert( std::is_base_of<semantics::zg::state_t, NODE>::value,
		   "*** graph::nodes_zg_leq: incompatible node type" );
    return ( nodes_distinct<NODE>(n1, n2) &&
	     nodes_syntax_eq<NODE>(n1, n2) &&
	     nodes_zone_leq<NODE>(n1, n2) );
  }



  /*!
    \class nodes_zg_aLU_global_t
    \brief Binary predicate on nodes that checks for inclusion of zones wrt to
    aLU abstraction and global clock bounds
    \tparam NODE : type of nodes. Is expected to derive from
    semantics::zg::state_t
  */
  template <class NODE>
  class nodes_zg_aLU_global_t {
    static_assert( std::is_base_of<semantics::zg::state_t, NODE>::value,
		   "*** graph::nodes_zg_aLU_global_t: incompatible node type" );
  public:
    /*!
      \brief Constructor
      \param system_bounds : clock bounds used for aLU abstraction
     */
    nodes_zg_aLU_global_t(syntax::system_bounds_t const & system_bounds) {
      system_bounds.global_LU(LU);
    }

    /*!
      \brief Binary predicate on nodes that checks for inclusion of zones wrt to
      aLU abstraction and global clock bounds
      \param n1 : first node to check
      \param n2 : second node to check
      \return True if n1 and n2 are distinct, with same syntax::state_t and the
      zone in n1 is included in the aLU abstraction of the zone in n2 with
      respect to global clock bounds, false otherwise.
     */
    inline bool operator () (NODE const * n1, NODE const * n2) {
      return ( nodes_distinct<NODE>(n1, n2) &&
	       nodes_syntax_eq<NODE>(n1, n2) &&
	       n2->zone()->aLU_contains(* n1->zone(), LU.L, LU.U) );
    }
  protected:
    syntax::LU_bounds_t LU;   /*!< Global clock bounds */
  };



  /*!
    \class nodes_zg_aLU_local_t
    \brief Binary predicate on nodes that checks for inclusion of zones wrt to
    aLU abstraction and local clock bounds
    \tparam NODE : type of nodes. Is expected to derive from
    semantics::zg::state_t
  */
  template <class NODE>
  class nodes_zg_aLU_local_t {
    static_assert( std::is_base_of<semantics::zg::state_t, NODE>::value,
		   "*** graph::nodes_zg_aLU_local_t: incompatible node type" );
  public:
    /*!
      \brief Constructor
      \param system_bounds : clock bounds used for aLU abstraction
     */
    nodes_zg_aLU_local_t(syntax::system_bounds_t const & system_bounds)
      : _system_bounds(system_bounds) {
    }

    /*!
      \brief Binary predicate on nodes that checks for inclusion of zones wrt to
      aLU abstraction and local clock bounds
      \param n1 : first node to check
      \param n2 : second node to check
      \return True if n1 and n2 are distinct, with same syntax::state_t and the
      zone in n1 is included in the aLU abstraction of the zone in n2 with
      respect to local clock bounds, false otherwise.
    */
    inline bool operator () (NODE const * n1, NODE const * n2) {
      _system_bounds.local_LU(* n2->vloc(), LU);
      return ( nodes_distinct<NODE>(n1, n2) &&
	       nodes_syntax_eq<NODE>(n1, n2) &&
	       n2->zone()->aLU_contains(* n1->zone(), LU.L, LU.U) );
    }
  protected:
    syntax::system_bounds_t const & _system_bounds; /*!< System bounds */
    syntax::LU_bounds_t LU;                         /*!< Local clock bounds */
  };



  /*!
    \class nodes_zg_clM_global_t
    \brief Binary predicate on nodes that checks for inclusion of zones wrt to
    ClosureM abstraction and global clock bounds
    \tparam NODE : type of nodes. Is expected to derive from
    semantics::zg::state_t
  */
  template <class NODE>
  class nodes_zg_clM_global_t {
    static_assert( std::is_base_of<semantics::zg::state_t, NODE>::value,
		   "*** graph::nodes_zg_clM_global_t: incompatible node type" );
  public:
    /*!
      \brief Constructor
      \param system_bounds : clock bounds used for ClosureM abstraction
    */
    nodes_zg_clM_global_t(syntax::system_bounds_t const & system_bounds) {
      system_bounds.global_M(M);
    }

    /*!
      \brief Binary predicate on nodes that checks for inclusion of zones wrt to
      ClosureM abstraction and global clock bounds
      \param n1 : first node to check
      \param n2 : second node to check
      \return True if n1 and n2 are distinct, with same syntax::state_t and the
      zone in n1 is included in the ClosureM abstraction of the zone in n2 with
      respect to global clock bounds, false otherwise.
    */
    inline bool operator () (NODE const * n1, NODE const * n2) {
      return ( nodes_distinct<NODE>(n1, n2) &&
	       nodes_syntax_eq<NODE>(n1, n2) &&
	       n2->zone()->closure_contains(* n1->zone(), M.M) );
    }
  protected:
    syntax::M_bounds_t M;   /*!< Global clock bounds */
  };



  /*!
    \class nodes_zg_clM_local_t
    \brief Binary predicate on nodes that checks for inclusion of zones wrt to
    ClosureM abstraction and local clock bounds
    \tparam NODE : type of nodes. Is expected to derive from
    semantics::zg::state_t
  */  
  template <class NODE>
  class nodes_zg_clM_local_t {
    static_assert( std::is_base_of<semantics::zg::state_t, NODE>::value,
		   "*** graph::nodes_zg_clM_local_t: incompatible node type" );
  public:
    /*!
      \brief Constructor
      \param system_bounds : clock bounds used for ClosureM abstraction
    */
    nodes_zg_clM_local_t(syntax::system_bounds_t const & system_bounds)
      : _system_bounds(system_bounds) {
    }

    /*!
      \brief Binary predicate on nodes that checks for inclusion of zones wrt to
      ClosureM abstraction and local clock bounds
      \param n1 : first node to check
      \param n2 : second node to check
      \return True if n1 and n2 are distinct, with same syntax::state_t and the
      zone in n1 is included in the ClosureM abstraction of the zone in n2 with
      respect to local clock bounds, false otherwise.
    */
    inline bool operator () (NODE const * n1, NODE const * n2) {
      _system_bounds.local_M(* n2->vloc(), M);
      return ( nodes_distinct<NODE>(n1, n2) &&
	       nodes_syntax_eq<NODE>(n1, n2) &&
	       n2->zone()->closure_contains(* n1->zone(), M.M) );
    }
  protected:
    syntax::system_bounds_t const & _system_bounds; /*!< System bounds */
    syntax::M_bounds_t M;                           /*!< Local clock bounds */
  };



  /* Factory */

  /*!
    \brief Setup flags for binary predicates on nodes
  */
  typedef char nodes_binpred_flags_t;

  const nodes_binpred_flags_t NPRED_FALSE    =  0; /*<! always false */
  const nodes_binpred_flags_t NPRED_ZG_EQ    =  1; /*<! ZG state equal */
  const nodes_binpred_flags_t NPRED_ZG_LEQ   =  2; /*<! ZG state <=  */
  const nodes_binpred_flags_t NPRED_ZG_ALUG  =  3; /*<! ZG state aLU global */
  const nodes_binpred_flags_t NPRED_ZG_ALUL  =  4; /*<! ZG state aLU local */
  const nodes_binpred_flags_t NPRED_ZG_CLMG  =  5; /*<! ZG state clM global */
  const nodes_binpred_flags_t NPRED_ZG_CLML  =  6; /*<! ZG state clM local */

  /*!
    \brief Yields binary predicates on nodes (except aLU and clM predicates)
    \tparam NODE : type of nodes
    \param flags : type of node predicate to build
    \return A node predicate of type required by flags
    \throw std::logic_error : if flags is invalid
  */
  template <class NODE>
  nodes_binpred_t<NODE> nodes_binpred(nodes_binpred_flags_t flags) {
    switch (flags) {
    case NPRED_FALSE:
      return nodes_false<NODE>;
    case NPRED_ZG_EQ:
      return nodes_zg_eq<NODE>;
    case NPRED_ZG_LEQ:
      return nodes_zg_leq<NODE>;
    default:
      throw std::logic_error("*** nodes_binpred: invalid flags");
      break;
    }
  }

  
  /*!
    \brief Yields binary predicates on nodes (including aLU and clM
    predicates)
    \tparam NODE : type of nodes
    \param flags : type of node predicate to build
    \param system_bounds : clock bounds
    \return A node predicate of type required by flags
    \throw std::logic_error : if flags is invalid
  */
  template <class NODE>
  nodes_binpred_t<NODE> nodes_binpred(nodes_binpred_flags_t flags,
				      syntax::system_bounds_t const &
				      system_bounds) {
    switch (flags) {
    case NPRED_ZG_ALUG:
      return nodes_zg_aLU_global_t<NODE>(system_bounds);
    case NPRED_ZG_ALUL:
      return nodes_zg_aLU_local_t<NODE>(system_bounds);
    case NPRED_ZG_CLMG:
      return nodes_zg_clM_global_t<NODE>(system_bounds);
    case NPRED_ZG_CLML:
      return nodes_zg_clM_local_t<NODE>(system_bounds);
    default:
      return nodes_binpred<NODE>(flags);
    }
  }

} // end of namespace graph

#endif // __TCHECKER_NODESCMP_HH__

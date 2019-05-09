#ifndef __TCHECKER_REACHSET_HH__
#define __TCHECKER_REACHSET_HH__

#include <functional>
#include <utility>

#include <boost/functional/hash.hpp>

#include "base/cache.hh"
#include "base/ptr.hh"
#include "graph/ts.hh"


/*!
  \file reachset.hh
  \brief Reachability set of a transition system
*/

namespace graph {

  /* IMPLEMENTATION NOTE: we need template parameter TS below since the
     transition system given to the constructor of reachset_t may not inherit
     from graph::ts_t<STATE, EDGE_RANGE>. Usually, STATE derives
     from the type of states (i.e. state_t) defined by this transition system.
     That is the transition system used to build reachset_t inherits from
     graph::ts_t<S, EDGE_RANGE> and STATE derives from S (it is
     S plus some extra datas needed by the algorithm using reachset_t).
  */


  /*!
    \class reachset_t
    \brief Reachability set of a transition system
    
    Yields access to the state space of a transition system (see graph::ts_t)
    with states of type STATE and edge range of type EDGE_RANGE, with
    guarantee of unicity of nodes w.r.t. EQUAL. Each node that is explored
    using initial() and next() is stored in a hash table parametrized by HASH
    and EQUAL (see cache_t).
    
    The reachset is quite similar to graph::ts_t except that the memory
    allocated for the states is managed by the reachset. As a consequence,
    shared pointers are used to make sure that the nodes stored by the reachset
    are not deleted.
    
    \tparam STATE : type of states
    \tparam EDGE_RANGE : type of ranges of edges
    \tparam TS : type of underlying transition system. Implements graph::ts_t.
    STATE, EDGE_RANGE derive from states and edge_range_t in TS
    \tparam HASH : hasher on states
    \tparam EQUAL : equality predicate on states
   */
  template < class STATE,
	     class EDGE_RANGE,
	     class TS = graph::ts_t<STATE, EDGE_RANGE>,
	     class HASH = typename sp_t<STATE>::delegate_hash,
	     class EQUAL = typename sp_t<STATE>::delegate_equal_to >
  class reachset_t {
  public:
    /*!
      \brief Constructor
      \param ts : transition system
    */
    reachset_t(TS & ts) : _ts(ts) {
    }
    
    /*!
      \brief Destructor
      \post No destructors are called on stored values
     */
    ~reachset_t() = default;

    /*!
      \brief Clears the state space
      \post The state space is empty. No destructors are called on the state
      space
    */
    void clear() {
      _cache.clear();
    }

    /*!
      \brief Clears the state space and disposes of stored values
      \tparam DISPOSER : type of disposer
      \param disposer : disposer of stored values
      \post The state space is empty and disposer has been called on every
      stored value
    */
    template <class DISPOSER>
    void clear_and_dispose(DISPOSER disposer) {
      _cache.clear_and_dispose(disposer);
    }
    
    /*!
      \brief Initial state computation (see graph::ts_t::initial)
      \return The initial state of the underlying transition system. Its status 
      tells if the transition system has an initial state. The states with
      status graph::STATE_STATUS_OK are stored in a cache. Hence, if the
      state has status graph::STATE_STATUS_OK, then it is unique in the state
      space wrt EQUAL (i.e. successive calls return the same state). 
    */
    sp_t<STATE> initial() {
      sp_t<STATE> s = make_sp<STATE>();
      _ts.initial(*s);
      if (s->status() == graph::STATE_STATUS_OK)
	return _cache.find_else_insert(s);
      else
	return s;
    }

    /*!
      \brief Next state computation (see graph::ts_t::next)
      \return The successor state of s along edge 'it'. Its status tells if
      edge 'it' is enabled from state s. The states with status
      graph::STATE_STATUS_OK are stored in a cache. Hence, if the state has
      status graph::STATE_STATUS_OK, then it is unique in the state space wrt
      EQUAL (i.e. successive calls return the same state).
     */
    sp_t<STATE> next(sp_t<STATE> const & s, typename EDGE_RANGE::reference e) {
      sp_t<STATE> nexts = make_sp<STATE>();
      _ts.next(*s, e, *nexts);
      if (nexts->status() == graph::STATE_STATUS_OK)
	return _cache.find_else_insert(nexts);
      else
	return nexts;
    }

    /*!
      \brief see graph::ts_t::edge_range
     */
    EDGE_RANGE outgoing_edges(sp_t<STATE> const & s) {
      return _ts.outgoing_edges(*s);
    }

    /*!
      \brief Finds a state in the state space
      \param s : state to find
      \param sfound : state equal to s wrt EQUAL in the state space
      \return True if s is found in the state space, false otherwise
      \post If s is found in the state space, then sfound has been set to the
      state equal to s w.r.t. EQUAL. Othewise, sfound is meaningless.
     */
    bool find(sp_t<STATE> const & s, sp_t<STATE> & sfound) const {
      sfound.reset(); // by default, s is not found
      return _cache.find(s, sfound);
    }

    /*!
      \brief Type of iterator on the state space
      \warning Iterators should not be used to alter the nodes in the reachset,
      but exclusively for inspection
    */
    typedef typename cache_t< sp_t<STATE>, HASH, EQUAL >::iterator iterator;

    /*!
     \brief Iterator
     \return Iterator on first state in the state space
    */
    iterator begin() {
      return _cache.begin();
    }

    /*!
      \brief Iterator
      \return Iterator on the passed-the-end value in the state space
     */
    iterator end() {
      return _cache.end();
    }
  protected:
    /*!< Underlying transition system */
    TS & _ts;

    /*!< State space */
    cache_t< sp_t<STATE>, HASH, EQUAL > _cache;
  };

} // end of namespace graph

#endif // __TCHECKER_REACHSET_HH__

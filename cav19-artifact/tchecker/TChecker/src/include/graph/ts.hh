#ifndef __TCHECKER_TS_HH__
#define __TCHECKER_TS_HH__

#include <utility>

/*!
  \file ts.hh
  \brief Provides interfaces to transition systems

  A transition system is a directed graph with distinguished initial
  state. Class ts_t provides an abstract class (interface) that allows
  forward exploration of transition systems.

  The initial state of a transition system is retrieved using method
  ts_t::initial. The method ts_t::next allows to access the next states of
  a given state.

  The outgoing edges of a state (accessed through ts_t::outgoing_edges())
  should return at least all the edges enabled from the given state. It may
  return more edges. The status of the corresponding next state tells if the
  edge is enabled or not.
*/


/*!
  \namespace graph
  \brief Description and manipulation of graphs
*/
namespace graph {

  /*!
    \brief Status of a state
  */
  static const unsigned STATE_STATUS_OK         = 0; /*!< State is ok */
  static const unsigned STATE_STATUS_NO_VLOC    = 1; /*!< Has nullptr vloc */
  static const unsigned STATE_STATUS_NO_LAYOUT  = 2; /*!< Has nullptr layout */
  static const unsigned STATE_STATUS_NO_ZONE    = 4; /*!< Has nullptr zone */
  static const unsigned STATE_STATUS_EMPTY_ZONE = 8; /*!< Has an empty zone */



  /*!
    \class ts_t
    \brief Transition system (interface).
    \tparam STATE : type of states
    \tparam EDGE_RANGE : type of range over edges
  */
  template <class STATE, class EDGE_RANGE>
  class ts_t {
  public:
    /*!
      \brief Type of states in the transition system
    */
    typedef STATE state_t;

    /*!
      \brief Type of range of edges in the transition system
    */
    typedef EDGE_RANGE edge_range_t;

    /*!
      \brief Destructor
    */
    virtual ~ts_t() = default;

    /*!
      \brief Initial state of the transition system
      \param s : state to initialize
      \post s has been set to the initial state of the transition system. The
      status of s is set to indicate if the transition system has an initial
      state
    */
    virtual void initial(state_t & s) = 0;

    /*!
      \brief Next state computation
      \param s : source state
      \param e : outgoing edge of s
      \param nexts : state to compute
      \post nexts is the successor state of s along edge e. The status of
      nexts indicates if edge e is enabled from state s.
     */
    virtual void next(state_t const & s, typename edge_range_t::reference e,
		      state_t & nexts) = 0;

    /*!
      \brief Outgoing edges computation
      \param s : source state
      \return A range of outgoing edges of state s
     */
    virtual edge_range_t outgoing_edges(state_t const & s) = 0;
  };
    
} // end of namespace graph

#endif // __TCHECKER_TS_HH__

#ifndef __TCHECKER_TA_HH__
#define __TCHECKER_TA_HH__

#include <map>
#include <ostream>
#include <utility>
#include <vector>

#include <boost/container/flat_map.hpp>
#include <boost/container/flat_set.hpp>

#include "base/cache.hh"
#include "base/labelset.hh"
#include "base/stats.hh"
#include "base/ptr.hh"
#include "graph/ts.hh"
#include "syntax/layout.hh"
#include "syntax/sync_product.hh"
#include "syntax/system.hh"

/*!
  \file ta.hh
  \brief Timed automaton

  A timed automaton is built over a system of timed processes (see
  syntax::system_t). It basically computes the product of the
  processes, taking into account the synchronizations, that is,
  implementing asynchronous and synchronous transitions as specified
  by synchronizations.

  A state of an automaton is made of a vector of process locations (see
  syntax::vloc_t) and a layout (see syntax::layout_t).

  A transition is made of a tuple of synchronized edges. The tuple only
  contains one edge when the transition is asynchronous.

  The class syntax::ta_t implements virtual class graph::ts_t. The initial
  state is obtained using method syntax::ta_t::initial. Transitions from
  a state are obtained using method syntax::ta_t::next. It returns a range
  on which one can iterate to compute transitions (using method
  syntax::ta_t::transition) or next state (using method syntax::ta_t::next).

  Tuples of locations and layouts are cached and shared by the states computed
  by the timed automaton.
*/

/*!
  \namespace syntax
  \brief Syntax of timed automata
*/
namespace syntax {

  // States

  /*!
    \class state_t
    \brief State of a timed automaton

    A state contains a tuple of locations and a layout. The tuple of locations
    and the layout are cached and shared among the states that have the same
    values. There is a one-to-one correspondance between pointers and values.
  */
  class state_t {
  public:
    /*!
      \brief Constructor
      \post this has been initialized with nullptr pointers
    */
    state_t();

    /*!
      \brief Constructor
      \param vloc : a pointer to a tuple of locations
      \param layout : a pointer to a layout
      \post this has been initialized with vloc and layout. It stores
      shared pointers vloc and layout.
    */
    state_t(sp_t<vloc_t const> & vloc, sp_t<layout_t const> & layout);

    /*!
      \brief Copy-constructor
      \param state : the state to copy from
      \post this has been initialized from state and both share the same
      pointers
    */
    state_t(state_t const & state);

    /*!
      \brief Destructor
      \post The stored pointers have not been freed.
    */
    ~state_t();

    /*!
      \brief Assignment operator
      \param state : the state to assign from
      \post this has been assigned state and both share the same pointers
    */
    state_t & operator = (state_t const & state);

    /*!
      \brief Accessor
      \return Pointer to vloc
    */
    vloc_t const * vloc() const;

    /*!
      \brief Accessor
      \return Pointer to layout
     */
    layout_t const * layout() const;

    /*!
      \brief Equality predicate
      \param s : state to check
      \return True if this and s have the same pointers, false otherwise
    */
    bool operator == (state_t const & s) const;    

    /*!
      \brief Hash function
      \return Hash code for this. Two states with the same pointers have the
      same hash code.
    */
    size_t hash() const;

    /*!
      \brief Predicate on whether time can elapse in the state
      \return True if there is not committed nor urgent location in the tuple
      of location in the state, false otherwise
     */
    bool time_can_elapse() const;

    /*!
      \brief Predicate on whether the state is accepting
      \param accepting_labels : set of labels that are accepting
      \return True is the state's labels contains accepting_labels, false
      otherwise
     */
    bool accepting(label_bitset_t const & accepting_labels) const;

    /*!
      \brief Status of state
      \return graph::STATE_STATUS_OK if vloc and layout pointers are not
      nullptr. Otherwise:
      graph::STATE_STATUS_NO_VLOC is set when vloc pointer is nullptr, and
      graph::STATE_STATUS_NO_LAYOUT is set when layout pointer is nullptr
     */
    unsigned status() const;

    /*!
      \brief Output function
      \param os : output stream
      \post The state has been output to os
    */
    void output(std::ostream & os) const;


    sp_t<vloc_t const> _vloc;      /*!< Shared pointer on tuple of locs */
    sp_t<layout_t const> _layout;  /*!< Shared pointer on layout */
  };



  /*!
    \brief Boost-compatible hash function on syntax::state_t
    \param s : state to hash
    \return Hash value of state s
   */
  size_t hash_value(syntax::state_t const & s);




  // Range of edges

  /*!
    \class ta_edge_range_t
    \brief Range of timed automaton edges
   */
  class ta_edge_range_t : public vedge_range_t {
  public:
    /*!
      \brief Constructor
      \param rp : a range of vedge_t
      \post this shares a pointer to rp
    */
    ta_edge_range_t(sp_t<vedge_range_t> const & rp);

    /*!
      \brief Copy constructor
      \param r : edge range to copy
      \post this and r points to the same shared range of vedge_t
    */
    ta_edge_range_t(ta_edge_range_t const & r);

    /*!
      \brief Destructor
    */
    virtual ~ta_edge_range_t();

    /*!
      \brief see range_t::first
      \post this points to the first vedge_t in pointed range
    */
    virtual void first();

    /*!
      \brief see range_t::current
      \return current vedge_t in pointed range
    */
    virtual vedge_t const & current();

    /*!
      \brief see range_t::advance
      \post this points to next vedge_t in pointed range
    */
    virtual void advance();

    /*!
      \brief see range_t::at_end
      \return True if pointed range is at end, false otherwise
    */
    virtual bool at_end();
  protected:
    sp_t<vedge_range_t> _rp; /*!< Pointed range of vedge_t */
  };




  // Timed automaton

  /*!
    \class ta_t
    \brief Timed automaton over a syntax::system_t

    The class maintains a cache of vloc_t and a cache of layout_t. It ensures
    that there is only one instance of each one of this object. That is, there
    is a one-to-one correspondance between pointers and datas.
  */
  class ta_t : public graph::ts_t<state_t, ta_edge_range_t> {
  public:
    /*!
      \brief Constructor
      \param system : underlying system
      \throw std::invalid_argument if system is not valid
    */
    ta_t(system_t const & system);

    /*!
      \brief Destructor
    */
    virtual ~ta_t();

    /*!
      \brief Accessor
      \return Underlying system
    */
    system_t const & system() const;
    
    /*!
      \brief Initial state computation (see ts_t::initial)
      \post s has been initialized to the initial state of timed automaton
      this. State s has status graph::STATE_STATUS_OK, except if the layout
      assertion does not hold, then s has status graph::STATE_STATUS_NO_LAYOUT.
    */
    virtual void initial(state_t & s);

    /*!
      \brief Next state computation (see ts_t::next)
      \pre vedge is enabled by the vloc in state s (checked by assertion)
      \post nexts is the successor state of s along edge vedge. State nexts has
      status graph::STATE_STATUS_OK if vedge is enabled from state s,
      otherwise, the status of nexts explains why vedge is disabled.
     */
    virtual void next(state_t const & s, vedge_t const & vedge,
		      state_t & nexts);

    /*!
      \brief Outgoing edges computation
     */
    virtual ta_edge_range_t outgoing_edges(state_t const & s);

    /*!
      \brief Transforms into a timed automaton where edges are iterated in
      a random order by edge ranges.
     */
    void make_random_edges();

    /*!
      \brief Outputs stats
      \param level : stats level
      \post Size and approximate memory footprint of internal caches, included
      cached data, has been output to std::cout (level >= 2)
     */
    void stats(unsigned level);
  private:
    /*!< Underlying system */
    system_t const & _system;

    /*!< Cache of vlocs */
    cache_t< sp_t<vloc_t const>,
	     sp_t<vloc_t const>::delegate_hash,
	     sp_t<vloc_t const>::delegate_equal_to > _vloc_cache;

    /*!< Cache of layouts */
    cache_t< sp_t<layout_t const>,
	     sp_t<layout_t const>::delegate_hash,
	     sp_t<layout_t const>::delegate_equal_to > _layout_cache;    

    /*!< Randomize outgoing edges */
    bool _randomize_edges;


    /*!
      \brief Computes next vloc wrt vedge
      \param vloc : source vloc
      \param vedge : synchronized edges
      \return Successor of vloc along vedge.
      \pre vedge is enabled from vloc
     */
    sp_t<vloc_t const> next_vloc(vloc_t const & vloc, vedge_t const & vedge);
				 

    /*!
      \brief Computes next layout wrt vedge
      \param layout : source layout
      \param tgt_vloc : vloc in target state
      \param vedge : synchronized edges
      \return Successor of layout along vedge if enabled (wrt to guards in
      vedge and assertions in tgt_vloc), nullptr otherwise.
    */
    sp_t<layout_t const> next_layout(layout_t const & layout,
				     vloc_t const & tgt_vloc,
				     vedge_t const & vedge);
    
    /*!
      \brief Checks if a vedge is enabled from a vloc
      \param vloc : tuple of locations to be checked
      \param vedge : synchronized edges to be checked
      \return True if for each process involved in vedge, the source location
      of the process correspond to the location for this process in vloc,
      false otherwise
     */
    bool is_enabled(vloc_t const & vloc, vedge_t const & vedge);
  };

} // end of name space syntax


#endif // __TCHECKER_TA_HH__

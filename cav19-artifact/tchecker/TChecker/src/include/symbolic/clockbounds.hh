#ifndef __TCHECKER_CLOCKBOUNDS_HH__
#define __TCHECKER_CLOCKBOUNDS_HH__

#include <ostream>

#include <base/inttypes.h> // from UPPAAL DBM library
#include <dbm/constraints.h>

#include "base/clockindex.hh"
#include "base/global.hh"
#include "symbolic/constraints.hh"

/*!
  \file clock_bounds.hh
  \brief Representation of clock bounds

  A clock bound is a function that maps each clock to a non-negative
  integer or -infinity. The meaning of a bound B on clock x is that
  the value of x is relevant up to B. Clock bounds have been
  introduced in: Alur and Dill, A theory of Timed Automata, TCS,
  126(2), pp. 183-235, 1994.
*/

#define ABS(x) ((x) >= 0 ? (x) : -(x))
#define MAX(x,y) ((x) >= (y) ? (x) : (y))


/*!
  \namespace symbolic
  \brief Symbolic tools for clock valuations
*/
namespace symbolic {

  /*!
    \class clock_bounds_t
    \brief Representation of a function that associates a bound to each clock.
    Inactive clocks have bound M_INFINITY. Bounds must be non-negative.
    
    Any modification to the index used for creating a clock_bounds_t will
    invalidate the bounds
  */
  class clock_bounds_t {
  public:
    static const int32_t M_INFINITY = -dbm_INFINITY; /*!< Inactive clocks */
    
    /*!
      \brief Constructor
      \param index : domain of the bound function. Taken as the global clock
      index by default.
      \post All bounds set to M_INFINITY except clock 0 which has bound 0
    */
    clock_bounds_t(clock_index_t const & index =
        global_t::instance().clock_index());
    
    /*!
      \brief Copy constructor
      \param bounds : the bounds to build from
      \post The instance has been initialized to bounds
    */
    clock_bounds_t(clock_bounds_t const & bounds);
    
    /*!
      \brief Assignement operator
      \param bounds : clock bounds to assign from
    */
    clock_bounds_t & operator = (clock_bounds_t const & bounds);
    
    /*!
      \brief Destructor
    */
    ~clock_bounds_t();
    
    /*!
      \brief Clears all bounds
      \post All bounds set to M_INFINITY except clock 0 which has bound 0
    */
    void clear();

    /*!
      \brief Clear bound for some clock
      \param i : clock to clear (identifier)
      \pre i is a valid clock identifier (checked by assertion)
      \post The bound for clock i has been cleared
    */
    void clear(clock_id_t i);
    
    /*!
      \brief Access to bounds array
      \return An array representation of the bound function indexed according to
      the clock index given at (copy-)construction
    */
    inline int32_t const * operator() () const {
      return _bounds;
    }
    
    /*!
      \brief Access to bound for clock i
      \param i : the id of the clock
      \return The bound associated to clock i
      \pre i is a valid clock identifier (checked by assertion)
    */
    inline int32_t operator[] (clock_id_t i) const {
      assert(i < _size);
      return _bounds[i];
    }
    
    /*!
      \brief Mutable access to bound for clock i
      \param i : the id of the clock
      \return A reference on bound associated to clock i
      \pre i is a valid clock identifier (checked by assertion)
    */
    inline int32_t & operator[] (clock_id_t i) {
      assert(i < _size);
      return _bounds[i];
    }
    
    /*!
      \brief Equality predicate
      \param bounds : the bounds to compare
      \return True if equal to bounds, false otherwise
      \pre this and bounds have the same size
      \throw std::invalid_argument : when sizes differ
    */
    bool operator == (clock_bounds_t const & bounds) const;
    
    /*!
      \brief Disequality predicate
      \param bounds : the bounds to compare
      \return True if different from bounds, false otherwise
      \pre this and bounds have the same size
      \throw std::invalid_argument : when sizes differ
    */
    bool operator != (clock_bounds_t const & bounds) const;
    
    /*!
      \brief Pointwise less-or-equal-to predicate
      \param bounds : the bounds to compare
      \return True if leq to bounds for all clocks, false otherwise
      \pre this and bounds have the same size
      \throw std::invalid_argument : when sizes differ
    */
    bool operator <= (clock_bounds_t const & bounds) const;
    
    /*!
      \brief Maximizes bounds
      \param bounds : the bounds to compare
      \pre All clock bounds are non-negative, this and bounds have the same size
      \post The bound for each clock is the maximum among pre value and bounds
      value
      \throw std::invalid_argument : when sizes differ
    */
    void max(clock_bounds_t const & bounds);

    /*!
      \brief Maximizes and tracks modified bounds
      \tparam CLOCK_SET : type of clock set
      \param bounds : the bounds to compare
      \param modified : set of clocks with modified bounds
      \param accumulate : whether modified should only be expanded or not
      \pre All clock bounds are non-negative, this and bounds have the same size
      and have been built with same clock index as modified (not checked)
      \post The bound for each clock is the maximum among pre value and bounds
      value and all clocks with a modified bound have been added to modified.
      If accumulate is false, modified has been first emptied.
      \throw std::invalid_argument : when sizes differ
    */
    template <class CLOCK_SET>
    void max(clock_bounds_t const & bounds, CLOCK_SET & modified,
             bool accumulate = false) {
      if (_size != bounds._size)
        throw std::invalid_argument("*** clock_bounds_t::max: bad size");

      if (! accumulate)
        modified.clear();

      for (clock_id_t i = 1; i < _size; ++i) {
          if (bounds._bounds[i] > _bounds[i]) {
              _bounds[i] = bounds._bounds[i];
              modified.add(i);
            }
        }
      _bounds[0] = 0; // must be invariant
    }

    /*!
      \brief Copies and tracks modified bounds
      \tparam CLOCK_SET : type of clock set
      \param bounds : the bounds to copy from
      \param modified : set of clocks with modified bounds
      \param accumulate : whether modified should only be expanded or not
      \pre this and bounds have same size. They have been built with same clock
      index as modified (not checked)
      \post bounds has been copied to this and all clocks with a modified
      bound have been added to modified. If accumulate is false, modified has
      been first emptied
      \throw std::invalid_argument : when sizes differ
     */
    template <class CLOCK_SET>
    void copy(clock_bounds_t const & bounds, CLOCK_SET & modified,
              bool accumulate = false) {
      if (_size != bounds._size)
        throw std::invalid_argument("*** clock_bounds_t::copy: bad size");

      modified.clear();

      for (clock_id_t i = 1; i < _size; ++i) {
          if (bounds._bounds[i] != _bounds[i])
            modified.add(i);
          _bounds[i] = bounds._bounds[i];
        }
      _bounds[0] = 0; // must be invariant
    }
    
    /*!
      \brief Output the bounds
      \param output : where to output
      \param index : domain of the bound function. Taken as the global clock
      index by default.
      \post The bounds have been output to output
    */
    void output(std::ostream & output,
                clock_index_t const & index =
        global_t::instance().clock_index()) const;

    /*!
      \brief Accessor to memory usage
      \return The memory used by this
     */
    std::size_t memsize() const;
  private:
    int32_t * _bounds;  /*!< Array of clock bounds */
    size_t _size;       /*!< Size of _bounds */
  };


  /*!
    \brief Computes clocks maximal bounds from a constraint collection
    \tparam CLOCK_BOUNDS: type of clock bounds
    \param cc : constraint collection to consider
    \param M : clocks bounds
    \param accumulate : whether input value of M should be considered or not
    \pre All clock identifiers in the collection must be valid wrt clock index
    used to build M. The collection should not contain diagonal constraints.
    \post If accumulate is true, M associates to each clock x the maximum
    between input M[x] and the (absolute value of the) maximal constant x is
    compared to in cc. If accumulate is false, M is cleared before computation
    \throw std::runtime_error : when the collection contains a diagonal
    constraint
  */
  template <class CLOCK_BOUNDS>
  void max_bounds(symbolic::constraint_collection_t const & cc,
                  CLOCK_BOUNDS & M, bool accumulate = false) {
    int32_t bound;
    
    if (! accumulate)
      M.clear();

    for (symbolic::constraint_t const & c : cc) {
        // Checks no diagonal constraints
        if ( (c.i != 0) && (c.j != 0) )
          throw std::runtime_error("*** symbolic::max_bounds: "
                                   "diagonal constraint");

        // Sets the bound
        bound = ABS( dbm_raw2bound(c.value) );
        if (c.i != 0)
          M[c.i] = MAX( M[c.i], bound );
        if (c.j != 0)
          M[c.j] = MAX( M[c.j], bound );
      }
  }


  /*!
    \brief Computes clocks maximal bounds from a constraint collection
    \tparam CLOCK_BOUNDS: type of clock bounds
    \tparam CLOCK_SET : type of clock set
    \param cc : constraint collection to consider
    \param M : clocks bounds
    \param modified : set of clocks with modified bound
    \param accumulate : whether input values of M and modified should be
    considered or not
    \pre All clock identifiers in the collection must be valid wrt clock index
    used to build M and modified. The collection should not contain diagonal
    constraints.
    \post If accumulate is true, M associates to each clock x the maximum
    between input M[x] and the (absolute value of the) maximal constant x is
    compared to in cc; all clocks with modified bound have been added to
    modified. If accumulate is false, M and modified are cleared before
    computation
    \throw std::runtime_error : when the collection contains a diagonal
    constraint
  */
  template <class CLOCK_BOUNDS, class CLOCK_SET>
  void max_bounds(symbolic::constraint_collection_t const & cc,
                  CLOCK_BOUNDS & M, CLOCK_SET & modified,
                  bool accumulate = false) {
    int32_t bound;
    
    if (! accumulate) {
        M.clear();
        modified.clear();
      }

    for (symbolic::constraint_t const & c : cc) {
        // Checks no diagonal constraints
        if ( (c.i != 0) && (c.j != 0) )
          throw std::runtime_error("*** symbolic::max_bounds: "
                                   "diagonal constraint");

        // Sets the bound
        bound = ABS( dbm_raw2bound(c.value) );
        if ( (c.i != 0) && (bound > M[c.i]) ) {
            M[c.i] = bound;
            modified.add(c.i);
          }
        if ( (c.j != 0) && (bound > M[c.j]) ) {
            M[c.j] = bound;
            modified.add(c.j);
          }
      }
  }


  /*!
    \brief Computes clocks maximal lower and upper bounds from a constraint
    collection
    \tparam CLOCK_BOUNDS: type of clock bounds
    \param cc : constraint collection to consider
    \param L : clocks lower bounds (i.e. x >= or x > c)
    \param U : clocks upper bounds (i.e. x <= or x < c)
    \param accumulate : whether input values of L and U should be considered
    or not
    \pre All clock identifiers in the collection must be valid wrt clock index
    used to build L and U. The collection should not contain diagonal
    constraints.
    \post If accumulate is true, L associates to each clock x the maximum
    between input L[x] and the (absolute value of the) maximal constant that
    lower bounds x (i.e. x >= c or x > c). Same for U with upper bounds (i.e.
    x <= c or x < c). If accumulate is false, L and U are cleared before
    computation
    \throw std::runtime_error : when the collection contains a diagonal
    constraint
  */
  template <class CLOCK_BOUNDS>
  void max_bounds(symbolic::constraint_collection_t const & cc,
                  CLOCK_BOUNDS & L, CLOCK_BOUNDS & U, bool accumulate = false) {
    int32_t bound;
    
    if (! accumulate) {
        L.clear();
        U.clear();
      }

    for (symbolic::constraint_t const & c : cc) {
        // Checks no diagonal constraints
        if ( (c.i != 0) && (c.j != 0) )
          throw std::runtime_error("*** symbolic::max_bounds: "
                                   "diagonal constraint");

        // Sets the bound
        bound = ABS( dbm_raw2bound(c.value) );
        if (c.i != 0)
          U[c.i] = MAX( U[c.i], bound );
        if (c.j != 0)
          L[c.j] = MAX( L[c.j], bound );
      }
  }


  /*!
    \brief Computes clocks maximal lower and upper bounds from a constraint
    collection
    \tparam CLOCK_BOUNDS: type of clock bounds
    \tparam CLOCK_SET : type of clock set
    \param cc : constraint collection to consider
    \param L : clocks lower bounds (i.e. x >= or x > c)
    \param U : clocks upper bounds (i.e. x <= or x < c)
    \param L_modified : set of clocks with modified L bound
    \param U_modified : set of clocks with modified U bound
    \param accumulate : whether input values of L, U, L_modified and U_modified
    should be considered or not
    \pre All clock identifiers in the collection must be valid wrt clock index
    used to build L, U, L_modified and U_modified. The collection should not
    contain diagonal constraints.
    \post If accumulate is true, L associates to each clock x the maximum
    between input L[x] and the (absolute value of the) maximal constant that
    lower bounds x (i.e. x >= c or x > c). All clocks with modified L bound
    have been added to L_modified. Same for U and U_modified with upper bounds
    (i.e. x <= c or x < c). If accumulate is false, L, U, L_modified and
    U_modified are cleared before computation
    \throw std::runtime_error : when the collection contains a diagonal
    constraint
  */
  template <class CLOCK_BOUNDS, class CLOCK_SET>
  void max_bounds(symbolic::constraint_collection_t const & cc,
                  CLOCK_BOUNDS & L, CLOCK_BOUNDS & U,
                  CLOCK_SET & L_modified, CLOCK_SET & U_modified,
                  bool accumulate = false) {
    int32_t bound;
    
    if (! accumulate) {
        L.clear();
        L_modified.clear();
        U.clear();
        U_modified.clear();
      }

    for (symbolic::constraint_t const & c : cc) {
        // Checks no diagonal constraints
        if ( (c.i != 0) && (c.j != 0) )
          throw std::runtime_error("*** symbolic::max_bounds: "
                                   "diagonal constraint");

        // Sets the bound
        bound = ABS( dbm_raw2bound(c.value) );
        if ( (c.i != 0) && (bound > U[c.i]) ) {
            U[c.i] = bound;
            U_modified.add(c.i);
          }
        if ( (c.j != 0) && (bound > L[c.j]) ) {
            L[c.j] = bound;
            L_modified.add(c.j);
          }
      }
  }

} // end of namespace symbolic

#endif // __TCHECKER_CLOCKBOUNDS_HH__

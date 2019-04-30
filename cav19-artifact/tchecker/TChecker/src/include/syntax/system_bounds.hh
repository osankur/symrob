#ifndef __TCHECKER_SYSTEM_BOUNDS_HH__
#define __TCHECKER_SYSTEM_BOUNDS_HH__

#include <boost/container/flat_map.hpp>

#include "symbolic/clockbounds.hh"
#include "syntax/system.hh"
#include "syntax/sync_product.hh"

/*!
  \file system_bounds.hh
  \brief Bounds on clock in a system

  Bounds on clocks are used by extrapolations to compute a finite
  abstraction of the semantics of a timed automaton and ensure
  termination of the algorithms.

  Clock bounds are functions that associate to each clock an
  non-negative integer value or -infinity (see
  symbolic::clock_bounds_t). Rougly speaking, a bound B for clock x
  means that the value of x is relevant up to value B.

  The class syntax::system_bounds_t below provides: global LU bounds,
  global M bounds, local LU bounds and local M bounds.

  LU bounds state relevance of clcok values by distinguishing between
  lower bounds (L) and upper bounds (U). A complete description can be
  found in: Behrmann, Bouyer, Larsen and Pelanek, Lower and upper
  bounds in zone-based abstractions of timed automata, STTT, 8(3),
  pp. 204-215, 2006.

  M bounds do not distinguish between lower and upper bounds. Hence
  they can be seen as the maximum of lower of upper bounds. However,
  they were introduced much before in: Alur and Dill, A theory of
  Timed Automata, TCS, 126(2), pp. 183-235, 1994.

  Finally, bounds can be computed globally for a system (or an
  automaton), or one can associate a bound to each state in the
  automaton, which we call local bounds. Global bounds have been the
  classical approach since the seminal paper of Alur and Dill (see
  above). The optimization using local bounds has been introduced in:
  Behrmann, Bouyer, Fleury and Larsen, Static guard analysis in timed
  automata verification, TACAS, LNCS, vol. 2619, pp. 254-270, 2003.
*/

namespace syntax {

  /*!
    \struct LU_bounds_t
    \brief Provides LU bounds
  */
  struct LU_bounds_t {
    symbolic::clock_bounds_t L, U; /*!< L and U clock bounds */

    /*!
      \brief Clears bounds for all clocks
      \post L and U have been cleared (see clock_bouds_t::clear)
    */
    void clear();

    /*!
      \brief Clears bounds for clock cid
      \pre cid is a clock identifier registed in the global clock index, and
      cid > 0 (assert)
      \post L[cid] and U[cid] have been cleared (see clock_bouds_t::clear)      
    */
    void clear(clock_id_t cid);

    /*!
      \brief Maximization operator
      \pre L and U have the same size as b.L and b.U (asserted in
      clock_bounds_t)
      \post For every clock x, L[x] := max(L[x], b.L[x]) and
      U[x] := max(U[x], b.U[x])
    */
    void max(LU_bounds_t const & b);

    /*!
      \brief Pointwise less-or-equal-to operator
      \pre b has the same size as instance (asserted in clock_bounds_t)
      \return True if both L and U are less or equal to b.L and b.U pointwise
    */
    bool operator <= (LU_bounds_t const & b) const;

    /*!
      \brief Accessor to memory usage
      \return The memory used by this
     */
    std::size_t memsize() const;
  };



  /*!
    \struct M_bounds_t
    \brief Provides M bounds
  */
  struct M_bounds_t {
    symbolic::clock_bounds_t M; /*!< M clock bounds */

    /*!
      \brief Clears bounds for all clocks
      \post L and U have been cleared (see clock_bouds_t::clear)
    */
    void clear();

    /*!
      \brief Clears bounds for clock cid
      \pre cid is a clock identifier registed in the global clock index, and
      cid > 0 (assert)
      \post L[cid] and U[cid] have been cleared (see clock_bouds_t::clear)      
    */
    void clear(clock_id_t cid);

    /*!
      \brief Maximization operator
      \pre b.L and b.U have the same size as M (asserted in clock_bounds_t)
      \post For every clock x, M[x] := max(M[x], b.L[x], b.U[x])
    */
    void max(LU_bounds_t const & b);

    /*!
      \brief Maximization operator
      \pre b.M has the same size as M (asserted in clock_bounds_t)
      \post For every clock x, M[x] := max(M[x], b.M[x])
    */
    void max(M_bounds_t const & b);

    /*!
      \brief Accessor to memory usage
      \return The memory used by this
     */
    std::size_t memsize() const;
  };



  /*!
    \class system_bounds_t
    \brief Provides global and local, LU and M, clock bounds
  */
  class system_bounds_t {
  public:
    /*!
      \brief Constructor
      \param system : system for which clock bounds have to be computed
    */
    system_bounds_t(system_t const & system);

    /*!
      \brief Destructor
    */
    ~system_bounds_t();

    /*!
      \brief Accessor
      \param b : return the bounds
      \post b stores the global LU clock bounds for the system given to the
      constructor
    */
    void global_LU(LU_bounds_t & b) const;

    /*!
      \brief Accessor
      \param b : return the bounds
      \post b stores the global M clock bounds for the system given to the
      constructor
    */
    void global_M(M_bounds_t & b) const;

    /*!
      \brief Accessor
      \param vloc : for which local clock bounds have to be computed
      \param b : return the bounds
      \pre vloc is a valid vector of location identifiers in the system given
      to the constructor
      \post b stores the LU clock bounds for vloc in the system given to the
      constructor
    */
    void local_LU(vloc_t const & vloc, LU_bounds_t & b) const;

    /*!
      \brief Accessor
      \param vloc : for which local clock bounds have to be computed
      \param b : return the bounds
      \pre vloc is a valid vector of location identifiers in the system given
      to the constructor
      \post b stores the M clock bounds for vloc in the system given to the
      constructor
    */
    void local_M(vloc_t const & vloc, M_bounds_t & b) const;

    /*!
      \brief Accessor to memory usage
      \return Approximate memory usage of this
     */
    std::size_t memsize() const;
  private:
    /*!< global LU bounds */
    LU_bounds_t _global_LU;

    /*!< local LU bounds */
    boost::container::flat_map<loc_t const *,
			       LU_bounds_t> _local_LU; 

    /*!
      \brief Computes the local LU bounds for each location in system
      \post _local_LU contains the LU clock bounds for every location in
      system
    */
    void compute_local_LU(system_t const & system);
  };

} // end of namespace syntax

#endif // __TCHECKER_SYSTEM_BOUNDS_HH__

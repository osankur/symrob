#ifndef __TCHECKER_DBM_UTILS_HH__
#define __TCHECKER_DBM_UTILS_HH__

#include <dbm/constraints.h>
#include <dbm/dbm.h>

#include "base/clockindex.hh"
#include "base/clockset.hh"
#include "symbolic/clockbounds.hh"
#include "symbolic/constraints.hh"

/*!
  \file dbm_utils.hh
  \brief Utility function on DBMs
*/

namespace symbolic {

  /*!
    \brief Initializes a DBM to the universal zone
    \param dim : dimension of the DBM
    \return a DBM that represents the universal zone in dimension dim
    \pre dim includes the fake clock 0, hence must be at least 1
    \throw std::invalid_argument: if size is less than 1
  */
  raw_t * dbm_initialize(size_t dim);

  /*!
    \brief Initializes a DBM to the conjunction of constraints in collection
    \param dim : dimension of the DBM
    \param collection : constraint collection to initialize to
    \return a DBM that represents the zone in dimension dim, defined by the
    conjunction of constraints in collection. The returned pointer is nullptr
    if collection is inconsistent
    \pre dim includes the fake clock 0, hence must be at least 1
    \throw std::invalid_argument: if size is less than 1
  */
  raw_t * dbm_initialize(size_t dim,
                         constraint_collection_t const & collection);

  /*!
    \brief Return a minimal interpolant of z1,z2
    \param z1, z2 : the DBMs we compare (empty if nullptr)
    \param dim : dimension of DBMs and bounds
    \return a constraint collection such that every valuation in z2 respect these constraints and no valuation z1 respect them..
    \pre z1 and z2 are disjointed
  */
  
  constraint_collection_t dbm_interpolant(raw_t const * z1, raw_t const * z2, size_t dim);
  
  /*!
    \brief Checks if aLU(z1) contains z2.
    
    The test consists in checking if there exists two clock x and y s.t.
    z2[0x] >= (<=,-Ux)  &&  z1[yx] < z2[yx]  &&  z1[yx] + (<,-Ly) < z2[0x]
    
    \param z1, z2 : the DBMs we compare (empty if nullptr)
    \param dim : dimension of DBMs and bounds
    \param L : the lower bounds
    \param U : the upper bounds
    \return True if aLU(z1) contains z2 wrt L and U, false otherwise
    \pre The z1, z2, L and U have been built using the same clock index of
    dimension dim. z1 and z2 are tight (checked by assertion)
  */
  bool dbm_aLU_contains(raw_t const * z1, raw_t const * z2, size_t dim,
                        clock_bounds_t const & L, clock_bounds_t const & U);

  /*!
    \brief Checks if Closure(z1) contains z2.
    \param z1, z2 : the DBMs we compare (empty if nullptr)
    \param dim : dimension of DBMs and bounds
    \param M : the clock bounds
    \return True if Closure(z1) contains z2 wrt M, false otherwise
    \pre The z1, z2 and M have been built using the same clock index of
    dimension dim. z1 and z2 are tight (checked by assertion)
  */
  bool dbm_closure_contains(raw_t const * z1, raw_t const * z2, size_t dim,
                            clock_bounds_t const & M);

  /*!
    \brief Constrains a zone
    \param z : DBM to constraint
    \param dim : dimension of DBM z
    \param c : constraint
    \return True if z constrained with c is not empty, false otherwise
    \pre z and c have been built from the same clock index. z is tight
    (checked by assertion)
    \post z has been constrained with constraint c, and z is tight (if not
    empty)
  */
  bool dbm_constrain(raw_t * z, size_t dim, symbolic::constraint_t const & c);

  /*!
    \brief Constrains a zone with a constraint collection
    \param z : DBM to constraint
    \param dim : dimension of DBM z
    \param cc : constraint collection to constrain the DBM
    \return True if z constrained with cc is not empty, false otherwise
    \pre z and cc have been built from the same clock index. z is tight
    (checked by assertion)
    \post z has been constrained with all constraints in cc, and z is tight
    (if not empty)
  */
  bool dbm_constrain(raw_t * z, size_t dim,
                     constraint_collection_t const & cc);

  /*!
    \brief Reset clocks
    \param z : DBM to update
    \param dim : dimension of DBM z
    \param clocks : set of clocks to reset
    \pre z and clocks have been built from the same clock index. z is tight
    (checked by assertion)
    \post z has been updated by reseting the clocks in clocks, and z is tight
  */
  void dbm_reset(raw_t * z, size_t dim, clocks_t const & clocks);

  bool dbm_constrainreset(raw_t * z, size_t dim, clocks_t const & clocks);

  void dbm_free(raw_t * z, size_t dim, clocks_t const & clocks);
  /*!
    \brief Checks if a zone satisfies a constraint
    \param z : DBM to test
    \param dim : dimension of DBM z
    \param c : constraint to test
    \return True if z satisfies c, false otherwise
    \pre z if tight (checked by assertion)
   */
  bool dbm_satisfies(raw_t const * z, size_t dim,
                     symbolic::constraint_t const & c);

  /*!
    \brief Checks if a zone is consistent with a constraint
    \param z : DBM to test
    \param dim : dimension of DBM z
    \param c : constraint to test
    \return True if z contains a valuation that satisfies c (i.e. z is
    consistent with c), false otherwise
    \pre z is tight (checked by assertion)
   */
  bool dbm_consistent(raw_t const * z, size_t dim,
                      symbolic::constraint_t const & c);

  /*!
    \brief Sets a zone to empty
    \param z : DBM to empty
    \param dim : dimension of DBM z
    \post z has been emptied by setting x0-x0 < 0
   */
  void dbm_empty(raw_t * z, size_t dim);

  /*!
    \brief Sets a zone to universal
    \param z : DBM to make universal
    \param dim : dimension of DBM z
    \post z is the universal zone of dimension dim
   */
  void dbm_universal(raw_t * z, size_t dim);

  /*!
    \brief Checks if a zone is universal
    \param z: DBM to check (empty if nullptr pointer)
    \param dim : dimension of DBM z
    \return True if z is universal, false otherwise
    \pre z is tight (checked by assertion)
   */
  bool dbm_is_universal(raw_t const * z, size_t dim);


  // Hash code on DBMs

  /*!
    \brief DBM flags
   */
  enum dbm_flags_t {
    DBM_EMPTY,       /*!< Empty DBM */
    DBM_UNIVERSAL,   /*!< Universal DBM */
    DBM_OTHER        /*!< non-empty non-universal DBM */
  };

  /*!
    \brief Hash code of empty DBM
    \return Hash code arbitrarily associated to empty DBM
   */
  inline std::size_t dbm_empty_hash() {
    return global_t::instance().hash_seed();
  }
  
  /*!
    \brief Hash code of universal DBM
    \param dim : dimension of DBM
    \return Hash code of universal DBM of dimension dim
   */
  inline std::size_t dbm_universal_hash(cindex_t dim) {
    std::size_t seed = global_t::instance().hash_seed();
    for (cindex_t x = 0; x < dim; ++x)
      for (cindex_t y = 0; y < dim; ++y)
        boost::hash_combine(seed, ( (x==0) || (x==y)
                                    ? dbm_LE_ZERO
                                    : dbm_LS_INFINITY) );
    return seed;
  }

  /*!
    \brief Computes the hash code of a zone
    \param z : DBM to hash (empty if nullptr)
    \param dim : dimension of DBM z
    \param flags : informative flags on z (set duting call)
    \return The hash code of DBM z.
    \pre z==nullptr (interpreted as empty), or dbm_isEmpty(z, dim) or
    dbm_isClosed(z, dim) (checked by assertion)
    \post flags has been set to DBM_EMPTY if z is the empty zone
    (i.e. z is nullptr or dbm_isEmpty(z,dim) would return TRUE). flags has been
    set to DBM_UNIVERSAL if z is the universal zone (dbm_is_universal(z, dim)
    would return true). Otherwise, flags has been set to DBM_OTHER.
   */
  std::size_t dbm_hash(raw_t const * z, size_t dim, dbm_flags_t & flags);

} // end of namespace symbolic

#endif // __TCHECKER_DBM_UTILS_HH__

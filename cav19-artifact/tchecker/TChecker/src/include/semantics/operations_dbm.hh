#ifndef __TCHECKER_OPERATIONS_DBM_HH__
#define __TCHECKER_OPERATIONS_DBM_HH__

#include "symbolic/dbm_utils.hh"
#include "syntax/model.hh"
#include "syntax/ta.hh"

/*!
  \file operations_dbm.hh
  \brief Basic operations needed to compute operational semantics (see
  operational.hh and operational_dbm.hh)
*/

namespace semantics {

  /*!
    \class operations_dbm_t
    \brief Basic operations needed to compute the operational semantics of a
    model using DBMs as a symbolic representation for zones

    These basic operations are:
    - on_zero_valuation: DBM where all clocks have value zero
    - on_time_elapse: time-elapse of a DBM
    - on_inv: apply the invariant in a state to a DBM
    - on_guard: apply the guard on a transition to a DBM
    - on_reset: apply the reset on a transition to a DBM

    \tparam DATA : type of extra data needed by semantics
  */
  template <class DATA>
  class operations_dbm_t {
  public:
    /*!
      \brief Type of data
    */
    typedef DATA data_t;

    /*!
      \brief Constructor
      \param model : model (i.e. timed automaton) for which operations
      are defined
    */
    operations_dbm_t(syntax::model_t & model) : _model(model) {
    }

    /*!
      \brief Destructor
    */
    virtual ~operations_dbm_t() = default;

    /*!
      \brief Accessor
      \return Underlying model
    */
    syntax::model_t & model() {
      return _model;
    }

    /*!
      \brief Computes the valuation where all the clocks have value 0
      \param z : zone (DBM)
      \param dim : dimension of z
      \param d : extra data
      \return True
      \pre z is an allocated raw_t[dim * dim], and dim >= 1
      \post z maps every clock to 0. z is tight. d has not been modified.
    */
    virtual bool on_zero_valuation(raw_t * z, cindex_t dim, DATA d) {
      assert( z != nullptr );

      dbm_zero(z, dim);
      return true;
    }

    /*!
      \brief Time elapse of all the valuations in a zone
      \param s : state
      \param z : zone (DBM)
      \param dim : dimension of z
      \param d : extra data
      \return True
      \pre z is an allocated raw_t[dim * dim]. z is tight (checked by
      assertion). dim >= 1
      \post z has been opened up if time elapse is allowed in s, and z has
      been left unchanged otherwise. z is tight. d has not been modified.
    */
    virtual bool on_time_elapse(syntax::state_t const & s,
                                raw_t * z, cindex_t dim, DATA d) {
      assert( z != nullptr );
      assert( dbm_isClosed(z, dim) == TRUE );

      if (s.time_can_elapse()) // Time elapse, if allowed
        dbm_up(z, dim);

      return true;
    }
    virtual bool on_time_down(syntax::state_t const & s,
                              raw_t * z, cindex_t dim, DATA d) {
      assert( z != nullptr );
      assert( dbm_isClosed(z, dim) == TRUE );

      if (s.time_can_elapse()) // Time elapse, if allowed
        dbm_down(z, dim);

      return true;
    }
    /*!
      \brief Application of the invariant in a state
      \param s : state
      \param z : zone (DBM)
      \param dim : dimension of z
      \param d : extra data
      \return True if it yields a non-empty zone, false otherwise
      \pre z is an allocated raw_t[dim * dim]. z is tight (checked by
      assertion). dim >= 1
      \post z has been constrained by the invariant in state s. z is tight
      if not empty. d has not been modified.
    */
    virtual bool on_inv(syntax::state_t const & s, raw_t * z, cindex_t dim,
                        DATA d) {
      assert( z != nullptr );
      assert( dbm_isClosed(z, dim) == TRUE );

      syntax::vloc_t const * vloc = s.vloc();
      for (syntax::loc_t const * loc : *vloc)
        if ( ! symbolic::dbm_constrain(z, dim, loc->inv()) )
          return false;
      
      return true;
    }

    /*!
      \brief Application of the guard on a transition
      \param vedge : tuple of synchronized edges
      \param z : zone (DBM)
      \param dim : dimension of z
      \param d : extra data
      \return True if it yields a non-empty zone, false otherwise
      \pre z is an allocated raw_t[dim * dim]. z is tight (checked by
      assertion). dim >= 1
      \post z has been constrained by the guard on transition vedge. z is
      tight if not empty. d has not been modified.
    */
    virtual bool on_guard(syntax::vedge_t const & vedge, raw_t * z,
                          cindex_t dim, DATA d) {
      assert( z != nullptr );
      assert( dbm_isClosed(z, dim) == TRUE );

      for (syntax::edge_t const * edge : vedge)
        if ( ! symbolic::dbm_constrain(z, dim, edge->guard()) )
          return false;
      
      return true;
    }
    virtual bool on_backreset(syntax::vedge_t const & vedge, raw_t * z,
                              cindex_t dim, DATA d) {
      assert( z != nullptr );
      assert( dbm_isClosed(z, dim) == TRUE );

      for (syntax::edge_t const * edge : vedge)
        if ( ! symbolic::dbm_constrainreset(z, dim, edge->reset()) )
          return false;
      for (syntax::edge_t const * edge : vedge)
        symbolic::dbm_free(z, dim, edge->reset());
      return true;
    }
    
    /*!
      \brief Application of the reset on a transition
      \param vedge : tuple of synchronized edges
      \param z : zone (DBM)
      \param dim : dimension of z
      \param d : extra data
      \return True
      \pre z is an allocated raw_t[dim * dim]. z is tight (checked by
      assertion). dim >= 1
      \post z has been applied the reset from transition vedge. z is tight.
      d has not been modified.
    */
    virtual bool on_reset(syntax::vedge_t const & vedge, raw_t * z,
                          cindex_t dim, DATA d) {
      assert( z != nullptr );
      assert( dbm_isClosed(z, dim) == TRUE );

      for (syntax::edge_t const * edge : vedge)
        symbolic::dbm_reset(z, dim, edge->reset());
      
      return true;
    }
  protected:
    syntax::model_t & _model;  /*!< Underlying model */
  };

} // end of namespace semantics

#endif // __TCHECKER_OPERATIONS_DBM_HH__

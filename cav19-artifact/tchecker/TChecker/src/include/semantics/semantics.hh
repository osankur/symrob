#ifndef __TCHECKER_SEMANTICS_HH__
#define __TCHECKER_SEMANTICS_HH__

#include "graph/ts.hh"
#include "syntax/model.hh"
#include "symbolic/zone.hh"

/*!
  \file semantics.hh
  \brief Definitions shared by several semantics
*/

/*!
  \namespace semantics
  \brief Semantics of models (see syntax::model_t)
*/
namespace semantics {

  /*!
    \class semantics_t
    \brief Semantics of a timed automaton
    \tparam STATE : type of states. It must derive from syntax::state_t
    \tparam EDGE_RANGE : type of range over edges.
  */
  template <class STATE, class EDGE_RANGE>
  class semantics_t : public graph::ts_t<STATE, EDGE_RANGE> {
  public:
    /*!
      \brief Constructor
      \param model : underlying model
      \post this can produce the semantics of model
    */
    semantics_t(syntax::model_t & model) : _model(model) {
    }

    /*!
      \brief Destructor
    */
    virtual ~semantics_t() = default;

    /*!
      \brief Accessor
      \return Underlying model
    */
    syntax::model_t const & model() const {
      return _model;
    }

    /*!
      \brief Initial state computation (see graph::ts_t::initial)
      \post s has been set to the initial state of the semantics.
    */
    virtual void initial(STATE & s) {
      _model.ta().initial(s);
      _initial(s);
    }

    /*!
      \brief Outputs stats
      \param level : stats level
      \post does not do anything
     */
    virtual void stats(unsigned level) const {
    }

    virtual void pre(STATE const & s, raw_t * z, typename EDGE_RANGE::reference e,
                     STATE const & nexts) = 0;
  protected:
    /*!
      \brief Initial state computation
      \post The datas in s (except those from syntax::state_t) have been
      initialized
     */
    virtual void _initial(STATE & s) = 0;

    syntax::model_t & _model;  /*!< Underlying model */
  };



  /*!
    \brief Setup flags for semantics. Defined as a bit-or combination of flags,
    one from each group
  */
  typedef char sem_flags_t;

  // bit 0 sets operational semantics (lazyinv on/off)
  const sem_flags_t SEM_EL         = 0;  /*!< Elapsed-last */
  const sem_flags_t SEM_EL_LAZYINV = 1;  /*!< E.-last + lazy invariant */

  const sem_flags_t SEM_MASK_OPERATIONAL = 1; /*!< Operational bit mask */

  // bit 1-3 set extrapolation
  const sem_flags_t SEM_EX_NO      = 0;  /*!< No extrapolation */
  const sem_flags_t SEM_EXLUG      = 2;  /*!< ExtraLU+,global */
  const sem_flags_t SEM_EXLUL      = 4;  /*!< ExtraLU+,local */
  const sem_flags_t SEM_EXMG       = 6;  /*!< ExtraM+, global */
  const sem_flags_t SEM_EXML       = 8;  /*!< ExtraM+, local */

  const sem_flags_t SEM_MASK_EXTRAPOLATION = 14; /*!< Extrapolation bits mask */
  
  // bit 4-5 sets DBM vs mingraph
  const sem_flags_t SEM_DBM        = 0;  /*!< Zones as DBMs */
  const sem_flags_t SEM_SHDBM      = 16; /*!< Zones as shared DBMs */
  const sem_flags_t SEM_MG         = 32; /*!< Zones as min graphs */

  const sem_flags_t SEM_MASK_ZONE = 48;  /*!< Zone bit mask */
  
  /*!< Default semantics (Elapsed-last + ExtraLU+,local + DBMs) */
  const sem_flags_t SEM_DEFAULT    = SEM_EL | SEM_EXLUL | SEM_DBM;

} // end of namespace semantics

#endif // __TCHECKER_SEMANTICS_HH__

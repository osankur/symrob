#ifndef __TCHECKER_MODEL_HH__
#define __TCHECKER_MODEL_HH__

#include "base/singleton.hh"
#include "syntax/system.hh"
#include "syntax/system_bounds.hh"
#include "syntax/system_builder.hh"
#include "syntax/ta.hh"

/*!
  \file model.hh
  \brief Description of a model
*/

namespace syntax {

  /*!
    \brief Setup flags for models
  */
  typedef char model_flags_t;

  const model_flags_t MODEL_NORMAL       = 0;   /*!< Normal model */
  const model_flags_t MODEL_SNZ          = 1;   /*!< SNZ model */
  const model_flags_t MODEL_RANDOM_EDGES = 2;   /*!< Randomize edges */


  /*!
    \class model_t
    \brief Description of a model. A model contains all the information needed
    to analyse a system of synchronized timed processes. It is made of:
    - a syntax::system_t instance that described a system of synchronized
    timed processes
    - a syntax::system_bounds_t instance that provides the clock bounds for
    the system
    - a syntax::ta_t instance that describes the timed automaton corresponding
    to the system of synchronized timed processes
  */
  class model_t {
  public:
    /*!
      \brief Constructor
      \param system_builder : to build the model
      \post A model of type MODEL_NORMAL has been built calling system_builder
    */
    model_t(system_builder_t & system_builder);

    /*!
      \brief Constructor
      \param system_builder : to build the model
      \param accepting_labels : accepting labels
      \param flags : kind of system to build
      \post A model of type requested by flag has been built calling
      system_builder. The system builder may add labels that algorithms must
      consider accepting for correctness. All such labels have been added to
      accepting_labels.
    */
    model_t(system_builder_t & system_builder,
	    labels_t & accepting_labels,
	    model_flags_t flags = MODEL_NORMAL);

    /*!
      \brief Destructor
     */
    ~model_t();

    /*!
      \brief Accessor
      \return The own system
    */
    system_t const & system();

    /*!
      \brief Accessor
      \return The system bounds for the own system
    */
    system_bounds_t const & system_bounds();

    /*!
      \brief Accessor
      \return The timed automaton for the own system
    */
    ta_t & ta();

    /*!
      \brief Outputs stats
      \param level : stats level
      \post Stats of underlying system, system bounds and timed automaton have
      been output to std::cout
    */
    void stats(unsigned level) const;
  protected:
    /* IMPLEMENTATION NOTE: stored as pointers to allow calling methods
       on _system before building the other two (see constructors)
    */
    system_t * _system;               /*!< System */
    system_bounds_t * _system_bounds; /*!< System bounds */
    ta_t * _ta;                       /*!< Timed automaton */
  };


  
  /*!
    \class model_factory_t
    \brief Factory of models
  */
  class model_factory_t : public singleton_t<model_factory_t> {

    friend class singleton_t<model_factory_t>; // Grants access to cons/Des
    
  public:
    /*!
      \brief Builds a new model
      \param system_builder : to build the model
      \return A pointer to the new model of type MODEL_NORMAL
      built from system_builder
    */
    model_t * new_model(system_builder_t & system_builder);

    /*!
      \brief Builds a new model
      \param system_builder : to build the model
      \param accepting_labels : labels that are accepting in the model (see
      syntax::model_t)
      \param flags : type of model to build
      \return A pointer to the new model of type required by flags,
      built from system_builder
    */
    model_t * new_model(system_builder_t & system_builder,
			labels_t & accepting_labels,
			model_flags_t flags = MODEL_NORMAL);
  private:
    /*!
      \brief Constructor (made private)
    */
    model_factory_t();

    /*!
      \brief Destructor (made private)
    */
    ~model_factory_t();
  };

} // end of namespace syntax

#endif // __TCHECKER_MODEL_HH__

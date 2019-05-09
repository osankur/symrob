#ifndef __TCHECKER_ALGORITHMS_HH__
#define __TCHECKER_ALGORITHMS_HH__

#include "algorithms/algorithms-options.hh"
#include "base/labelset.hh"
#include "graph/graphoutput.hh"
#include "graph/pw.hh"
#include "semantics/gzg.hh"
#include "semantics/semantics.hh"
#include "semantics/zg.hh"
#include "syntax/model.hh"
#include "syntax/system_builder.hh"


/*!
  \namespace algorithms
  \brief Algorithms for timed systems
*/
namespace algorithms {

  /* Owners */

  /*!
    \class graph_output_owner_t
    \brief Graph output owner
  */
  class graph_output_owner_t {
  public:
    /*!
      \brief Constructor
      \param os : output stream
      \param flags : type of graph output to build
      \post A graph output has been built with type requested by flags and
      output stream os
     */
    graph_output_owner_t(std::ostream & os,
                         graph::output_flags_t flags = graph::OUTPUT_DEFAULT);

    /*!
      \brief Destructor
    */
    ~graph_output_owner_t();
  protected:
    /*!< Graph output */
    graph::output_t * _go;
  };




  /* Algorithms */


  /*!
    \class model_algorithm_t
    \brief Algorithm on timed automaton (model)
   */
  class model_algorithm_t {
  public:
    /*!
      \brief Constructor
      \param system_builder : builds underlying system
      \param accepting_labels : labels that are accepting in the model
      \param flags : type of model to build
      \post Provides a model of type requested by flags and built by
      system_builder. The system builder may add labels that algorithms must
      consider accepting for correctness. All such labels have been added to
      accepting_labels.
    */
    model_algorithm_t(syntax::system_builder_t & system_builder,
                      labels_t & accepting_labels,
                      syntax::model_flags_t flags = syntax::MODEL_NORMAL);

    /*!
      \brief Destructor
    */
    ~model_algorithm_t();

    /*!
      \brief Displays stats
      \param level : stats level
      \post Stats of the underlying model have been output to std::cout, including
      model name
     */
    void stats(unsigned level) const;
  protected:
    syntax::model_t * _model; /*!< Model */
  };



  /*!
    \class zg_algorithm_t
    \brief Algorithm on zone graph
  */
  class zg_algorithm_t : public model_algorithm_t {
  public:
    /*!
      \brief Constructor
      \param system_builder : builds underlying system (model)
      \param accepting_labels : labels that are accepting in the model
      \param model_flags : type of underlying model to build
      \param sem_flags : type of zone graph to build
      \post Provides a zone graph of type requested by sem_flags, over a model
      of type requested by model_flags and built by system_builder. The system
      builder may add labels that algorithms must consider accepting for
      correctness. All such labels have been added to
      accepting_labels.
    */
    zg_algorithm_t(syntax::system_builder_t & system_builder,
                   labels_t & accepting_labels,
                   syntax::model_flags_t model_flags = syntax::MODEL_NORMAL,
                   semantics::sem_flags_t sem_flags = semantics::SEM_DEFAULT);

    /*!
      \brief Destructor
    */
    ~zg_algorithm_t();

    /*!
      \brief Displays stats
      \param level : stats level
      \post Stats of the underlying model and underlying zone graph have been
      output to std::cout
     */
    void stats(unsigned level) const;
  protected:
    semantics::zg::zone_graph_t * _zg; /*!< Zone graph */
  };



  /*!
    \class gzg_algorithm_t
    \brief Algorithm on guessing zone graph
  */
  class gzg_algorithm_t : public model_algorithm_t {
  public:
    /*!
      \brief Constructor
      \param system_builder : builds underlying system (model)
      \param accepting_labels : labels that are accepting in the model
      \param model_flags : type of underlying model to build
      \param sem_flags : type of guessing zone graph to build
      \post Provides a guessing zone graph of type requested by sem_flags,
      over a model of type requested by model_flags and built by system_builder.
      The system builder may add labels that algorithms must consider accepting
      for correctness. All such labels have been added to accepting_labels.
    */
    gzg_algorithm_t(syntax::system_builder_t & system_builder,
                    labels_t & accepting_labels,
                    syntax::model_flags_t model_flags = syntax::MODEL_NORMAL,
                    semantics::sem_flags_t sem_flags = semantics::SEM_DEFAULT);

    /*!
      \brief Destructor
    */
    ~gzg_algorithm_t();

    /*!
      \brief Displays stats
      \param level : stats level
      \post Stats of the underlying model and underlying guessing zone graph
      have been output to std::cout
     */
    void stats(unsigned level) const;
  protected:
    semantics::gzg::guessing_zone_graph_t * _gzg;
  };



  /* Algorithm runner */

  /*!
    \brief Runs algorithms
    \param system_builder : system builder
    \param options : defines which algorithm to run
    \post Algorithm selected by options has been ran on system built by
    system_builder
    \throw std::invalid_argument : if options does not select an existing
    algorithm
   */
  void run(syntax::system_builder_t & system_builder,
           algorithms::options_t const & options);

} // end of namespace algorithms

#endif // __TCHECKER_ALGORITHMS_HH__

#ifndef __TCHECKER_ALGORITHMS_EMPTINESS_HH__
#define __TCHECKER_ALGORITHMS_EMPTINESS_HH__

#include <string>

#include "algorithms/algorithms-options.hh"
#include "algorithms/runnable.hh"
#include "base/labelset.hh"
#include "base/singleton.hh"
#include "syntax/system_builder.hh"

/*!
  \file emptiness.hh
  \brief Emptiness algorithms
*/

namespace algorithms {

  /*!
    \namespace emptiness
    \brief Emptiness algorithms
   */

  namespace emptiness {

    /*!
      \class algorithm_t
      \brief Class for emptiness algorithms that handle accepting labels.

      Notice that labels are first stored in an instance of labels_t as it is
      not invalidated when the global lable index (see global_t) evolves.
      Then, when the run() method is called, it is expected that the global
      label index is fully defined, and an instance of label_bitset_t is
      built from the instance of labels_t.
    */
    class algorithm_t : public algorithms::runnable_t {
    public:
      /*!
        \brief Destructor
      */
      virtual ~algorithm_t();

      /*!
        \brief Runs the algorithm
        \return True if the model is empty, false otherwise
        \pre The global label index should not be modified after the call to
        run()
        \post The labels bitset (_accepting_labels) has been built from the
        set (_labels) using the global label index
        \throw std::runtime_error when the set of accepting labels is empty
      */
      virtual bool run();
      
      /*!
        \brief Adds accepting labels
        \param labels : a comma-separated string of labels (see parse_id_list
        for the precise input format)
        \post All the accepting labels have been added to the set of accepting
        labels
        \throws std::out_of_range when some label in labels does not belong to
        the global label index
      */
      void accepting_labels(std::string const & labels);
      
      /*!
        \brief Accessor
        \return The set of accepting labels
      */
      labels_t const & labels() const;
      
      /*!
        \brief Accessor
        \return The set of accepting labels as a bitset
        \pre As the bitset is built by calling run(), the method run() has to
        be called before
      */
      label_bitset_t const & accepting_labels() const;
      
      /*!
        \brief Displays stats
        \param level : stats level
        \post The set of accepting labels has been output to std::cout (Level 0)
       */
      virtual void stats(unsigned level) const;

      /*!
        \brief Emptiness check
        \return True if the model is empty, false otherwise
        \note This method is called by run() after the bitset of accepting
        labels has been built
      */
      virtual bool emptiness_check() = 0;
    protected:
      /*!< Accepting labels set by accepting_labels() */
      labels_t _labels;
      /*!< Accepting labels built by run() */
      label_bitset_t _accepting_labels;
    };





    /*!
      \class factory_t
      \brief Factory for emptiness algorithms based on static bounds
    */
    class factory_t : public singleton_t<factory_t> {
      
      friend class singleton_t<factory_t>; // Grants access to cons/des
      
    public:
      /*!
        \brief Builds a new algorithm
        \param system_builder : model builder
        \param options : algorithm settings
        \throw std::logic_error : if the graph type in options is not
        supported by emptiness algorithms
        \throw std::logic_error : if the dynamic covering in options is not
        supported by emptiness algorithms
      */
      algorithms::emptiness::algorithm_t *
      new_algorithm(syntax::system_builder_t & system_builder,
                    algorithms::options_t const & options);
    private:
      /*!
        \brief Constructor (made private)
      */
      factory_t();
      
      /*!
        \brief Destructor (made private)
      */
      ~factory_t();
    };

    
  } // end of namespace emptiness

} // end of namespace algorithms

#endif // __TCHECKER_ALGORITHMS_EMPTINESS_HH__

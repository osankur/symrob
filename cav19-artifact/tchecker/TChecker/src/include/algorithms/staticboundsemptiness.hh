#ifndef __TCHECKER_ALGORITHMS_STATIC_BOUNDS_EMPTINESS_HH__
#define __TCHECKER_ALGORITHMS_STATIC_BOUNDS_EMPTINESS_HH__

#include "algorithms/algorithms.hh"
#include "algorithms/algorithms-options.hh"
#include "algorithms/emptiness.hh"
#include "graph/graph.hh"
#include "graph/nodescmp.hh"
#include "graph/pw.hh"
#include "semantics/semantics.hh"
#include "semantics/zg.hh"
#include "syntax/system_builder.hh"



/*!
  \file staticboundsemptiness.hh
  \brief Emptiness algorithms that use only static bounds (e.g. UPPAAL-like)
*/

namespace algorithms {

  /*!
    \namespace staticboundsemptiness
    \brief Emptiness algorithms that use only static bounds
  */

  namespace staticboundsemptiness {

    /*!
      \class node_t
      \brief Type of nodes (PW node + state based node)
    */
    class node_t : public graph::pw_node_t,
        public graph::state_node_t<semantics::zg::state_t> {
    public:
    };


    
    /*!
      \class stats_t
      \brief Provides counters for statistics on emptiness algorithms with
      static bounds computation
     */
    class stats_t {
    public:
      /*!
        \brief Constructor
        \post All counters have been initialized to 0
       */
      stats_t();

      /*!
        \brief Initializes all counters
        \post All counters have been initialized to 0
       */
      void initialize();

      /*!
        \brief Outputs the stats
        \param os : output stream
        \param level : stats level
        \post Stats of level at most 'level' have been output to os
       */
      void output(std::ostream & os, unsigned level) const;

      unsigned nodes_count;         /*!< Total number of nodes */
      unsigned visited_nodes_count; /*!< Number of visited nodes */
    };



    /*!
      \class emptiness_algorithm_t
      \brief Emptiness algorithm on zone graph using static bounds for
      extrapolation

      The algorithm is the following:

      insert initial node n0 in PW
      while (W is not empty) do
        pick a node n from W
        if (n is accepting)
          return "not empty"
        for each transition n -> n' in the zone graph do
          insert n' in PW
      return "empty"

      It uses a Passed-waiting list (see graph::pw_t) to ensure termination and
      to reduce memory usage. On insertion of a node n in PW:
      1- don't add n if it is covered by some node n' in P
      2- otherwise, remove all the nodes n' from P and from W that are covered
         by n, and insert n in P and in W

      The algorithm is guaranteed to terminate if the zone graph is abstracted
      using a finite extrapolation like ExtraLU+ or ExtraM+ and step (1) of the
      insertion in PW is enabled (i.e. the _covered predicate below is well
      chosen)
    */
    class algorithm_t
        : public algorithms::emptiness::algorithm_t,
        public algorithms::zg_algorithm_t,
        public algorithms::graph_output_owner_t {
    public:
      /*!
        \brief Constructor
        \param system_builder : model builder, hence zone graph builder
        \param options : algorithm settings
        \throw std::runtime_error : if the search strategy in options in not
        supported
        \throw std::runtime_error : if the check flag is set in options
       */
      algorithm_t(syntax::system_builder_t & system_builder,
                  algorithms::options_t const & options);

      /*!
        \brief Destructor
       */
      ~algorithm_t();
    protected:
      /*!
        \brief Emptiness check
        \return True if no accepting state is reachable, false otherwise
      */
      virtual bool emptiness_check();

      /*!
        \brief Outputs stats
        \param level : stats level
        \post Number of visited nodes, etc, have been output to std::cout
       */
      void stats(unsigned level) const;

      /*!
        \brief Displays the state-space computed by the algorithm
        \post All the states in the PW list have been displayed
       */
      void dump() const;

      /*!< PW cover predicate */
      graph::nodes_binpred_t<node_t> _pw_cover;
      /*!< Passed waiting list */
      graph::pw_t<node_t> * _pw;
      /*!< Statistics */
      stats_t _stats;
      /*!< Algorithm's options */
      algorithms::options_t const & _algorithm_options;
    };
    
  } // end of namespace staticboundsemptiness

} // end of namespace algorithms

#endif // __TCHECKER_ALGORITHMS_STATIC_BOUNDS_EMPTINESS_HH__

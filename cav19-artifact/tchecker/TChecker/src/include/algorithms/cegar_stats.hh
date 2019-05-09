#ifndef CEGAR_STATS_HH
#define CEGAR_STATS_HH

#include <iostream>
namespace algorithms {

  namespace cegaremptiness {


    /*!
    \class stats_t
    \brief Provides counters for statistics on emptiness algorithms with
    on-the-fly bounds computation
   */
    class stats_t {
    public:
      /*!
      \brief Constructor
      \post All counters have been intialized to 0
    */
      stats_t();

      /*!
      \brief Initializes the counters
      \post All counters have been intialized to 0
     */
      void initialize();

      /*!
      \brief Outputs the stats
      \param os : output stream
      \param level : stats level
      \post Stats of level at most 'level' have been output to os
     */
      void output(std::ostream & os, unsigned level) const;

      unsigned nodes_count;           /*!< Total number of nodes */
      unsigned visited_nodes_count;   /*!< Number of visited nodes */
      unsigned uncoverings_count;     /*!< Number of node uncoverings */
      unsigned deleted_count;
      unsigned refinement_count;    /*!< Number of propagation threads */
      unsigned max_refine;              /*!< Longest propagation thread */
      double   avg_refine;              /*!< Avg. length of propagation thread */
    };
  }
}
#endif // CEGAR_STATS_HH

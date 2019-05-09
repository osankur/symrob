#ifndef __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_STATS_HH__
#define __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_STATS_HH__

#include <iostream>

/*!
  \file otfboundsemptiness-stats.hh
  \brief Statistics for on-the-fly bounds emptiness algorithms
*/

namespace algorithms {

  namespace otfboundsemptiness {

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
      unsigned updates_count;         /*!< Number of node updates */
      unsigned uncoverings_count;     /*!< Number of node uncoverings */
      unsigned prop_threads_count;    /*!< Number of propagation threads */
      unsigned max_hops;              /*!< Longest propagation thread */
      double   avg_hops;              /*!< Avg. length of propagation thread */
    };

  } // end of namespace otfboundsemptiness

} // end of namespace algorithms

#endif // __TCHECKER_ALGORITHMS_OTF_BOUNDS_EMPTINESS_STATS_HH__

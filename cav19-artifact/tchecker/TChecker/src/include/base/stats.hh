#ifndef __TCHECKER_STATS_HH__
#define __TCHECKER_STATS_HH__

#include <ostream>
#include <stdexcept>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/unordered_map.hpp>


/*!
  \file stats.hh
  \brief Tools for statistics
 */




/* IMPLEMENTATION NOTE: we extend below Boost accumulators framework with
   frequency distributions. The coding style is borrowed from Boost accumulator
   framework documentation
*/

namespace boost {

  namespace accumulators {

    namespace impl {
      
      /*!
	\class frequency_accumulator
	\tparam T : type of datas in the sample. The frequency distribution
	is stored in boost::ordered::unordered_map with hash function
	boost::hash<T> and equality predicate std::equal_to<T> that must
	be defined.
	\brief Frequency distribution of datas in a sample
       */
      template < typename T >
      class frequency_accumulator : public accumulator_base {

	/*!
	  \brief Type of frequency distribution map
	 */
	template < typename U >
	using frequency_map_t =
	  typename boost::unordered::unordered_map<U, size_t>;

      public:
	/*!
	  \brief Type of result (frequency distribution map)
	*/
	typedef frequency_map_t<T> const & result_type;

	/*!
	  \brief Constructor
	 */
	frequency_accumulator(dont_care) {
	  /* IMPLEMENTATION NOTE: documentation for Boost 1.54 stipulates that
	     there may be an initial value in the argument pack given to the
	     constructor. This is not the case here, as for accumulator count.
	  */
	}


	/*!
	  \brief Accumulate operator
	  \tparam ARGS : type of argument pack
	  \param args : argument pack
	  \pre The sample value is at index 'sample'
	  \post The sample value has been counted in the frequency
	  distribution
	*/
	template <typename ARGS>
	void operator() (ARGS const & args) {
	  ++ _d[ args[sample] ];
	}

	/*!
	  \brief Result function
	  \return Frequency distribution of accumulated datas
	*/
	result_type result(dont_care) const {
	  return _d;
	}
      private:
	/*!< Distribution */
	frequency_map_t<T> _d;
      };

    } // end of namespace impl



    namespace tag {

      /*!
	\class frequency
	\brief Feature for frequency distribution accumulator
       */
      class frequency : public depends_on<> {
      public:
	/*!
	  \brief Type of accumulator implementing feature frequency
	  distribution
	*/
	typedef accumulators::impl::frequency_accumulator< mpl::_1 > impl;
      };

    } // end of namespace tag



    namespace extract {

      /*!
	\brief Extractor for frequency distribution accumulator
       */
      extractor< tag::frequency > const frequency = {};

    } // end of namespace extract


    using extract::frequency; // Make it reachable from that namespace


  } // end of namespace accumulators

} // end of namespace boost




/*!
  \namespace stats
  \brief Tools for statistics
 */
namespace stats {

  /*!
    \brief Type of stats labels
  */
  enum labels_t {
    TCHECKER_OUTCOME,        /*!< Outcome of tchecker algorithm */
    TCHECKER_RSS_PEAK,       /*!< Maximum resident set size */
    TCHECKER_RSS_NOW,        /*!< Maximum resident set size */
    TCHECKER_TIME_USER,      /*!< User time used */
    TCHECKER_TIME_OS,        /*!< System time used */
    MODEL_NAME,              /*!< Name of the model */
    MODEL_VLOC_CACHE_SIZE,   /*!< Cache of vlocs: size (#entries) */
    MODEL_VLOC_CACHE_MEM,    /*!< Cache of vlocs: memory (approx) */
    MODEL_LAYOUT_CACHE_SIZE, /*!< Cache of layouts: size (#entries) */
    MODEL_LAYOUT_CACHE_MEM,  /*!< Cache of layouts: memory (approx) */
    NODES_TOTAL,             /*!< Total number of nodes */
    NODES_VISITED,           /*!< Number of visited nodes */
    NODES_UNVISITED,         /*!< Number of unvisited nodes */
    NODES_INACTIVE,          /*!< Number of inactive nodes */
    REFINE_COUNT,            /*!< Number of refinement */
    REFINE_MAX,              /*!< maximum length of refinement */
    REFINE_AVG,              /*!< average length of refinement */
    REFINE_DELETED,          /*!< Number of deleted node */
    REFINE_UNCOVERED,        /*!< Number of uncovered node */
    PW_SIZE,                 /*!< Size of PW */
    PW_KEYS_TOTAL,           /*!< Number of keys in PW */
    PW_LSIZE_MIN,            /*!< Min number of nodes with same key in PW */
    PW_LSIZE_MAX,            /*!< Max number of nodes with same key in PW */
    PW_LSIZE_AVG,            /*!< Average number of nodes with same key in PW */
    PW_LSIZE_FREQ,           /*!< Frequency of number of nodes per key in PW */
    STATES_TOTAL,            /*!< Total number of automaton states */
    STATES_MIN,              /*!< Min number of states occurrences */
    STATES_MAX,              /*!< Max number of states occurrences */
    STATES_AVG,              /*!< Average number of states occurrences */
    STATES_FREQ,             /*!< Frequency of states occurrences */
    DCOV_TOTAL,              /*!< Total number of dynamic covered nodes */
    DCOV_MIN,                /*!< Min number of dynamic covered nodes */
    DCOV_MAX,                /*!< Max number of dynamic covered nodes */
    DCOV_AVG,                /*!< Average number of dynamic covered nodes */
    DCOV_FREQ,               /*!< Frequency: number of dynamic covered nodes */
    DCOV_UNCOVERS,           /*!< Number of dynamic uncovering */
    DBOUNDS_UPDATES,         /*!< Number of dynamic bounds updates */
    DBOUNDS_PTHREADS,        /*!< Number of dynamic bounds propagation threads*/
    DBOUNDS_HOPS_MAX,        /*!< Max number of propagation hops */
    DBOUNDS_HOPS_AVG,        /*!< Average number of propagation hops */
    ZONES_TOTAL,             /*!< Total number of zones */
    ZONES_MIN,               /*!< Min number of occurrences for a zone */
    ZONES_MAX,               /*!< Max number of occurrences for a zone */
    ZONES_AVG,               /*!< Average number of occurrences for a zone */
    ZONES_FREQ,              /*!< Frequency of occurrences of zones */
    ZONES_SHARED_CACHE_SIZE, /*!< Shared zones cache: size (#entries) */
    ZONES_SHARED_CACHE_MEM,  /*!< Shared zones cache: memory (approx) */
    ACCEPTING_LABELS         /*!< Set of accepting labels */
  };


  /*!
    \brief Outputs stats label
    \param os : output stream
    \param l : stats label
    \return output stream stream resulting from outputing standard code for l
    to os
    \throws std::logic_error : if l is an unknown label (should never occur)
   */
  std::ostream & operator << (std::ostream & os, enum labels_t const l);


  /*!
    \class sample_analyzer_t
    \brief Provides min, max, mean, count and frequency accumulators
  */
  template <class T>
  using sample_analyzer_t 
  = boost::accumulators::accumulator_set
    < T,
      boost::accumulators::stats< boost::accumulators::tag::count,
				  boost::accumulators::tag::frequency,
				  boost::accumulators::tag::max,
				  boost::accumulators::tag::mean,
				  boost::accumulators::tag::min > >;


  /*!
    \brief Accessor to peak resident set size
    \return max resident set size, 0 if OS is not supported or could not
    read the value from OS
   */
  size_t peak_rss();

  
  /*!
    \brief Accessor to current resident set size
    \return current resident set size, 0 if OS is not supported or could not
    read the value from OS
   */
  size_t current_rss();


  /*!
    \brief Time in seconds and micro-secconds
    \remark like struct timeval in the POSIX world. Compatible with non-POSIX
    systems
   */
  struct time_t {
    long int sec;
    long int usec;
  };

  
  /*!
    \brief Accessor to user time used
    \return user time used, sec = -1 in returned structure if OS is not
    supported
   */
  struct time_t user_time();


  /*!
    \brief Accessor to system time used
    \return system time used, sec = -1 in returned structure if OS is not
    supported
   */
  struct time_t system_time();
  

  /*!
    \brief outputs a struct timeval object
    \param os : output stream
    \param t : timeval to output
    \post t has been output to os
   */
  std::ostream & operator << (std::ostream & os, struct time_t const & t);

} // end of namespace stats

#endif // __TCHECKER_STATS_HH__

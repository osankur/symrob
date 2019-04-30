#ifndef __TCHECKER_GRAPH_STATS_HH__
#define __TCHECKER_GRAPH_STATS_HH__

#include <iostream>
#include <ostream>

#include <boost/unordered/unordered_map.hpp>

#include "base/ptr.hh"
#include "base/stats.hh"
#include "symbolic/zone.hh"
#include "syntax/ta.hh"

/*!
  \file stats.hh
  \brief Statistics on nodes range used by several algorithms
 */

namespace graph {

  /*!
    \brief Computes and displays statistics on zones
    \tparam ITERATOR : type of iterator on nodes
    \tparam ZONE_ACCESSOR : type of accessor to the zone in a node
    \param os : output stream
    \param level : stats level
    \param begin : iterator on first node in the range
    \param end : iterator on past-the-end value in the range
    \param zone_accessor : accessor to the zone in a node. Should be callable
    with type (NODE const * -> symbolic::zone_t const *) where NODE is the
    type of nodes in the range
    \pre (begin, end) is a range of node pointers with zones of type
    symbolic::zone_t const * accessible by a call to zone_accessor
    \post if level >= 2, the number of distinct zones, minimum number of
    occurrences, maximum number of occurrences, average number of occurrences
    and frequency of occurrences for zones in range (begin, end) have been
    output to os with labels defined in stats::labels_t
    \note This function has a high complexity in time and space since it builds
    the set of zones in (begin, end)
   */
  template <class ITERATOR, class ZONE_ACCESSOR>
  void stats_zones(std::ostream & os, unsigned level, ITERATOR const & begin,
		   ITERATOR const & end, ZONE_ACCESSOR zone_accessor) {
    // Level 0 and 1 : nothing
    if (level <= 1)
      return;

    // Count occurrences of zones in (begin, end)
    boost::unordered::unordered_map
      < symbolic::zone_t const *,
	unsigned,
	ptr_delegate_hash<symbolic::zone_t const>,
	ptr_delegate_equal_to<symbolic::zone_t const> > m;
    
    for (auto it = begin; it != end; ++it)
      ++ m[ zone_accessor(*it) ];

    // Analyze the sample of zone occurrences
    stats::sample_analyzer_t<unsigned> acc;
    for (auto p : m)
      acc(p.second);

    // Output distribution
    os << stats::ZONES_TOTAL << m.size() << std::endl
       << stats::ZONES_MIN   << boost::accumulators::min(acc) << std::endl
       << stats::ZONES_MAX   << boost::accumulators::max(acc) << std::endl
       << stats::ZONES_AVG   << boost::accumulators::mean(acc)
       << std::endl;

    boost::accumulators::impl::frequency_accumulator<unsigned>::result_type
      d = boost::accumulators::frequency(acc);
    for (std::pair<unsigned, unsigned> const & p : d)
      os << stats::ZONES_FREQ << p.first << " : " << p.second
	 << std::endl;
  }




  /*!
    \brief Computes and displays statistics on automaton states
    \tparam ITERATOR : type of iterator on nodes
    \tparam STATE_ACCESSOR : type of accessor to the state in a node
    \param os : output stream
    \param level : stats level
    \param begin : iterator on first node in the range
    \param end : iterator on past-the-end value in the range
    \param state_accessor : accessor to the state in a node. Should be callable
    with type (NODE const * -> syntax::state_t const *) where NODE is the
    type of nodes in the range
    \pre (begin, end) is a range of node pointers with states of type
    syntax::state_t const * accessible by a call to state_accessor
    \post if level >= 2, the number of distinct states, minimum number of
    occurrences, maximum number of occurrences, average number of occurrences
    and frequency of occurrences for states in range (begin, end) have been
    output to os with labels defined in stats::labels_t
    \note This function has a high complexity in time and space since it builds
    the set of states in (begin, end)
   */
  template <class ITERATOR, class STATE_ACCESSOR>
  void stats_states(std::ostream & os, unsigned level, ITERATOR const & begin,
		    ITERATOR const & end, STATE_ACCESSOR state_accessor) {
    // Level 0 and 1 : nothing
    if (level <= 1)
      return;

    // Count occurrences of states in (begin, end)
    boost::unordered::unordered_map
      < syntax::state_t const *,
	unsigned,
	ptr_delegate_hash<syntax::state_t const>,
	ptr_delegate_equal_to<syntax::state_t const> > m;
    
    for (auto it = begin; it != end; ++it)
      ++ m[ state_accessor(*it) ];

    // Compute the distribution of state occurrences
    stats::sample_analyzer_t<unsigned> acc;
    for (auto p : m)
      acc(p.second);

    // Output distribution
    os << stats::STATES_TOTAL << m.size() << std::endl
       << stats::STATES_MIN   << boost::accumulators::min(acc) << std::endl
       << stats::STATES_MAX   << boost::accumulators::max(acc) << std::endl
       << stats::STATES_AVG   << boost::accumulators::mean(acc)
       << std::endl;

    boost::accumulators::impl::frequency_accumulator<unsigned>::result_type
      d = boost::accumulators::frequency(acc);
    for (std::pair<unsigned, unsigned> const & p : d)
      os << stats::STATES_FREQ << p.first << " : " << p.second
	 << std::endl;
  }




  /*!
    \brief Computes and displays statistics on dynamic covered nodes
    \tparam ITERATOR : type of iterator on nodes
    \tparam NCOV_ACCESSOR : type of accessor to the number of dynamic covered
    nodes
    \param os : output stream
    \param level : stats level
    \param begin : iterator on first node in the range
    \param end : iterator on past-the-end value in the range
    \param ncov_accessor : accessor to the number of nodes dynamically covered
    by a node. Should be callable with type (NODE const * -> unsigned) where
    NODE is the type of nodes in the range
    \pre (begin, end) is a range of node pointers with number of dynamic 
    covered nodes accessible by a call to ncov_accessor
    \post if level >= 2, the number of dynamic covered nodes, minimum
    number of dynamic covered nodes, maximum number of dynamic covered nodes,
    average number of dynamic covered nodes and frequency of numbers of dynamic
    covered nodes in range (begin, end) have been output to os with labels
    defined in stats::labels_t
   */
  template <class ITERATOR, class NCOV_ACCESSOR>
  void stats_dynamic_covered(std::ostream & os, unsigned level,
			     ITERATOR const & begin, ITERATOR const & end,
			     NCOV_ACCESSOR ncov_accessor) {
    // Level 0 and 1 : nothing
    if (level <= 1)
      return;

    // Compute the distribution of number of dynamic covered nodes
    unsigned ncov_total = 0;
    stats::sample_analyzer_t<unsigned> acc;
    for (auto it = begin; it != end; ++it) {
      unsigned ncov = ncov_accessor(*it);
      acc(ncov);
      ncov_total += ncov;
    }

    // Output distribution
    os << stats::DCOV_TOTAL << ncov_total << std::endl
       << stats::DCOV_MIN   << boost::accumulators::min(acc) << std::endl
       << stats::DCOV_MAX   << boost::accumulators::max(acc) << std::endl
       << stats::DCOV_AVG   << boost::accumulators::mean(acc)
       << std::endl;

    boost::accumulators::impl::frequency_accumulator<unsigned>::result_type
      d = boost::accumulators::frequency(acc);
    for (std::pair<unsigned, unsigned> const & p : d)
      os << stats::DCOV_FREQ << p.first << " : " << p.second
	 << std::endl;
  }

} // end of namespace graph

#endif // __TCHECKER_GRAPH_STATS_HH__

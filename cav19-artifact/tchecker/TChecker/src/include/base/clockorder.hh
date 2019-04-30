#ifndef __TCHECKER_CLOCKORDER_HH__
#define __TCHECKER_CLOCKORDER_HH__

#include <ostream>
#include <vector>

#include "base/clockindex.hh"
#include "base/clockset.hh"

/*!
  \file clockorder.hh
  \brief Linear order over clocks
*/

/*!
  \class clock_order_t
  \brief Representation of a linear order over clocks in global_t::clock_index
*/
class clock_order_t : public std::vector<clock_id_t> {
public:
  /*!
    \brief Constructor
  */
  clock_order_t();

  /*!
    \brief Hash function
    \return Hash code of the clock order
  */
  size_t hash() const;

  /*!
    \brief Check if cs is downward closed for clock order
    \param cs : clock bit set to check
    \return True if cs is downward closed,
    false otherwise
  */
  bool downward_closed(clock_bitset_t const & cs) const;

  /*!
    \brief Output clock order
    \param output : where to output
    \param index : to decode clock ids
    \post The clock index has been output to output
  */
  void output(std::ostream & output,
	      clock_index_t const & index =
	      global_t::instance().clock_index()) const;
};

#endif // __TCHECKER_CLOCKORDER_HH__

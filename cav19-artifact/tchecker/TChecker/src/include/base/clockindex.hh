#ifndef __TCHECKER_CLOCKINDEX_HH__
#define __TCHECKER_CLOCKINDEX_HH__

#include <string>

#include <dbm/ClockAccessor.h>

#include "base/index.hh"


/*!
  \file clockindex.hh
  \brief An index for clocks
*/

/*!
  \typedef clock_id_t
  \brief Type of clock indices
*/
typedef cindex_t clock_id_t;


/*!
  \class clock_index_t
  \brief A class for clock index

  A fake clock with index 0 is added at construction/clearing
*/
class clock_index_t : public auto_index_t<clock_id_t, std::string>,
		      public dbm::ClockAccessor {
public:
  /*!
    \brief Constructor
  */
  clock_index_t();

  /*!
    \brief Copy-constructor
    \param ci : clock index to build from
    \post The instance is a copy of ci
  */
  clock_index_t(clock_index_t const & ci);

  /*!
    \brief Assignment operator
    \param ci : clock index to assign from
    \post The instance is a copy of ci
   */
  clock_index_t & operator = (clock_index_t const & ci);

  /*!
    \brief Access to clock names required by UPPAAL DMB library
    \param i : index of the clock
    \return Name of the clock
  */
  const std::string getClockName(cindex_t i) const;

  /*!
    \brief Clears index and puts back the fake clock
  */
  void clear();

  // Lightweight iterator

  typedef enum {
    ALL_CLOCKS, /*!< Iterates over all clocks */
    REAL_CLOCKS /*!< Iterates over all clocks but the fake clock */
  } iiterator_t;
  
  /*!
    \brief Lightweight iterator
    \param it_type : type of iterator
    \return Iterator on the first clock (according to it_type)
  */
  clock_id_t ibegin(iiterator_t it_type = REAL_CLOCKS) const;

  /*!
    \var static const clock_id_t fake_clock_index
    \brief Index of the fake clock (fast access)
   */
  static const clock_id_t fake_clock_index;

  /*!
    \var static const std::string fake_clock_name
    \brief Name of the fake clock.

    ONLY FOR INTERNAL USE. ACCESS FROM global_t.
  */
  static const std::string fake_clock_name;
};

#endif // __TCHECKER_CLOCKINDEX_HH__

#ifndef __TCHECKER_LABELINDEX_HH__
#define __TCHECKER_LABELINDEX_HH__

#include <boost/cstdint.hpp>

#include "base/index.hh"


/*!
  \file labelindex.hh
  \brief An index for labels (e.g. accepting labels on states)
*/

/*!
  \typedef label_id_t
  \brief Type of label indices
 */
typedef boost::uint8_t label_id_t;


/*!
  \class label_index_t
  \brief A class for label index
 */
class label_index_t : public auto_index_t<label_id_t, std::string> {
public:
  /*!
    \brief Constructor
  */
  label_index_t() = default;

  /*!
    \brief Copy-constructor
    \param li : label index to build from
    \post The instance is a copy of li
  */
  label_index_t(label_index_t const & li);

  /*!
    \brief Assignment operator
    \param li : label index to assign from
    \post The instance is a copy of li
   */
  label_index_t & operator = (label_index_t const & li);
};

#endif // __TCHECKER_LABELINDEX_HH__

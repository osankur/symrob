#ifndef __TCHECKER_SYNCHRO_HH__
#define __TCHECKER_SYNCHRO_HH__

#include <ostream>
#include <unordered_map>
#include <boost/functional/hash.hpp>

#include "base/cast.hh"

/*!
  \file synchro.hh
  \brief Synchronization labels
*/

namespace syntax {

  /*!
    \class sync_label_t
    \brief Generic synchronization labels
   */
  class sync_label_t {
  protected:
    /*!
      \brief Constructor
     */
    sync_label_t();

    /*!
      \brief Copy constructor
      \param l : synchronization label to copy from
     */
    sync_label_t(sync_label_t const & l);
  public:
    /*!
      \brief Destructor
     */
    virtual ~sync_label_t();

    /*!
      \brief Equality predicate
      \param l : synchronization label to compare to
      \return True if l and this are equal, false otherwise
     */
    virtual bool operator == (sync_label_t const & l) const = 0;

    /*!
      \brief Hash function
      \return Hash code of this
     */
    virtual std::size_t hash() const = 0;

    /*!
      \brief Output function
      \param os : output stream
      \post This has been output to os
     */
    virtual void output(std::ostream & os) const = 0;

    /*!
      \brief Empty label
     */
    static sync_label_t const * null;
  };
 


  /*!
    \class generic_label_t
    \param T : type of label
    \brief Synchronization label with type T
  */
  template<typename T>
  class generic_label_t : public sync_label_t {
  public:
    /*!
      \brief Constructor
    */
    generic_label_t() : sync_label_t(), _val() {
    }

    /*!
      \brief Copy constructor
      \param l : label to copy
      \post this is a copy of l
     */
    generic_label_t(generic_label_t<T> const &l) : sync_label_t(l),
						   _val(l._val) {
    }

    /*!
      \brief Constructor from value
      \param v : label value
      \post this has been built with value v
     */
    generic_label_t(T const & v) : sync_label_t(), _val(v) {
    }

    /*!
      \brief Destructor
    */
    virtual ~generic_label_t() = default;

    /*!
      \brief Equality predicate (see sync_label_t::operator==)
    */
    virtual bool operator == (sync_label_t const & l) const {
      auto glt = CAST(generic_label_t<T> const *, &l);
      return (glt != nullptr) && (glt->_val == _val);
    }

    /*!
      \brief Hash function (see sync_label_t::hash)
    */
    virtual std::size_t hash() const {
      return boost::hash_value(_val);
    }

    /*!
      \brief Output function (see sync_label_t::output)
     */
    virtual void output(std::ostream & os) const {
      os << _val;
    }
    
    /*!
      \brief Accessor
      \return Label value
     */
    virtual T const & get () const {
      return _val;
    }

    /*!
      \brief Label cache management
      \param val : label value
      \return The unique label representing value val in cache
     */
    static generic_label_t<T> const * find_or_add(T const & val) {
      static std::unordered_map<T, generic_label_t<T>> unique_table;
      generic_label_t<T> const * result;

      auto i = unique_table.find (val);
      if (i == unique_table.end ()) {
	unique_table[val] = generic_label_t<T> (val);
	result = &unique_table[val];
      }
      else
	result = &(i->second);

      return result;
    }
  private:
    T _val; /*!< Label value */
  };


  /*!
    \brief String valued synchronization labels
   */
  typedef generic_label_t<std::string> sync_string_t;


} // end of namespace syntax


#endif // __TCHECKER_SYNCHRO_HH__

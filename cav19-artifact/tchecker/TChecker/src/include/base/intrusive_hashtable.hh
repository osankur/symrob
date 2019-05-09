#ifndef __TCHECKER_INTRUSIVE_HASHTABLE_HH__
#define __TCHECKER_INTRUSIVE_HASHTABLE_HH__

#include <cstddef>
#include <boost/intrusive/unordered_set.hpp>


/*!
  \file intrusive_hashtable.hh
  \brief Intrusive hashtable based on Boost unordered sets, with internal
  bucket array
*/



/*!
  \class buckets_owner_t
  \brief Owns a bucket array compliant with Boost unordered sets
  \tparam see boost::intrusive::unordered_set
*/
template <typename T, class... Options>
class buckets_owner_t {
public:
  /*!
    \brief Alias type name for type of buckets
  */
  typedef typename boost::intrusive::unordered_set<T, Options...>::bucket_type
  bucket_type;

  /*!
    \brief Constructor
    \param size : number of buckets
    \post An array of "size" buckets has been allocated
  */
  buckets_owner_t(std::size_t size) {
    _buckets = new bucket_type[size];
  }

  /*!
    \brief Destructor
    \post The array of buckets has been deallocated
  */
  ~buckets_owner_t() {
    delete[] _buckets;
  }
protected:
  bucket_type * _buckets; /*!< Array of buckets */
};


/*!
  \class intrusive_hashtable_t
  \brief Intrusive hashtable based on Boost intrusive unordered sets
  \taparm see boost::intrusive::unordered_set
  \note buckets_owner_t is used to build the array of buckets before to build
  the unordered set using the inheritance mechanism
 */
template <typename T, class... Options>
class intrusive_hashtable_t
  : protected buckets_owner_t<T, Options...>,
    public boost::intrusive::unordered_set<T, Options...> {

  /*!
    \brief Alias type name for bucket traits
  */
  typedef
  typename boost::intrusive::unordered_set<T, Options...>::bucket_traits
  bucket_traits;

public:
  /*!
    \brief Constructor
    \param size : size of the hash table (number of buckets)
    \post A hashtable with an array of buckets of size "size" has been built
  */
  intrusive_hashtable_t(std::size_t size)
    : buckets_owner_t<T, Options...>(size),
    boost::intrusive::unordered_set<T, Options...>(bucket_traits(this->_buckets,
								 size))
  {}

  /*!
    \brief Memory occupation
    \return Memory used by the hash table, excluding stored objects
   */
  std::size_t memsize() const {
    std::size_t size = sizeof(*this)
      + ( this->bucket_count() 
	  * sizeof(typename buckets_owner_t<T, Options...>::bucket_type) );
    return size;
  }
};


#endif // __TCHECKER_INTRUSIVE_HASHTABLE_HH__

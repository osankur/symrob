#ifndef __TCHECKER_CACHE_HH__
#define __TCHECKER_CACHE_HH__

#include <functional>
#include <stdexcept>
#include <utility>

#include <boost/functional/hash.hpp>
#include <boost/unordered_set.hpp>

/*!
  \file cache.hh
  \brief A cache for objects
 */


/*!
  \class cache_t
  \tparam T : The type of stored values
  \tparam HASH : Hasher for type T (see boost::hash for documentation)
  \tparam EQUAL : Equality on type T
  \brief Stores unique values of type T w.r.t. predicate EQUAL
*/
template <class T,
	  class HASH = boost::hash<T>,
	  class EQUAL = std::equal_to<T> >
class cache_t {
private:
  /*!< Type of storage */
  typedef typename boost::unordered_set<T, HASH, EQUAL> set_t;
public:
  /*!
    \brief Constructor
  */
  cache_t() {
    clear();
  }

  /*!
    \brief Clears the cache
    \post The cache is empty. No destructor are called.
  */
  void clear() {
    _set.clear();
  }

  /*!
    \brief Clears the cache and disposes of stored values
    \tparam DISPOSER : type of disposer
    \param disposer : a disposer
    \post The cache is empty and all stored elements have been removed, then
    disposed. No destructors are called.
   */
  template <class DISPOSER>
  void clear_and_dispose(DISPOSER disposer) {
    for (typename set_t::iterator it = _set.begin(); it != _set.end(); ++it) {
      T const & t = *it;
      _set.erase(it);
      disposer(t);
    }
    _set.clear();
  }
  
  /*!
    \brief Insertion in the cache
    \param t : the value to store in the cache
    \throw std::invalid_argument : when insertion fails, in particular if an 
    identical value is already in the cache    
    \post t has been added to the cache
  */
  void insert(T const & t) {
    std::pair<typename set_t::iterator, bool> res = _set.insert(t);
    if (! res.second)
      throw std::invalid_argument("*** cache_t::insert: failed");
  }

  /*!
    \brief Finds a value in the cache
    \param t : the value to find
    \return True if (a value equivalent to) t is found,
    false otherwise
  */
  bool find(T const & t) const {
    return (_set.find(t) != _set.end());
  }

  /*!
    \brief Finds a value in the cache
    \param t : the value to find
    \param found : a reference to the stored value equivalent to t (if found)
    \return True if (a value equivalent to) t is found and sets found,
    false otherwise
  */
  bool find(T const & t, T & found) const {
    typename set_t::iterator it = _set.find(t);

    if (it == _set.end())
      return false;

    found = *it;
    return true;
  }

  /*!
    \brief Ensures that t is stored in the cache
    \param t : the value to store
    \return The value equivalent to t that is stored in the cache. It is t
    itself when no value equivalent to t was stored before the call
    \post t has been added to the cache if it was not in before
  */  
  T const & find_else_insert(T const & t) {
    typename set_t::iterator itf = _set.find(t);

    // Checks t already stored
    if (itf != _set.end())
      return *itf;

    // Stores t and returns a reference to stored value
    std::pair<typename set_t::iterator, bool> iti = _set.insert(t);
    if (! iti.second)
      throw std::invalid_argument("*** cache_t::find_else_insert: failed");

    return *(iti.first);
  }

  /*!
    \brief Size of the cache
    \return The number of elements in the cache
   */
  std::size_t size() const {
    return _set.size();
  }

  /*!
    \brief Accessor to memory footprint
    \return Approximate memory footprint of internal hashtable, excluding
    footprint of stored elements
   */
  std::size_t memsize() const {
    std::size_t memsize =
      _set.bucket_count() * sizeof(void *) + // size of hashtable (boost doc)
      _set.size() * sizeof(T *); // pointers to stored elements
    return memsize;
  }

  /*!
    \brief Iterator on cached values

    USE WITH CARE: MODIFYING CACHED VALUES MAY INVALIDATE THE UNDERLYING HASH
    TABLE!!!
  */
  typedef typename set_t::iterator iterator;

  /*!
    \brief Iterator
    \return Reference on first value
  */
  iterator begin() {
    return _set.begin();
  }

  /*!
    \brief Iterator
    \return Reference out of range
  */
  iterator end() {
    return _set.end();
  }
private:
  /*!< Hash table */
  set_t _set;
};

#endif // __TCHECKER_CACHE_HH__

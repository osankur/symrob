#ifndef __TCHECKER_KEY_SET_HH__
#define __TCHECKER_KEY_SET_HH__

#include <ostream>
#include <string>
#include <vector>

#include <boost/dynamic_bitset.hpp>
#include <boost/functional/hash.hpp>

#include "base/global.hh"
#include "base/index.hh"
#include "base/parsers.hh"

/*!
  \file keyset.hh
  \brief Collections of keys
*/


// key_collection_t

/*!
  \class key_collection_t
  \brief Collection of values as the collection of their keys
  \tparam KEY : type of keys
  \tparam T : type of values
  \tparam COLLECTION : name of derived class, to avoid casting. Typical use:
  class A : public key_collection_t<...,...,A>
 */
template <class KEY, class T, class COLLECTION>
class key_collection_t : public std::vector<KEY> {
public:
  /*!
    \typedef typename T value_t;
    \brief Type of values in the collection
  */
  typedef T value_t;

  /*!
    \typedef typename KEY key_t;
    \brief Type of keys
  */
  typedef KEY key_t;

  /*!
    \typedef typename COLLECTION t;
    \brief Type of the collection
  */
  typedef COLLECTION t;

  /*!
    \brief Adds k to the collection
    \param k : the key to add
  */
  void add(KEY const & k) {
    this->push_back(k);
  }

  /*!
    \brief Adds key of value t to the collection
    \param t : value to add
    \param index : for indexing t
    \throw std::out_of_range : when t is not indexed
  */
  void add(T const & t, index_t<KEY, T> const & index) {
    this->push_back(index(t));
  }

  /*!
    \brief Appends collection c
    \param c : the collection to append
  */
  void append(COLLECTION const & c) {
    this->insert(this->end(), c.begin(), c.end());
  }

  /*!
    \brief Finds k in collection
    \param k : the key to find
    \return True when k belongs to the collection,
    false otherwise
  */
  bool find(KEY const & k) const {
    return (std::find(this->begin(), this->end(), k) != this->end());
  }

  /*!
    \brief Finds (key of) t in a collection
    \param t : the value to find
    \param index : to encode t
    \return True when (key of t) belongs to the collection,
    false otherwise
  */
  bool find(T const & t, index_t<KEY, T> const & index) const {
    return find(index(t));
  }

  /*!
    \brief Hash function for collections
    \return Hash code
  */
  size_t hash() const {
    size_t seed = global_t::instance().hash_seed();

    boost::hash_combine(seed, this->size());
    for ( const KEY & k : *this )
      boost::hash_combine(seed, k);

    return seed;
  }

  /*!
    \brief Output a key collection
    \param output : where to output the collection
    \param index : to decode keys in collection
    \post The collection has been output to output
  */
  void output(std::ostream & output, index_t<KEY, T> const & index) const {
    for (auto it = this->begin(); it != this->end(); ++it) {
      if (it != this->begin())
	output << ",";
      output << index(*it);
    }
  }
};


/*!
  \brief A function that sets a collection from a string of comma-separated
  names  
  \tparam KEY : type of keys
  \tparam COLLECTION : see ::key_collection_t
  \param c : value to set
  \param s : string of comma-separated names
  \param index : for encoding names into KEYs
*/
template <class KEY, class COLLECTION>
void set(key_collection_t<KEY, std::string, COLLECTION> & c,
	 std::string const & s,
	 index_t<KEY, std::string> const & index) {
  std::vector<std::string> v;
  
  parse_id_list(s, v);

  c.clear();
  for (std::string & name : v) {
    c.add(name, index);
  }
}



// key_bitset_t


/*!
  \class key_bitset_t
  \brief Set of values as the set of their keys, implemented as a bit set

  Any modification to the index used for creating a key_bitset_t<> will
  invalidate the bit set

  \tparam KEY : type of keys, supposed to be an unsigned integer type
  \tparam T : type of values
  \tparam BITSET : name of derived class, to avoid casting. Typical use:
  class A : public key_bitset_t<...,...,A>
*/
template <class KEY, class T, class BITSET>
class key_bitset_t {

  static_assert( !std::numeric_limits<KEY>::is_signed, "KEY must be unsigned" );

public:
  /*!
    \typedef typename T value_t;
    \brief Type of values in bit set
  */
  typedef T value_t;

  /*!
    \typedef typename KEY key_t;
    \brief Type of keys
  */
  typedef KEY key_t;

  /*!
    \typedef typename BITSET t;
    \brief Type of bit set
  */
  typedef BITSET t;

  /*!
    \brief Constructor
    \param index : index of values to store
  */
  key_bitset_t(auto_index_t<KEY, T> const & index) : _bs(index.size()) {
    _bs.reset();
  }

  /*!
    \brief Copy constructor
    \param bitset : value to copy from
  */
  key_bitset_t(BITSET const & bitset) : _bs(bitset._bs) {
  }

  /*!
    \brief Assignement
    \param bitset : the bit set to assign from
  */
  BITSET & operator = (BITSET const & bitset) {
    if (this != &bitset)
      _bs = bitset._bs;
    return (*this);
  }

  /*!
    \brief Union and assignement
    \param bitset : the bit set to unite with
  */
  void operator |= (BITSET const & bitset) {
    _bs |= bitset._bs;
  }

  /*!
    \brief Intersection and assignement
    \param bitset : the bit set to intersect with
  */
  void operator &= (BITSET const & bitset) {
    _bs &= bitset._bs;
  }

  /*!
    \brief Substraction and assignement
    \param bitset : the bit set to substract
  */
  void operator -= (BITSET const & bitset) {
    _bs -= bitset._bs;
  }

  /*!
    \brief Inclusion predicate
    \param bitset : the bit set compared to
    \return True if included into bitset,
    false otherwise
  */
  bool operator <= (BITSET const & bitset) const {
    return _bs.is_subset_of(bitset._bs);
  }

  /*!
    \brief Equality predicate
    \param bitset : the bit set compared to
    \return True if equal to bitset,
    false otherwise
  */
  bool operator == (BITSET const & bitset) const {
    return (_bs == bitset._bs);
  }

  /*!
    \brief Disequality predicate
    \param bitset : the bit set compared to
    \return True if different from bitset,
    false otherwise
  */
  bool operator != (BITSET const & bitset) const {
    return (_bs != bitset._bs);
  }

  /*!
    \brief Non-empty intersection predicate
    \param bitset : the bit set compared to
    \return True if non-empty intersection with bitset,
    false otherwise
  */
  bool intersects(BITSET const & bitset) const {
    return _bs.intersects(bitset._bs);
  }

  /*!
    \brief Empties the bit set
  */
  void clear() {
    _bs.reset();
  }

  /*!
    \brief Fills the bit set with all keys according to size (i.e. index
    size by construction, see key_bitset_t::key_bitset_t)
  */
  void fill() {
    _bs.set();
  }

  /*!
    \brief Adds (key of) value t
    \param t : value to add
    \param index : for indexing t
    \throw std::out_of_range : when t is not indexed
  */
  void add(T const & t, index_t<KEY, T> const & index) {
    add(index(t));
  }

  /*!
    \brief Adds key
    \param k : key to add
  */
  void add(KEY const & k) {
    _bs.set(k);
  }

  /*!
    \brief Adds all keys in a collection
    \tparam COLLECTION : type of collection
    \param collection : collection of keys to add
    \post all keys in collection have been added to the bit set
   */
  template <class COLLECTION>
  void add(key_collection_t<KEY, T, COLLECTION> const & collection) {
    for (KEY const & k : collection)
      _bs.set(k);
  }

  /*!
    \brief Removes (key of) value t
    \param t : value to remove
    \param index : for indexing t
    \throw std::out_of_range : when t is not indexed
  */
  void remove(T const & t, index_t<KEY, T> const & index) {
    remove(index(t));
  }

  /*!
    \brief Removes key k
  */
  void remove(KEY const & k) {
    _bs.reset(k);
  }

  /*!
    \brief Removes all keys in a collection
    \tparam COLLECTION : type of collection
    \param collection : collection of keys to remove
    \post all keys in collection have been removed from the bit set
   */
  template <class COLLECTION>
  void remove(key_collection_t<KEY, T, COLLECTION> const & collection) {
    for (KEY const & k : collection)
      _bs.reset(k);
  }

  /*!
    \brief Hash function
    \return Hash code for bit set
  */
  size_t hash() const {
    size_t seed = global_t::instance().hash_seed();

    boost::hash_combine(seed, _bs.size());
    auto i = _bs.find_first();
    while (i != _bs.npos) {
      boost::hash_combine(seed, i);
      i = _bs.find_next(i);
    }

    return seed;
  }

  /*!
    \brief Eptiness predicate
    \return True if bit set is empty,
    false otherwise
  */
  bool empty() const {
    return _bs.none();
  }

  /*!
    \brief Finds (key of) value t
    \param t : value to find
    \param index : to index t
    \return True if (key of) value t is in bit set,
    false otherwise
    \throw std::out_of_range : when t is not indexed
  */
  bool find(T const & t, index_t<KEY, T> const & index) const {
    return find(index(t));
  }
  
  /*!
    \brief Finds key k
    \param k :key to find
    \return True if k is in bit set,
    false otherwise
  */
  bool find(KEY const & k) const {
    return _bs[k];
  }

  /*!
    \brief Size (number of bits)
    \return Size of bit set
  */
  size_t size() const {
    return _bs.count();
  }

  /*!
    \brief Output a bit set
    \param output : where to output the bit set
    \param index : to decode keys in bit set
    \post The bit set has been output to output
  */
  void output(std::ostream & output, index_t<KEY, T> const & index) const {
    for (auto it = this->begin(); it != this->end(); ++it) {
      if (it != this->begin())
	output << ",";
      output << index(*it);
    }
  }

  
protected:
  /* IMPLEMENTATION NOTE: we use Boost dynamic_bitset with blocks of size
     unsigned char (instead of default unsigned int) to avoid wasting memory.
     This won't impact performances since we don't use operations (like bit
     shifting) that cross blocks.
   */

  /*!
    \brief Internal representation of key bitsets
   */
  typedef boost::dynamic_bitset<unsigned char> dynamic_bitset_t;


public:
  /*!
    \class iterator
    \brief Iterator on the bit set
  */
  class iterator : public std::iterator<std::forward_iterator_tag, T> {
  private:
    dynamic_bitset_t::size_type _current; /*!< current bit */
    dynamic_bitset_t const & _bs;         /*!< bit set */
  public:
    /*!
      \brief Constructor
      \param current : reference of the current bit
      \param bs : bit set to iterate over
      \post this refers to the first bit set from current in bs if any, or to
      the passed-the-end value
    */
    iterator(dynamic_bitset_t::size_type current,
	     dynamic_bitset_t const & bs) : _current(current), _bs(bs) {
      if ((_current < _bs.npos) && (! _bs[_current]))
	_current = _bs.find_next(_current);
    }

    /*!
      \brief Copy constructor
      \param it : iterator to copy
      \post this is a copy of it
    */
    iterator(iterator const & it) : _current(it._current),
				    _bs(it._bs) {
    }

    /*!
      \brief Assignement
      \param it : iterator to assign from
      \post this is a copy of it
    */
    iterator & operator = (iterator const & it) {
      if (this != &it) {
	_current = it._current;
	_bs = it._bs;
      }
      return (*this);
    }

    /*!
      \brief Jumps to next set bit
      \return An iterator to the next set bit if any
      \pre this does not point to the passed the end value (not checked)
      \post this has been updated to point to the next set bit if any, or to
      the passed-then-end value otherwise
    */
    iterator & operator ++ () {
      _current = _bs.find_next(_current);
      return (*this);
    }

    /*!
      \brief Equality predicate
      \param it : iterator to compare to
      \return True if this is equal to it, false otherwise
    */
    bool operator == (iterator const & it) const {
      return ((_current == it._current) && (_bs == it._bs));
    }

    /*!
      \brief Disequality predicate
      \param it : iterator to compare to
      \return True if different from it, false otherwise
    */
    bool operator != (iterator const & it) const {
      return (! (*this == it));
    }

    /*!
      \brief Access to current bit
      \return Key referenced by iterator
      \pre this does not point to the passed-the-end value (not checked)
    */
    KEY const operator * () const {
      return _current;
    }
  };

  /*!
    \brief Iterator
    \return Reference on first value
  */
  iterator const begin() const {
    return iterator(_bs.find_first(), this->_bs);
  }
  
  /*!
    \brief Iterator (see key_bitset_t::begin)
    \return Reference to the passed-the-end value
  */
  iterator const end() const {
    return iterator(_bs.npos, this->_bs);
  }
protected:
  dynamic_bitset_t _bs; /*!< Bit set */
};


/*!
  \brief Hash function compatible with boost library
  \tparam KEY : type of keys, supposed to be an unsigned integer type
  \tparam T : type of values
  \tparam BITSET : see ::key_bitset_t
  \param set : bit set to hash
  \return Hash code of set
*/

template <class KEY, class T, class BITSET>
size_t hash_value(key_bitset_t<KEY, T, BITSET> const & bitset) {
  return bitset.hash();
}


/*!
  \brief A function that sets a bit set from a string of comma-separated names  
  \tparam KEY : type of keys
  \tparam BITSET : see ::key_bitset_t
  \param bitset : value to set
  \param s : string of comma-separated names
  \param index : for encoding names into KEYs
*/
template <class KEY, class BITSET>
void set(key_bitset_t<KEY, std::string, BITSET> & bitset,
	 std::string const & s,
	 index_t<KEY, std::string> const & index) {
  std::vector<std::string> v;
  
  parse_id_list(s, v);

  bitset.clear();
  for (std::string & name : v) {
    bitset.add(name, index);
  }
}

#endif // __TCHECKER_KEY_SET_HH__

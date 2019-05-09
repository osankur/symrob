#ifndef __TCHECKER_INDEX_HH__
#define __TCHECKER_INDEX_HH__

#include <limits>
#include <ostream>
#include <stdexcept>

#include <boost/container/flat_map.hpp>

/*!
  \file index.hh
  \brief An index
*/


/*!
  \class index_t
  \tparam KEY : type of keys
  \tparam T : type of values
  \brief Stores an index (KEY,T)
*/
template <class KEY, class T> class index_t {

  /*!
    \brief KEY -> T map type
  */
  typedef typename boost::container::flat_map<KEY, T> left_map_t;

  /*!
    \brief T -> KEY map type
   */
  typedef typename boost::container::flat_map<T, KEY> right_map_t;

public:
  /*!
    \brief Constructor
  */
  index_t() {
    clear();
  }

  /*!
    \brief Copy constructor
    \param idx : index to build from
    \post The instance is a copy of idx
  */
  index_t(index_t<KEY, T> const & idx) : _left(idx._left),
					 _right(idx._right),
					 _size(idx._size) {
  }

  /*!
    \brief Assignment operator
    \param idx : index to assign from
    \post The instance is a copy of idx
  */
  index_t<KEY, T> & operator = (index_t<KEY, T> const & idx) {
    if (this != &idx) {
      _left = idx._left;
      _right = idx._right;
      _size = idx._size;
    }

    return *this;
  }

  /*!
    \brief Gives key of value t
    \param t : value to look for
    \return Key of t
    \throw std::out_of_range : when t is not indexed
  */
  KEY const & operator() (T const & t) const {
    try {
      return _right.at(t);
    }
    catch(std::out_of_range e) {
      throw std::out_of_range("*** index_t::operator(): unknown value");
    }
  }

  /*!
    \brief Gives value of key k
    \param k : key to look for
    \return Value with key k
    \throw std::out_of_range : when k is not in the range of keys
  */
  T const & operator() (KEY const & k) const {
    try {
      return _left.at(k);
    }
    catch(std::out_of_range e) {
      throw std::out_of_range("*** index_t::operator(): unknown key");
    }
  }

  /*!
    \brief Adds t wit hkey k
    \param t : value to add
    \param k : key of t
    \throw std::length_error : when maximum size is exceeded
  */
  void add(KEY const & k, T const & t) {
    if (_size == std::numeric_limits<size_t>::max())
      throw std::length_error("*** index_t::add: maximum size exceeded");
    _left.insert( typename left_map_t::value_type(k, t) );
    _right.insert( typename right_map_t::value_type(t, k) );
    ++_size;
  }
  
  /*!
    \brief Clears index
  */
  void clear() {
    _left.clear();
    _right.clear();
    _size = 0;
  }

  /*!
    \brief Gets the size of index
    \return Size of index
  */
  size_t size() const {
    return _size;
  }

  /*!
    \brief Finds a value
    \param t : value to look for
    \return True if t belongs to index,
    false otherwise
  */
  bool find(T const & t) const {
    return ( _right.find(t) != _right.end() );
  }

  /*!
    \brief Finds a key
    \param key : key to look for
    \return true if key belongs to index, false otherwise
  */
  bool find(KEY const & key) const {
    return ( _left.find(key) != _left.end() );
  }

  /*!
    \brief Finds a value and retrieves corresponding key
    \param t : value to look for
    \param key : set to the key of t if found
    \return True if t belongs to index,
    false otherwise
    \post key has been set to the key of t if found
  */
  bool find(T const & t, KEY & key) const {
    auto it = _right.find(t);

    if (it == _right.end())
      return false;

    key = it->second;
    return true;
  }

  /*!
    \brief Output index
    \param output : where to output
    \post The index has been output to output
  */
  void output(std::ostream & output) const {
    for (auto it = _left.begin(); it != _left.end(); ++it) {
      if (it != _left.begin())
	output << ",";
      output << (*it).second << "(" << (*it).first << ")";
    }
  }

  /*!
    \brief Iterator on index
  */
  class iterator : public left_map_t::const_iterator {
  public:
    /*!
      \brief Constructor
    */
    iterator(typename left_map_t::const_iterator it)
      : left_map_t::const_iterator(it)
    {}
  };

  /*!
    \brief Iterator
    \return Reference on first value
  */
  const iterator begin() const {
    return iterator(_left.begin());
  }

  /*!
    \brief Iterator (see index_t::begin)
    \return Reference out of range
  */
  const iterator end() const {
    return iterator(_left.end());
  }

protected:
  left_map_t _left;    /*!< KEY -> T map */
  right_map_t _right;  /*!< T -> KEY map */
  size_t _size;        /*!< size of index (fast access) */
};



/*!
  \class auto_index_t
  \tparam KEY : type of keys, has to be an unsigned integer type
  \tparam T : type of indexed values
  \brief Stores an index (KEY,T) where keys are automatically generated.
  
  Keys respect the order in which the values are added in the index.
*/
template <class KEY, class T> class auto_index_t : public index_t<KEY, T> {

  static_assert( !std::numeric_limits<KEY>::is_signed, "KEY must be unsigned" );

public:
  /*!
    \brief Constructor
  */
  auto_index_t() : index_t<KEY, T>() {
    clear(); // Sets _id to 0
  }

  /*!
    \brief Copy constructor
    \param idx : index to build from
    \post The instance is a copy of idx
  */
  auto_index_t(auto_index_t<KEY, T> const & idx) : index_t<KEY, T>(idx),
						   _key(idx._key) {
  }

  /*!
    \brief Assignment operator
    \param idx : index to assign from
    \post The instance is a copy of idx
  */
  auto_index_t<KEY, T> & operator = (auto_index_t<KEY, T> const & idx) {
    if (this != &idx) {
      this->index_t<KEY, T>::operator = (idx);
      _key = idx._key;
    }

    return *this;
  }

  /*!
    \brief Adds t (with next available key)
    \param t : value to add
    \throw std::length_error : when maximum key is exceeded
    \throw std::invalid_argument : when t is already indexed
  */
  const KEY add(T const & t) {
    if (_key < this->_size)   // overflow on _key
      throw std::length_error("*** auto_index_t::add: maximum index exceeded");
    if (this->index_t<KEY, T>::find(t))
      throw std::invalid_argument("*** auto_index_t::add: already in index");
    this->index_t<KEY, T>::add(_key, t);
    ++_key;

    return (_key - 1); // key of t
  }
  
  /*!
    \brief Clears index
  */
  void clear() {
    this->index_t<KEY, T>::clear();
    _key = 0;
  }

  /*!
    \brief Lightweight iterator on keys

    Usage: for ( KEY i = ibegin(); i < iend(); ++i )

    \param k : key to start from
    \return Reference on key k
  */
  KEY ibegin(KEY const & k = 0) const {
    return k;
  }

  /*!
    \brief Lightweight iterator on keys (see index_t::ibegin)
  */
  KEY iend() const {
    return _key;
  }

protected:
  KEY _key;                  /*!< next key available */
};


#endif // __TCHECKER_INDEX_HH__

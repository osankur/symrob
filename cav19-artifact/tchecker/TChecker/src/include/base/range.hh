#ifndef __TCHECKER_RANGE_HH__
#define __TCHECKER_RANGE_HH__

#include <cassert>
#include <iostream>
#include <type_traits>
#include <vector>

/*!
  \file range.hh
  \brief Range iterators
 */


/*!
  \class range_t
  \brief Generic Gang-of-for range for forward iteration
  \tparam R : type of reference to current element
*/
template <class R>
class range_t {
public:
  /*!
    \brief reference type
  */
  typedef R reference;

  /*!
    \brief Destructor
  */
  virtual ~range_t() = default;

  /*!
    \brief Moves to first element in range
    \post this references the first element in range
  */
  virtual void first() = 0;

  /*!
    \brief Accessor
    \pre not at_end()
    \return current element in range
  */
  virtual R current() = 0;

  /*!
    \brief Moves to next element in range
    \pre not at_end()
    \post this references the next element in range
  */
  virtual void advance() = 0;

  /*!
    \brief Checks range is over
    \return true if the range has been entirely enumerated, false otherwise
  */
  virtual bool at_end() = 0;
};



/*!
  \class iterator_range_t
  \brief Range over an STL-like iterator
  \tparam I : type of iterator
  \taparm R : type of reference to current element
*/
template <class I,
	  class R = typename I::reference>
class iterator_range_t : public range_t<R> {
public:
  /*!
    \brief Contructor
    \param begin : iterator pointing to first element
    \param end : iterator pointing after the last element
    \post this ranges from begin to end
  */
  iterator_range_t(I const & begin, I const & end) : _current(begin),
						     _begin(begin),
						     _end(end) {
  }

  /*!
    \brief Copy constructor
    \param r : range to copy
    \post this is a copy of r
  */
  iterator_range_t(iterator_range_t const & r) : _current(r._current),
						 _begin(r._begin),
						 _end(r._end) {
  }

  /*!
    \brief Destructor
  */
  virtual ~iterator_range_t() = default;

  /*!
    \brief see range_t::first
  */
  virtual void first() {
    _current = _begin;
  }

  /*!
    \brief see range_t::current
  */
  virtual R current() {
    return (* _current);
  }

  /*!
    \brief see range_t::advance
  */
  virtual void advance() {
    ++ _current;
  }

  /*!
    \brief see range_t::at_end
  */
  virtual bool at_end() {
    return (_current == _end);
  }
protected:
  I _current, /*!< Iterator to current element */
    _begin,   /*!< Iterator to first element */
    _end;     /*!< Iterator past-the-last element */
};



/*!
  \class container_range_t
  \brief Range over a container that provides begin() and end() methods
  \tparam C : type of container
  \tparam I : type of iterator over C
  \tparam R : type of reference to current element
*/
template <class C,
	  class I = typename C::iterator,
	  class R = typename I::reference >
class container_range_t : public iterator_range_t<I, R> {
public:
  /*!
    \brief Constructor
    \param c : container
    \post this ranges over the elements in c
  */
  container_range_t(C & c) : iterator_range_t<I, R>(c.begin(), c.end()) {}

  /*!
    \brief Copy constructor
    \param r : range to copy
    \post this is a copy of r
  */
  container_range_t(container_range_t const & r) : iterator_range_t<I, R>(r) {}

  /*!
    \brief Destructor
  */
  virtual ~container_range_t() = default;
};



/*!
  \class proxy_range_t
  \brief Range with access to elements through a proxy. This class provides
  the methods that are common to all proxy ranges. The proxy itself should
  be implemented by method current() in a derived class.
  \tparam RANGE : type of range
  \tparam R : type of reference to current element
*/
template <class RANGE,
	  class R>
class proxy_range_t : public range_t<R> {
public:
  /*!
    \brief Constructor
    \param r : range
    \post this acts as a proxy on top of r ans currently points to the first
    element in r
  */
  proxy_range_t(RANGE const & r) : _r(r) {
    first();
  }

  /*!
    \brief Copy constructor
    \param r : range to copy from
    \post this is a copy of r
  */
  proxy_range_t(proxy_range_t const & r) : _r(r._r) {}

  /*!
    \brief Destructor
  */
  virtual ~proxy_range_t() = default;

  /*!
    \brief see range_t::first
  */
  virtual void first() { return _r.first(); }

  /*!
    \brief see range_t::advance
  */
  virtual void advance() { _r.advance(); }

  /*!
    \brief see range_t::at_end
  */
  virtual bool at_end() { return _r.at_end(); }
protected:
  RANGE _r; /*!< Range behind the proxy */
};



/*!
  \class filter_range_t
  \tparam RANGE : type of filtered range
  \brief Filtered range
*/
template <class RANGE>
class filter_range_t {
public:
  /*!
    \brief Constructor
    \param r : filtered range
    \param filter : filtering predicate
    \post this is a range over the elements of r that match filter that points
    the first filtered value
  */
  filter_range_t(RANGE const & r,
		 std::function< bool(typename RANGE::reference) > filter)
    : _r(r), _filter(filter) {
    first();
  }

  /*!
    \brief Copy constructor
    \param r : range to copy
    \post this is a copy of r
  */
  filter_range_t(filter_range_t const & r) : _r(r._r), _filter(r._filter)
  {}

  /*!
    \brief Destructor
  */
  virtual ~filter_range_t() = default;

  /*!
    \brief see range_t::first
    \post this points to first filtered value
  */
  virtual void first() {
    _r.first();
    if ( (! at_end()) && (! _filter(current())) )
      advance();
  }

  /*!
    \brief see range_t::current
    \pre ! at_end()
    \return filtered value that is pointed to
  */
  virtual typename RANGE::reference current() {
    assert( ! at_end() );
    return _r.current();
  }

  /*!
    \brief see range_t::advance
    \pre ! at_end()
    \post this points the next filtered value
  */
  virtual void advance() {
    assert( ! at_end() );
    do {
      _r.advance();
    }
    while( (! at_end()) && (! _filter(current())) );
  }

  /*!
    \brief see range_t::at_end
    \return true if all filtered elements have been exhausted, false otherwise
  */
  virtual bool at_end() {
    return _r.at_end();
  }
protected:
  RANGE _r;   /*!< Range to filter */
  std::function< bool(typename RANGE::reference) > _filter; /*!< Predicate */
};



/*!
  \class chain_range_t
  \brief Sequential composition of two ranges
  \tparam RANGE1 : type of first range
  \tparam RANGE2 : type of second range
  \tparam R : type of reference to current element
  \note RANGE1::reference and RANGE2::reference should coincide with R
*/
template <class RANGE1,
	  class RANGE2,
	  class R = typename RANGE1::reference>
class chain_range_t : public range_t<R> {

  static_assert( std::is_same<typename RANGE1::reference,
		 typename RANGE2::reference>::value,
		 "*** chain_range_t: ranges must have same reference type" );

public:
  /*!
    \brief Constructor
    \param r1 : first range
    \param r2 : second range
    \post this is a range over r1, then r2, that currently points to the first
    element of r1
  */
  chain_range_t(RANGE1 const & r1, RANGE2 const & r2) : _r1(r1),
							_r2(r2) {
    first();
  }

  /*!
    \brief Copy constructor
    \param r : range to copy
    \post this is a copy of r
  */
  chain_range_t(chain_range_t<RANGE1, RANGE2, R> const & r) : _r1(r._r1),
							      _r2(r._r2)
  {}

  /*!
    \brief Destrcutor
  */
  virtual ~chain_range_t() = default;

  /*!
    \brief see range_t::first
  */
  virtual void first() {
    _r1.first();
    _r2.first();
  }

  /*!
    \brief see range_t::current
  */
  virtual R current() {
    if ( _r1.at_end() ) {
      assert( (! _r2.at_end()) );
      return _r2.current();
    }
    return _r1.current();
  }

  /*!
    \brief see range_t::advance
  */
  virtual void advance() {
    if ( _r1.at_end() ) {
      assert( (! _r2.at_end()) );
      _r2.advance();
    } else
      _r1.advance();
  }

  /*!
    \brief see range_t::at_end
  */
  virtual bool at_end() {
    return ( _r1.at_end() && _r2.at_end() );
  }
protected:
  RANGE1 _r1; /*!< First range */
  RANGE2 _r2; /*!< Second range */
};



/*!
  \class chain_iterator_range_t
  \brief Sequential composition of a range of ranges
  \tparam RANGE : type of range of ranges
  \tparam R : type of reference in the ranges inside the range of ranges
*/
template <class RANGE,
	  class R>
class chain_iterator_range_t : public range_t<R> {
public:
  /*!
    \brief Constructor
    \param r : range of ranges
    \post this has been built as a chain range on r that currently point to the
    first element
  */
  chain_iterator_range_t(RANGE const & r) : _r(r) {
    first();
  }

  /*!
    \brief Copy constructor
    \param r : chain interator range to copy
    \post this has been initialized to a copy of r
  */
  chain_iterator_range_t(chain_iterator_range_t const & r) : _r(r._r) {}

  /*!
    \brief Destructor
  */
  virtual ~chain_iterator_range_t() = default;

  /*!
    \brief Moves to first element in range
    \post this references the first element in range
  */
  virtual void first() {
    for ( _r.first(); ! _r.at_end(); _r.advance() )
      _r.current().first();
    _r.first();
    if ( (! _r.at_end()) && _r.current().at_end() )
      advance();
  }

  /*!
    \brief Accessor
    \pre not at_end()
    \return current element in range
  */
  virtual R current() {
    assert( (! _r.at_end()) );
    return _r.current().current();
  }

  /*!
    \brief Moves to next element in range
    \pre not at_end()
    \post this references the next element in range
  */
  virtual void advance() {
    assert( (! _r.at_end()) );
    do {
      if (_r.current().at_end())
	_r.advance();
      else
	_r.current().advance();
    }
    while ( (! _r.at_end()) && _r.current().at_end() );
  }

  /*!
    \brief Checks range is over
    \return true if the range has been entirely enumerated, false otherwise
  */
  virtual bool at_end() {
    return _r.at_end();
  }
protected:
  RANGE _r;  /*!< Range of ranges */
};



/*!
  \brief Counts elements in a range
  \tparam RANGE : type of range
  \param r : range to count
  \return number of elements from r's current element to last element in r
  \post r.at_end()
 */
template <class RANGE>
size_t count(RANGE & r) {
  size_t c = 0;
  for ( ; ! r.at_end(); r.advance() )
    ++c;
  return c;
}


/*!
  \brief Finds an element in a range
  \tparam RANGE : type of range
  \param r : range to search
  \param p : predicate over r elements
  \return true if an elements between r's current value and r's last value
  satisfies p, false otherwise
  \post r.at_end() if no element has been found, otherwise r.current() points
  to an element that satisfies p
 */
template <class RANGE>
bool find(RANGE & r, std::function<bool(typename RANGE::reference x)> p) {
  for ( ; ! r.at_end(); r.advance() )
    if (p(r.current()))
      return true;
  return false;
}


/*!
  \brief Finds an element in a range
  \tparam RANGE : type of range
  \param r : range to search
  \param e : element to find
  \return true if e has been found between r's current value and r's last value,
  false otherwise
  \post r.at_end() if e has not been found, otherwise r.current() points to e
 */
template <class RANGE>
bool find(RANGE & r, typename RANGE::reference e) {
  return find(r, [e] (typename RANGE::reference x) { return (x == e); });
}

#endif // __TCHECKER_RANGE_HH__

#ifndef __TCHECKER_PTR_HH__
#define __TCHECKER_PTR_HH__

#include <functional>
#include <type_traits>

#include <boost/functional/hash.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>


/*
  \file ptr.hh
  \brief Pointers and related functions
*/


/*!
  \class ptr_delegate_hash
  \tparam T : type of pointed value
  \tparam PTR : type of pointer, must be a pointer type
  \brief Delegates hashing to pointed value
*/
template <class T, class PTR = T *>
class ptr_delegate_hash : public std::function< std::size_t(PTR) > {

  // IMPLEMENTATION NOTE: does not compile with PTR = sp_T<>
  //static_assert( std::is_pointer<PTR>::value, "PTR must be a pointer type" );

public:
  /*!
    \brief Hash function
    \param p : pointer to value to hash
    \return Hash code for *p
  */
  size_t operator() (PTR p) const {
    boost::hash<T> hasher;
    return hasher(*p);
  }
};


/*!
  \class ptr_delegate_equal_to
  \tparam T : type of pointed value
  \tparam PTR : type of pointer, must be a pointer type
  \brief Delegates equality checking to pointed value
*/
template <class T, class PTR = T *>
class ptr_delegate_equal_to : public std::function< bool(PTR, PTR) > {

  // IMPLEMENTATION NOTE: does not compile with PTR = sp_T<>
  //static_assert( std::is_pointer<PTR>::value, "PTR must be a pointer type" );

public:
  /*!
    \brief Equality predicate
    \param p1 : pointer to 1st value to compare
    \param p2 : pointer to 2nd value to compare
    \return True if values pointed to by p1 and p2 are equal, false otherwise
  */
  bool operator() (PTR p1, PTR p2) const {
    return ( *p1 == *p2 );
  }
};


/*!
  \class sp_t
  \brief Shared pointer
  \tparam T : the type of value pointed to
 */
template <class T> class sp_t : public boost::shared_ptr<T> {
public:
  /*!
    \brief Constructor
  */
  sp_t() : boost::shared_ptr<T>() {
  }

  /*!
    \brief Constructor
    \param p : value to point to
    \post Instance points to p
  */
  template <class Y> explicit sp_t(Y * p) : boost::shared_ptr<T>(p) {
  }

  /*!
    \brief Constructor with type cast from Y to T (if allowed)
    \param p : value to point to
    \post Instance points to p
  */
  template <class Y> sp_t(sp_t<Y> const & p) : boost::shared_ptr<T>(p) {
  }

  /*!
    \brief Constructor
    \param p : shared pointer to built from
    \post Instance shares pointed value with p
  */
  sp_t(boost::shared_ptr<T> const & p) : boost::shared_ptr<T>(p) {
  }

  /*!
    \brief Copy-constructor
  */
  sp_t(sp_t<T> const & r) : boost::shared_ptr<T>(r) {
  }

  /*!
    \brief Accessor

    The implementation in boost::shared_ptr checks that the internal pointer
    does not point to nullptr using BOOST_ASSERT. This costs a lot. It can be
    deactivated using a macro, but we choose to override the method to keep
    assertions elsewhere.

    \return A reference to the value pointed to by the instance
    \pre Does not point to nullptr
  */
  T & operator * () const {
    assert(this->get() != nullptr);
    return (* this->get());
  }

  /*!
    \brief Accessor

    The implementation in boost::shared_ptr checks that the internal pointer
    does not point to nullptr using BOOST_ASSERT. This costs a lot. It can be
    deactivated using a macro, but we choose to override the method to keep
    assertions elsewhere.

    \return The value pointed to by the instance
    \pre Does not point to nullptr
  */
  T * operator -> () const {
    assert(this->get() != nullptr);
    return (this->get());
  }

  /*!
    \brief Delegates hashing to pointed value
  */
  typedef ptr_delegate_hash< T, sp_t<T> > delegate_hash;

  /*!
    \brief Delegates equality checking to pointed value
  */
  typedef ptr_delegate_equal_to< T, sp_t<T> > delegate_equal_to;
};


/*!
  \brief Makes a new shared pointer and allocates memory for pointed value
  \tparam T : type of pointed value
  \return A shared pointer that points a newly allocated value of type T
*/
template <class T> sp_t<T> make_sp() {
  return boost::make_shared<T>();
}

/*!
  \brief Makes a new shared pointer and allocates memory for pointed value
  \tparam T : type of pointed value
  \tparam ARGS : type of arguments to T's constructor
  \param args : arguments to T's constructor
  \return A shared pointer that points a newly allocated value of type T built
  with parameters args
*/
template <class T, class ARG1, class... ARGS>
sp_t<T> make_sp(ARG1 && arg1, ARGS && ... args) {
  return boost::make_shared<T>(arg1,args...);
}

#endif // __TCHECKER_PTR_HH__

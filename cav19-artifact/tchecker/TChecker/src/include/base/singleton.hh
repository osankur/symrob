#ifndef __TCHECKER_SINGLETON_HH__
#define __TCHECKER_SINGLETON_HH__

/*!
  \file singleton.hh
  \brief Implements the singleton design-pattern
*/

/*!
  \class singleton_t
  \brief Implementation of the singleton design-pattern
  \tparam T : class to make singleton
*/
template <class T> class singleton_t {
protected:
  static T * _t; /*!< Unique instance of class T */

  /*!
    \brief Constructor
  */
  singleton_t() = default;

  /*!
    \brief Destructor
  */
  ~singleton_t() = default;

public:
  /*!
    \brief Access singleton
    \return The instance of T
   */
  static T & instance() {
    if (_t == nullptr)
      _t = new T;

    return (*_t);
  }
};

// Static variable declaration

template <class T> T * singleton_t<T>::_t = nullptr;

#endif // __TCHECKER_SINGLETON_HH__

#ifndef __TCHECKER_GLOBAL_HH__
#define __TCHECKER_GLOBAL_HH__

#include <string>

#include "base/clockindex.hh"
#include "base/labelindex.hh"
#include "base/singleton.hh"
#include "syntax/system_fwd.hh"

/*!
  \file global.hh
  \brief Global definition: variables, constants, etc
*/


/*!
  \class global_frozen_exception
  \brief Thrown when global_t is frozen
*/
class global_frozen_exception : public std::logic_error {
public:
  explicit global_frozen_exception(std::string const & what_arg);
  ~global_frozen_exception() noexcept (true) = default;
};


/*!
  \class global_t
  \brief Provides global definitions: variables, constants, etc
*/
class global_t : public singleton_t<global_t> {
  
  friend class singleton_t<global_t>; // Grants access to cons/des

public:
  /*!
    \brief Freeze all definitions

    Only the immutable accessors are enabled once global_t has been frozen.
  */
  void freeze();

  // Cache of zones
  const std::size_t cache_shared_zone_size = 65536; // must be a power of 2


  // Clock index

  /*!
    \brief Access to clock index
    \return The global clock index
    \throw global_frozen_exception : when in frozen mode
  */
  clock_index_t & clock_index();

  /*!
    \brief Access to immutable clock index
    \return A constant reference to the global clock index
  */
  clock_index_t const & clock_index() const;




  // Hash seed

  /*!
    \brief Value of hash seed
    \return Hash seed
  */
  size_t hash_seed() const;

  /*!
    \brief Sets value of hash seed
    \param seed : new hash seed
  */
  void hash_seed(size_t seed);



  // Label index

  /*!
    \brief Access to label index
    \return The global label index
    \throw global_frozen_exception : when in frozen mode
  */
  label_index_t & label_index();

  /*!
    \brief Access to immutable label index
    \return A constant reference to the global label index
  */
  label_index_t const & label_index() const;



  // Reserved names

  /*!
    \enum global_t::reserved_names_t
    Symbolic identifiers for reserved names
  */
  typedef enum {
    RN_FAKE_CLOCK = 0,  /*!< Fake clock used to represent value 0 */
    RN_SNZ1,            /*!< For strongly non-zeno construction */
    RN_SNZ2,            /*!< For strongly non-zeno construction */
    RN_COUNT            /*!< Not a name (for counting names only) */
  } reserved_names_t;

  /*!
    \brief Access reserved names
    \param rn : identifier of the reserved name (symbolic name)
    \return The real name associated to symbolic name rn
    \throw std::invalid_argument : when RN_COUNT is given as a parameter
  */
  std::string const & reserved_name(reserved_names_t rn) const;

  /*!
    \brief Access reserved names
    \param name : name to check
    \return True if name is reserved, false otherwise
  */
  bool reserved_name(std::string const & name) const;
private:
  /*!
    \brief Constructor
  */
  global_t();

  /*!
    \brief Destructor
  */
  ~global_t();

  clock_index_t _ci;  /*!< Clock index */
  bool _frozen;       /*!< Frozen flag */
  size_t _hash_seed;  /*!< Hash seed */
  label_index_t _li;  /*!< Label index */

  /*!< Table of reserved names */
  std::string const _reserved_names[RN_COUNT];
};

#endif // __TCHECKER_GLOBAL_HH__

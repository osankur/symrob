#ifndef __TCHECKER_CLOCKSET_HH__
#define __TCHECKER_CLOCKSET_HH__

#include <ostream>
#include <string>

#include "base/global.hh"
#include "base/clockindex.hh"
#include "base/keyset.hh"

/*!
  \file clockset.hh
  \brief Collection and set of clocks using ::clock_index_t, with default
  reference to global_t::clock_index()
*/

/*!
  \class clocks_t
  \brief A collection of clock IDs.
*/
class clocks_t : public key_collection_t<clock_id_t,
					 std::string,
					 clocks_t> {
public:
  /*!
    \brief Constructor
    \param s : a comma-separated list of clock names to initialize the
    collection
    \param index : a clock index for encoding clock names
  */
  clocks_t(std::string const & s = "",
	   clock_index_t const & index = global_t::instance().clock_index());


  using key_collection_t<clock_id_t, std::string, clocks_t>::add;

  /*!
    \brief Adds key of value t to the collection
    \param t : value to add
    \param index : for indexing t
    \throw std::out_of_range : when t is not indexed
  */
  void add(std::string const & t,
	   clock_index_t const & index = global_t::instance().clock_index());


  using key_collection_t<clock_id_t, std::string, clocks_t>::find;

  /*!
    \brief Finds (key of) t in a collection
    \param t : the value to find
    \param index : to encode t
    \return True when (key of t) belongs to the collection,
    false otherwise
  */
  bool find(std::string const & t,
	    clock_index_t const & index = 
	    global_t::instance().clock_index()) const;
  
  /*!
    \brief Output the collection
    \param output : where to output
    \param index : to decode keys in collection
    \post The collection has been output to output
  */
  void output(std::ostream & output,
	      clock_index_t const & index =
	      global_t::instance().clock_index()) const;
};




/*!
  \class clock_bitset_t
  \brief A set of clock IDs
*/

class clock_bitset_t : public key_bitset_t<clock_id_t,
					   std::string,
					   clock_bitset_t> {
public:
  /*!
    \brief Constructor
    \param index : clock index for encoding clock names
    \post Initialized to the empty set over index
  */
  clock_bitset_t(clock_index_t const & index =
		 global_t::instance().clock_index());
  
  /*!
    \brief Constructor
    \param s : comma-separated list of clock names for initializing the
    bit set
    \param index : clock index for encoding clock names
    \post Initialized to the set described by s over index
  */
  clock_bitset_t(std::string const & s,
		 clock_index_t const & index =
		 global_t::instance().clock_index());

  /*!
    \brief Constructor
    \param l : clock collection for intializing the bit set
    \param index : clock index for the bit set (the same as used for l)
  */
  clock_bitset_t(clocks_t const & l,
		 clock_index_t const & index =
		 global_t::instance().clock_index());

  /*!
    \brief Copy constructor
    \param cbs : value to copy from
  */
  clock_bitset_t(clock_bitset_t const & cbs);


  using key_bitset_t<clock_id_t, std::string, clock_bitset_t>::add;

  /*!
    \brief Adds (key of) value t
    \param t : value to add
    \param index : for indexing t
    \throw std::out_of_range : when t is not indexed
  */
  void add(std::string const & t,
	   clock_index_t const & index = global_t::instance().clock_index());


  using key_bitset_t<clock_id_t, std::string, clock_bitset_t>::remove;

  /*!
    \brief Removes (key of) value t
    \param t : value to remove
    \param index : for indexing t
    \throw std::out_of_range : when t is not indexed
  */
  void remove(std::string const & t,
	      clock_index_t const & index = global_t::instance().clock_index());


  using key_bitset_t<clock_id_t, std::string, clock_bitset_t>::find;

  /*!
    \brief Finds (key of) value t
    \param t : value to find
    \param index : to index t
    \return True if (key of) value t is in bit set,
    false otherwise
    \throw std::out_of_range : when t is not indexed
  */
  bool find(std::string const & t,
	    clock_index_t const & index =
	    global_t::instance().clock_index()) const;

  /*!
    \brief Output the bit set
    \param output : where to output
    \param index : to decode keys in bit set
    \post The bit set has been output to output
  */
  void output(std::ostream & output,
	      clock_index_t const & index =
	      global_t::instance().clock_index()) const;
};

#endif // __TCHECKER_CLOCKSET_HH__

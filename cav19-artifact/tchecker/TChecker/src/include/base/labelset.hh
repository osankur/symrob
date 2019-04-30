#ifndef __TCHECKER_LABELSET_HH__
#define __TCHECKER_LABELSET_HH__

#include <ostream>
#include <string>

#include "base/global.hh"
#include "base/labelindex.hh"
#include "base/keyset.hh"

/*!
  \file labeset.hh
  \brief Collection and set of labels using ::label_index_t, with default
  reference to global_t::label_index()
*/

/*!
  \class labels_t
  \brief A collection of labels IDs
*/
class labels_t : public key_collection_t<label_id_t,
					 std::string,
					 labels_t> {
public:
  /*!
    \brief Constructor
    \param s : a comma-separated list of label names to initialize the
    collection
    \param index : a label index for encoding label names
  */
  labels_t(std::string const & s = "",
	   label_index_t const & index = global_t::instance().label_index());


  using key_collection_t<label_id_t, std::string, labels_t>::add;

  /*!
    \brief Adds key of value t to the collection
    \param t : value to add
    \param index : for indexing t
    \throw std::out_of_range : when t is not indexed
  */
  void add(std::string const & t,
	   label_index_t const & index = global_t::instance().label_index());


  using key_collection_t<label_id_t, std::string, labels_t>::find;

  /*!
    \brief Finds (key of) t in a collection
    \param t : the value to find
    \param index : to encode t
    \return True when (key of t) belongs to the collection,
    false otherwise
  */
  bool find(std::string const & t,
	    label_index_t const & index = 
	    global_t::instance().label_index()) const;

  /*!
    \brief Output a collection
    \param output : where to output the collection
    \param index : to decode keys in collection
    \post The collection has been output to output
  */
  void output(std::ostream & output,
	      label_index_t const & index =
	      global_t::instance().label_index()) const;
};




/*!
  \class label_bitset_t
  \brief A set of label IDs
*/
class label_bitset_t : public key_bitset_t<label_id_t,
					   std::string,
					   label_bitset_t> {
public:
  /*!
    \brief Constructor
    \param index : label index for encoding label names
    \post Initialized to the empty set over index
  */
  label_bitset_t(label_index_t const & index =
		 global_t::instance().label_index());

  /*!
    \brief Constructor
    \param s : comma-separated list of label names for initializing the
    bit set
    \param index : label index for encoding label names
    \post Initialized to the set described by s over index
  */
  label_bitset_t(std::string const & s,
		 label_index_t const & index =
		 global_t::instance().label_index());

  /*!
    \brief Constructor
    \param l : label collection for intializing the bit set
    \param index : label index for the bit set (the same as used for l)
  */
  label_bitset_t(labels_t const & l,
		 label_index_t const & index =
		 global_t::instance().label_index());

  /*!
    \brief Copy constructor
    \param lbs : value to copy from
  */
  label_bitset_t(label_bitset_t const & lbs);


  using key_bitset_t<label_id_t, std::string, label_bitset_t>::add;

  /*!
    \brief Adds (key of) value t
    \param t : value to add
    \param index : for indexing t
    \throw std::out_of_range : when t is not indexed
  */
  void add(std::string const & t,
	   label_index_t const & index = global_t::instance().label_index());


  using key_bitset_t<label_id_t, std::string, label_bitset_t>::remove;

  /*!
    \brief Removes (key of) value t
    \param t : value to remove
    \param index : for indexing t
    \throw std::out_of_range : when t is not indexed
  */
  void remove(std::string const & t,
	      label_index_t const & index = global_t::instance().label_index());


  using key_bitset_t<label_id_t, std::string, label_bitset_t>::find;

  /*!
    \brief Finds (key of) value t
    \param t : value to find
    \param index : to index t
    \return True if (key of) value t is in bit set,
    false otherwise
    \throw std::out_of_range : when t is not indexed
  */
  bool find(std::string const & t,
	    label_index_t const & index =
	    global_t::instance().label_index()) const;

  /*!
    \brief Output a bit set
    \param output : where to output the bit set
    \param index : to decode keys in bit set
    \post The bit set has been output to output
  */
  void output(std::ostream & output,
	      label_index_t const & index =
	      global_t::instance().label_index()) const;
};

#endif // __TCHECKER_LABELSET_HH__

#ifndef __TCHECKER_CONSTRAINTS_HH__
#define __TCHECKER_CONSTRAINTS_HH__

#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <dbm/constraints.h>

#include "base/clockindex.hh"
#include "base/global.hh"
/*!
  \file constraints.hh
  \brief Clock constraints

  Clock constraints make use of clock_index_t to identify clocks. It is
  assumed that the fake clock has identifier 0.

  Admissible constraints in timed automata have one of the following to forms:
         x ~ c
     x - y ~ c
  where x and y are clocks, ~ is one of <,<=,==,>=,> and c is a
  natural number. Thanks to the fake clock 0, all these constraints
  can be encoded as:
     x - y # c
  where x and y are clocks or 0 (at least one of them is not 0), # is
  either < or <= and c is an integer or infinity.

  The class symbolic::constraint_t permits the representation of clock
  constraints using this encoding. The class
  symbolic::constraint_collection_t represents a conjunction of clock
  constraints as a set of constraints.
*/



/*!
  \namespace symbolic
  \brief Symbolic tools for clock valuations
*/
namespace symbolic {

  /*!
    \class constraint_t
    \brief Clock constraint xi - xj < or <= bound. See UPPAAL's dbm library
    documentation for more details
  */
  class constraint_t : public ::constraint_t {
  public:
    /*!
      \brief Constructor
      \post The constraint has undetermined values
     */
    constraint_t();

    /*!
      \brief Constructor
      \param i : identifier of first clock
      \param j : identifier of second clock
      \param bound : bound on xi - xj
      \param strict : choose between < (when true) and <= (when false)
      \pre At most one of i and j may be 0, the fake clock identifier
      \post xi - xj # bound has been encoded where # is either < or <= depending
      on strict
    */
    constraint_t(clock_id_t i, clock_id_t j, int32_t bound, bool strict);

    /*!
      \brief Constructor
      \param i : identifier of first clock
      \param j : identifier of second clock
      \param bound : bound on xi - xj
      \param strict : choose between < (when true) and <= (when false)
      \pre At most one of i and j may be 0, the fake clock identifier
      \post xi - xj # bound has been encoded where # is either < or <= depending
      on strict
    */
    constraint_t(clock_id_t i, clock_id_t j, raw_t value);


    /*!
      \brief Zero-check predicate
      \return True if the constraint is a zero-check (i.e. x<=0), false
      otherwise
    */
    bool zero_check() const;

    /*!
      \brief Hash function
      \return Hash code of clock constraint
    */
    size_t hash() const;

    /*!
      \brief Output a constraint
      \param output : where to output the constraint
      \param index : to translate clock identifiers into clock names, defaults
      to the global clock index
      \post The constraint has been output to ostream
    */
    void output(std::ostream & output,
                clock_index_t const & index =
        global_t::instance().clock_index()) const;
  };

  /*!
    \brief Hash function compatible with boost library
    \return Hash code of clock constraint
  */
  size_t hash_value(symbolic::constraint_t const & c);







  /*!
    \class constraint_collection_t
    \brief A collection of clock constraints
  */
  class constraint_collection_t : public std::vector<symbolic::constraint_t> {
  public:
    /*!
      \brief Constructor
      \post The collection is empty
    */
    constraint_collection_t();

    /*!
      \brief Constructor
      \param s : a conjunction of clock constraints (see
      ::parse_clock_constraints for syntax)
      \param index : to encode clocks as identifiers, defaults to the global
      clock index
      \post The collection has been set to the conjunction of constraints in s
      \throw std::invalid_argument : when s is not syntactically correct
    */
    constraint_collection_t(std::string const & s,
                            clock_index_t const & index =
        global_t::instance().clock_index());

    /*!
      \brief Adds a clock constraint
      \param c : clock constraint to add
    */
    void operator += (symbolic::constraint_t const & c);

    /*!
      \brief Appends a constraint collection
      \param collection : constraint collection to append
    */
    void operator += (constraint_collection_t const & collection);

    /*!
      \brief Hash function
      \return Hash code of the collection
    */
    size_t hash() const;

    /*!
      \brief Output a constraint collection
      \param output : where to output the collection
      \param index : to translate clock identifiers into clock names, defaults
      to the global clock index
      \post The collection has been output to ostream
    */
    void output(std::ostream & output,
                clock_index_t const & index =
        global_t::instance().clock_index()) const;
  };

  /*!
    \brief Hash function compatible with boost library
    \return Hash code of clock constraint
  */
  size_t hash_value(constraint_collection_t const & collection);



} // end of namespace symbolic

#endif // __TCHECKER_CONSTRAINTS_HH__

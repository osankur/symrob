#ifndef __TCHECKER_PARSERS_HH__
#define __TCHECKER_PARSERS_HH__

#include <string>
#include <utility>
#include <vector>

/*!
  \file parsers.hh
  \brief Parsers
*/


// parse_id_list


/*!
  \brief Builds a vector of identifiers from a string

  The input string is a comma-separated list of identifiers complying with
  the following grammar:
  IDLIST ::= ID ',' IDLIST | ""
  ID  ::= ['a'-'z' 'A'-Z' '_']['a'-'z' 'A'-Z' '0'-'9' '_' '.' '!' '?']+

  For instance, "x,y,z" will result in ["x", "y", "z"]. Notice that spaces
  are ignored: "x  , y" will result in ["x", "y"].

  \param s : the string to parse
  \param v : all identifiers are added to v, in the order in which they
  appear in s
  \throw std::invalid_argument : if s does dot comply with the grammar above
*/

void parse_id_list(std::string const & s, std::vector<std::string> & v);


// parse_clock_constraints

/*!
  \struct parsed_constraint_t
  \brief A clock constraint just parsed

  A clock constraint is either a comparison of a clock to a constant like
  x # c (e.g. x > 1) or the comparison of the difference of two clocks to
  a constant like x - y # c (e.g. x-y==2). See ::parse_clock_constraints
  for the syntax.

  Both forms are stored as a constraint x - y # c. The value of y is set to
  global_t::reserved_name(global_t::RN_FAKE_CLOCK) to encode the former type
  of constraints.
*/
typedef struct {
  std::string x;
  std::string y;
  std::string op;
  std::string c;
} parsed_constraint_t;

/*!
  \brief Builds a vector of parsed constraints from a string

  The input string is a conjunction of clock constraints that should comply
  with the following grammar:
  CC     ::= CONSTR | CONSTR '&&' CC
  CONSTR ::= CMP | '(' CMP ')'
  CMP    ::= TERM BINOP NAT
  TERM   ::= ID | ID '-' ID
  BINOP  ::= '<' | '<=' | '==' | '>=' | '>'
  NAT    ::= ['0'-'9']+
  ID     ::= ['a'-'z' 'A'-Z' '_']['a'-'z' 'A'-Z' '0'-'9' '_' '.']+

  For instance "(x==1) && x-y<=2 && z>7" is a valid clock constraint. Notice
  that spaces are ignored, hence "x  - y <=   2" is the same as "x-y<=2.

  \param s : the string to parse
  \param v : all constraints are parsed and added to v in the order in which
  they appear in s
  \throw std::invalid_argument : if s does dot comply with the grammar above
*/
void parse_clock_constraints(std::string const & s,
			     std::vector<parsed_constraint_t> & v);



// parse_dot_separated_ids

/*!
  \brief Builds a pair of identifiers from a string

  The input string should comply with the following grammar:
  S      ::= ID '.' ID
  ID     ::= ['a'-'z' 'A'-Z' '_']['a'-'z' 'A'-Z' '0'-'9' '_' '!' '?']+

  \param s : the string to parse
  \param p : the pair made from both IDs
  \throw std::invalid_argument : if s does dot comply with the grammar above
*/
void parse_dot_separated_ids(std::string const & s,
			     std::pair<std::string, std::string> & p);

#endif // __TCHECKER_PARSERS_HH__

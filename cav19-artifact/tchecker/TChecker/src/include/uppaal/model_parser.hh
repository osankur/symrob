#ifndef __UPPAAL_MODEL_PARSER_HH__
# define __UPPAAL_MODEL_PARSER_HH__

# include <istream>
# include "uppaal/compiled_model.hh"

namespace uppaal {
# define INSTRUCTIONS \
  INSTRUCTION(PUSH, "push") \
  INSTRUCTION(LOAD, "load") \
  INSTRUCTION(LOADN, "loadN")		\
  INSTRUCTION(LID, "lid") \
  INSTRUCTION(PLUS, "plus") \
  INSTRUCTION(MULT, "mult") \
  INSTRUCTION(DIV, "div") \
  INSTRUCTION(MOD, "mod") \
  INSTRUCTION(BAND, "band") \
  INSTRUCTION(BOR, "bor") \
  INSTRUCTION(BXOR, "bxor") \
  INSTRUCTION(BLSH, "blsh") \
  INSTRUCTION(BRSH, "brsh") \
  INSTRUCTION(AND, "and") \
  INSTRUCTION(LT, "lt") \
  INSTRUCTION(LE, "le") \
  INSTRUCTION(EQ, "eq" )\
  INSTRUCTION(MIN, "min" ) \
  INSTRUCTION(MAX, "max" ) \
  INSTRUCTION(STORE, "store") \
  INSTRUCTION(STOREN, "storeN") \
  INSTRUCTION(ASSIGNN, "assignN") \
  INSTRUCTION(INCREMENT, "increment") \
  INSTRUCTION(COMPAREN, "compareN")		\
  INSTRUCTION(UMINUS, "uminus") \
  INSTRUCTION(NOT, "not") \
  INSTRUCTION(COPY, "copy") \
  INSTRUCTION(POP, "pop") \
  INSTRUCTION(SWAP, "swap")\
  INSTRUCTION(CEXPR, "cexpr") \
  INSTRUCTION(ARRAY, "array") \
  INSTRUCTION(JMP, "jmp") \
  INSTRUCTION(JMZ, "jmpz") \
  INSTRUCTION(HALT, "halt") \
  INSTRUCTION(CALL, "call") \
  INSTRUCTION(RETURN, "return")	\
  INSTRUCTION(NOP, "nop")

  enum instruction_kind_t {
# define INSTRUCTION(enumid, id) INST_ ## enumid,
  INSTRUCTIONS
# undef INSTRUCTION
  INST_NB_INSTR
};

  extern void 
  parse_list (const std::string &s, const char *regexpsep, 
	      std::vector<std::string> &result);

  extern compiled_model_t *
  parse_model (std::istream &in) throw (std::string);
}

#endif /* !  __UPPAAL_MODEL_PARSER_HH__ */

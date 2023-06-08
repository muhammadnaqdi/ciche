#ifndef CICHE_SCANNER_H
#define CICHE_SCANNER_H

enum ciche_scanner_tag {
  HASH_TAG,
  DEFINE_TAG,
  ID_TAG,
  INT_TAG,
  SEMICOLON_TAG,
  OPENING_PARENTHESES_TAG,
  CLOSING_PARENTHESES_TAG,
  VOID_TAG,
  COMMA_TAG,
  OPENING_CURLY_BRACE_TAG,
  CLOSING_CURLY_BRACE_TAG,
  BREAK_TAG,
  CONTINUE_TAG,
  RETURN_TAG,
  IF_TAG,
  ELSE_TAG,
  WHILE_TAG,
  DO_TAG,
  FOR_TAG,
  ASSIGNMENT_TAG,
  ADD_AND_ASSIGNMENT_TAG,
  SUB_AND_SSIGNMENT_TAG,
  MUL_AND_SSIGNMENT_TAG,
  DIV_AND_SSIGNMENT_TAG,
  MOD_AND_SSIGNMENT_TAG,
  LOGICAL_OR_TAG,
  LOGICAL_AND_TAG,
  EQUAL_TAG,
  NOT_EQUAL_TAG,
  GREATER_TAG,
  LESS_TAG,
  GREATER_OR_EQUAL_TAG,
  LESS_OR_EQUAL_TAG,
  ADD_TAG,
  SUB_TAG,
  MUL_TAG,
  DIV_TAG,
  MOD_TAG,
  INC_TAG,
  DEC_TAG,
  NUM_TAG
};

struct ciche_scanner {

};

#endif /* CICHE_SCANNER_H */

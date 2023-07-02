#ifndef CICHE_SCANNER_H
#define CICHE_SCANNER_H

#include "ciche_symbol_table.h"

#include <stdio.h>

#define SCANNER_ERROR  printf("** BAD CHARACTER: %c LINE %d **", scanner->head, (int) scanner->line);  \
                       fclose(scanner->file);                                                          \
		       exit(EXIT_FAILURE);

struct ciche_token {
  enum ciche_token_tag token_tag;
  char identifier[9];
  size_t pointer;
};

struct ciche_scanner {
  FILE *file;
  int head;
  size_t line;
  bool done;
  struct ciche_token *token;
};

struct ciche_scanner *scanner = NULL;

bool ciche_is_digit(char c) {
  if (c >= 48 && c <= 57)
    return true;

  return false;
}
bool ciche_is_letter(char c) {
  if (c >= 65 && c <= 122)
    return true;

  return false;
}

bool ciche_token_init() {
  if (!scanner->token)
    return false;
  
  scanner->token->token_tag = 0;
  for (int i = 0; i < IDENTIFIER_SIZE; ++i)
    scanner->token->identifier[i] = '\0';
  scanner->token->pointer = 0;

  return true;
}

bool ciche_scanner_init(char *file_name) {
  scanner = (struct ciche_scanner *) malloc(sizeof(struct ciche_scanner));

  scanner->file = fopen(file_name, "r");
  if (!scanner->file)
    return false;
  
  scanner->head = fgetc(scanner->file);
  scanner->token = (struct ciche_token *) malloc(sizeof(struct ciche_token));
  scanner->line = 1;
  scanner->done = false;
  
  return true;
}

bool ciche_scanner_advance() {
  if (scanner->done)
    return false;
  
  ciche_token_init();
 BEGIN:
  switch (scanner->head) {
  case '\n':
    scanner->line ++;
  case ' ':
  case '\t':
    scanner->head = fgetc(scanner->file);
    goto BEGIN;
  case '#':
    scanner->head = fgetc(scanner->file);
    scanner->token->token_tag = HASH_TAG;
    break;
  case ';':
    scanner->head = fgetc(scanner->file);
    scanner->token->token_tag = SEMICOLON_TAG;
    break;
  case '(':
    scanner->head = fgetc(scanner->file);
    scanner->token->token_tag = OPENING_PARENTHESES_TAG;
    break;
  case ')':
    scanner->head = fgetc(scanner->file);
    scanner->token->token_tag = CLOSING_PARENTHESES_TAG;
    break;
  case ',':
    scanner->head = fgetc(scanner->file);
    scanner->token->token_tag = COMMA_TAG;
    break;
  case '{':
    scanner->head = fgetc(scanner->file);
    scanner->token->token_tag = OPENING_CURLY_BRACE_TAG;
    break;
  case '}':
    scanner->head = fgetc(scanner->file);
    scanner->token->token_tag = CLOSING_CURLY_BRACE_TAG;
    break;
  case '=':
    scanner->head = fgetc(scanner->file);
    if (scanner->head == '=') {
      scanner->head = fgetc(scanner->file);
      scanner->token->token_tag = EQUAL_TAG;
      break;
    }
    scanner->token->token_tag = ASSIGNMENT_TAG;
    break;
  case '+':
    scanner->head = fgetc(scanner->file);
    if (scanner->head == '=') {
      scanner->head = fgetc(scanner->file);
      scanner->token->token_tag = ADD_AND_ASSIGNMENT_TAG;
      break;
    }
    if (scanner->head == '+') {
      scanner->head = fgetc(scanner->file);
      scanner->token->token_tag = INC_TAG;
      break;
    }
    scanner->token->token_tag = ADD_TAG;
    break;
  case '-':
    scanner->head = fgetc(scanner->file);
    if (scanner->head == '=') {
      scanner->head = fgetc(scanner->file);
      scanner->token->token_tag = SUB_AND_SSIGNMENT_TAG;
      break;
    }
    if (scanner->head == '-') {
      scanner->head = fgetc(scanner->file);
      scanner->token->token_tag = DEC_TAG;
      break;
    }
    scanner->token->token_tag = SUB_TAG;
    break;
  case '*':
    scanner->head = fgetc(scanner->file);
    if (scanner->head == '=') {
      scanner->head = fgetc(scanner->file);
      scanner->token->token_tag = MUL_AND_SSIGNMENT_TAG;
      break;
    }
    scanner->token->token_tag = MUL_TAG;
    break;
  case '/':
    scanner->head = fgetc(scanner->file);
    if (scanner->head == '=') {
      scanner->head = fgetc(scanner->file);
      scanner->token->token_tag = DIV_AND_SSIGNMENT_TAG;
      break;
    }
    scanner->token->token_tag = DIV_TAG;
    break;
  case '%':
    scanner->head = fgetc(scanner->file);
    if (scanner->head == '=') {
      scanner->head = fgetc(scanner->file);
      scanner->token->token_tag = MOD_AND_SSIGNMENT_TAG;
      break;
    }
    scanner->token->token_tag = MOD_TAG;
    break;
  case '<':
    scanner->head = fgetc(scanner->file);
    if (scanner->head == '=') {
      scanner->head = fgetc(scanner->file);
      scanner->token->token_tag = LESS_OR_EQUAL_TAG;
      break;
    }
    scanner->token->token_tag = LESS_TAG;
    break;
  case '>':
    scanner->head = fgetc(scanner->file);
    if (scanner->head == '=') {
      scanner->head = fgetc(scanner->file);
      scanner->token->token_tag = GREATER_OR_EQUAL_TAG;
      break;
    }
    scanner->token->token_tag = GREATER_TAG;
    break;
  case '!':
    scanner->head = fgetc(scanner->file);
    if (scanner->head == '=') {
      scanner->head = fgetc(scanner->file);
      scanner->token->token_tag = NOT_EQUAL_TAG;
      break;
    }
    SCANNER_ERROR
  case EOF:
    scanner->done = true;
    return false;
  default:
    if (ciche_is_digit(scanner->head))
      goto NUMBER;
    if (ciche_is_letter(scanner->head))
      goto IDENTIFIER;
    SCANNER_ERROR
  }
  goto DONE;

 NUMBER:
  if (scanner->token->pointer >= 8) {
    scanner->head = fgetc(scanner->file);
    while (ciche_is_digit(scanner->head))
      scanner->head = fgetc(scanner->file);
  } else {
    scanner->token->identifier[scanner->token->pointer++] = scanner->head;
    scanner->head = fgetc(scanner->file);
    if (ciche_is_digit(scanner->head))
      goto NUMBER;
  }
  scanner->token->token_tag = NUM_TAG;
  goto DONE;

 IDENTIFIER:
  if (scanner->token->pointer >= 8) {
    scanner->head = fgetc(scanner->file);
    while (ciche_is_digit(scanner->head) || ciche_is_letter(scanner->head))
      scanner->head = fgetc(scanner->file);
  } else {
    scanner->token->identifier[scanner->token->pointer++] = scanner->head;
    scanner->head = fgetc(scanner->file);
    if (ciche_is_digit(scanner->head)  || ciche_is_letter(scanner->head))
      goto IDENTIFIER;
  }
  struct ciche_symbol_table_obj *obj = ciche_varible_create(scanner->token->identifier);
  struct ciche_symbol_table_obj *fobj;
  if (ciche_hash_map_find_obj(symbol_table, obj, &ciche_symbol_table_obj_hash, &ciche_symbol_table_obj_equals, (void **) &fobj)) {
    if (fobj->type_tag == KEYWORD_TAG) {
      scanner->token->token_tag = fobj->data.token_tag;
    } else {
      scanner->token->token_tag = ID_TAG;
    }
  } else {
    ciche_hash_map_add(symbol_table, obj, &ciche_symbol_table_obj_hash);
    scanner->token->token_tag = ID_TAG;
  }
  goto DONE;
  
 DONE:
  return true;
}

bool ciche_scanner_print() {
  if (scanner->done)
    return false;

  switch (scanner->token->token_tag) {
  case HASH_TAG:
    printf("[HASH_TAG]");
    break;
  case DEFINE_TAG:
    printf("[DEFINE_TAG]");
    break;
  case ID_TAG:
    printf("[ID_TAG ID: %s]", scanner->token->identifier);
    break;
  case INT_TAG:
    printf("[INT_TAG]");
    break;
  case SEMICOLON_TAG:
    printf("[SEMICOLON_TAG]");
    break;
  case OPENING_PARENTHESES_TAG:
    printf("[OPENING_PARENTHESES_TAG]");
    break;
  case CLOSING_PARENTHESES_TAG:
    printf("[CLOSING_PARENTHESES_TAG]");
    break;
  case VOID_TAG:
    printf("[VOID_TAG]");
    break;
  case COMMA_TAG:
    printf("[COMMA_TAG]");
    break;
  case OPENING_CURLY_BRACE_TAG:
    printf("[OPENING_CURLY_BRACE_TAG]");
    break;
  case CLOSING_CURLY_BRACE_TAG:
    printf("[CLOSING_CURLY_BRACE_TAG]");
    break;
  case BREAK_TAG:
    printf("[BREAK_TAG]");
    break;
  case CONTINUE_TAG:
    printf("[CONTINUE_TAG]");
    break;
  case RETURN_TAG:
    printf("[RETURN_TAG]");
    break;
  case IF_TAG:
    printf("[IF_TAG]");
    break;
  case ELSE_TAG:
    printf("[ELSE_TAG]");
    break;
  case WHILE_TAG:
    printf("[WHILE_TAG]");
    break;
  case DO_TAG:
    printf("[DO_TAG]");
    break;
  case FOR_TAG:
    printf("[FOR_TAG]");
    break;
  case ASSIGNMENT_TAG:
    printf("[ASSIGNMENT_TAG]");
    break;
  case ADD_AND_ASSIGNMENT_TAG:
    printf("[ADD_AND_ASSIGNMENT_TAG]");
    break;
  case SUB_AND_SSIGNMENT_TAG:
    printf("[SUB_AND_SSIGNMENT_TAG]");
    break;
  case MUL_AND_SSIGNMENT_TAG:
    printf("[MUL_AND_SSIGNMENT_TAG]");
    break;
  case DIV_AND_SSIGNMENT_TAG:
    printf("[DIV_AND_SSIGNMENT_TAG]");
    break;
  case MOD_AND_SSIGNMENT_TAG:
    printf("[MOD_AND_SSIGNMENT_TAG]");
    break;
  case LOGICAL_OR_TAG:
    printf("[LOGICAL_OR_TAG]");
    break;
  case LOGICAL_AND_TAG:
    printf("[LOGICAL_AND_TAG]");
    break;
  case EQUAL_TAG:
    printf("[EQUAL_TAG]");
    break;
  case NOT_EQUAL_TAG:
    printf("[NOT_EQUAL_TAG]");
    break;
  case GREATER_TAG:
    printf("[GREATER_TAG]");
    break;
  case LESS_TAG:
    printf("[LESS_TAG]");
    break;
  case GREATER_OR_EQUAL_TAG:
    printf("[GREATER_OR_EQUAL_TAG]");
    break;
  case LESS_OR_EQUAL_TAG:
    printf("[LESS_OR_EQUAL_TAG]");
    break;
  case ADD_TAG:
    printf("[ADD_TAG]");
    break;
  case SUB_TAG:
    printf("[SUB_TAG]");
    break;
  case MUL_TAG:
    printf("[MUL_TAG]");
    break;
  case DIV_TAG:
    printf("[DIV_TAG]");
    break;
  case MOD_TAG:
    printf("[MOD_TAG]");
    break;
  case INC_TAG:
    printf("[INC_TAG]");
    break;
  case DEC_TAG:
    printf("[DEC_TAG]");
    break;
  case NUM_TAG:
    printf("[NUM_TAG VALUE: %s]", scanner->token->identifier);
    break;
  }

  return true;
}

#endif /* CICHE_SCANNER_H */

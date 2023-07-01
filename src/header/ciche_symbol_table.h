#ifndef CICHE_SYMBOL_TABLE_H
#define CICHE_SYMBOL_TABLE_H

#include "ciche_hash_map.h"
#include "ciche_tag.h"
#include "ciche_hash.h"

#include <string.h>

struct ciche_varible_data {
  int value;
  size_t address;
};

struct ciche_procedure_data {
  struct ciche_doubly arguments;
  size_t address;
};

union ciche_symbol_table_data {
  enum ciche_token_tag token_tag;
  struct ciche_varible_data *varible_data;
  struct ciche_procedure_data *procedure_data;
};

#define IDENTIFIER_SIZE 9
struct ciche_symbol_table_obj {
  enum ciche_type_tag type_tag;
  char identifier[IDENTIFIER_SIZE];
  union ciche_symbol_table_data data;
};

bool ciche_symbol_table_obj_equals(void *obj1, void *obj2) {
  if (!obj1)
    return obj1 == obj2;
  
  struct ciche_symbol_table_obj *st_obj1 = (struct ciche_symbol_table_obj *) obj1;
  struct ciche_symbol_table_obj *st_obj2 = (struct ciche_symbol_table_obj *) obj2;
  
  if (strcmp(st_obj1->identifier, st_obj2->identifier))
    return false;

  return true;
}

uint64_t ciche_symbol_table_obj_hash(void *obj) {
  if (!obj)
    return 0;
  
  struct ciche_symbol_table_obj *st_obj = (struct  ciche_symbol_table_obj *) obj;

  return ciche_hash_str(st_obj->identifier);
}

struct ciche_hash_map *symbol_table = NULL;

static struct ciche_symbol_table_obj *keyword_create(char *kw, enum ciche_token_tag tag) {
  struct ciche_symbol_table_obj *obj = (struct ciche_symbol_table_obj *) malloc(sizeof(struct ciche_symbol_table_obj));

  union ciche_symbol_table_data data;
  data.token_tag = tag;

  obj->type_tag = KEYWORD_TAG;
  for (int i = 0; i < IDENTIFIER_SIZE; ++i)
    obj->identifier[i] = '\0';
  strncpy(obj->identifier, kw, IDENTIFIER_SIZE - 1);
  obj->data = data;

  return obj;
}

bool ciche_symbol_table_init() {
  symbol_table = (struct ciche_hash_map *) malloc(sizeof(struct ciche_hash_map));

  ciche_hash_map_add(symbol_table, keyword_create("define", DEFINE_TAG), &ciche_symbol_table_obj_hash);
  ciche_hash_map_add(symbol_table, keyword_create("int", INT_TAG), &ciche_symbol_table_obj_hash);
  ciche_hash_map_add(symbol_table, keyword_create("void", VOID_TAG), &ciche_symbol_table_obj_hash);
  ciche_hash_map_add(symbol_table, keyword_create("break", BREAK_TAG), &ciche_symbol_table_obj_hash);
  ciche_hash_map_add(symbol_table, keyword_create("continue", CONTINUE_TAG), &ciche_symbol_table_obj_hash);
  ciche_hash_map_add(symbol_table, keyword_create("return", RETURN_TAG), &ciche_symbol_table_obj_hash);
  ciche_hash_map_add(symbol_table, keyword_create("if", IF_TAG), &ciche_symbol_table_obj_hash);
  ciche_hash_map_add(symbol_table, keyword_create("else", ELSE_TAG), &ciche_symbol_table_obj_hash);
  ciche_hash_map_add(symbol_table, keyword_create("while", WHILE_TAG), &ciche_symbol_table_obj_hash);
  ciche_hash_map_add(symbol_table, keyword_create("do", DO_TAG), &ciche_symbol_table_obj_hash);
  ciche_hash_map_add(symbol_table, keyword_create("for", FOR_TAG), &ciche_symbol_table_obj_hash);
  
  return true;
}

#endif /* CICHE_SYMBOL_TABLE_H */

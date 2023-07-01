#include "../src/header/ciche_symbol_table.h"

#include <stdio.h>

int main() {
  ciche_symbol_table_init();

  struct ciche_symbol_table_obj *obj = (struct ciche_symbol_table_obj *) malloc(sizeof(struct ciche_symbol_table_obj));

  union ciche_symbol_table_data data;
  data.token_tag = 0;

  obj->type_tag = 0;
  for (int i = 0; i < IDENTIFIER_SIZE; ++i)
    obj->identifier[i] = '\0';
  strncpy(obj->identifier, "while", IDENTIFIER_SIZE - 1);
  obj->data = data;

  ciche_hash_map_find_obj(symbol_table, obj, &ciche_symbol_table_obj_hash, &ciche_symbol_table_obj_equals, (void **) &obj);

  printf("%d\n", obj->data.token_tag);
  
  return 0;
}

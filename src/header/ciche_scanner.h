#ifndef CICHE_SCANNER_H
#define CICHE_SCANNER_H

#include "ciche_symbol_table.h"

#include <stdio.h>

struct ciche_token {
  enum ciche_token_tag token_tag;
  char identifier[9];
};

struct ciche_scanner {
  FILE *file;
  char head;
  struct ciche_token token;
};

struct ciche_scanner *scanner = NULL;

bool ciche_scanner_init(char *file_name) {
  scanner = (struct ciche_scanner *) malloc(sizeof(struct ciche_scanner));

  scanner->file = fopen(file_name, "r");
  if (!scanner->file)
    return false;
  
  scanner->head = fgetc(scanner->file);
  
  return true;
}

#endif /* CICHE_SCANNER_H */

#include "../src/header/ciche_scanner.h"

int main() {
  ciche_symbol_table_init();
  ciche_scanner_init("source.ci");

  printf("%c", scanner->head);
  
  return 0;
}

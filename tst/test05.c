#include "../src/header/ciche_scanner.h"

int main() {
  ciche_symbol_table_init();
  ciche_scanner_init("source.ci");

  int line = 1;
  printf("#1 ");
  while (ciche_scanner_advance()) {
    if (scanner->line > line) {
      line = scanner->line;
      printf("\n#%d ", line);
    }
    ciche_scanner_print();
  }
  
  return 0;
}

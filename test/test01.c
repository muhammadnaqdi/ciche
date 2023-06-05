#include "../src/header/ciche_hash.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  printf("%lu\n", ciche_hash_8(true, 'a'));
  printf("%lu\n", ciche_hash_8(true, 'b'));
  printf("%lu\n", ciche_hash_8(true, 'c'));
  printf("%lu\n", ciche_hash_8(true, 'a'));
  puts("");

  printf("%lu\n", ciche_hash_16(0));
  printf("%lu\n", ciche_hash_16(123));
  printf("%lu\n", ciche_hash_16(101));
  printf("%lu\n", ciche_hash_16(0));
  puts("");
  
  printf("%lu\n", ciche_hash_32(0));
  printf("%lu\n", ciche_hash_32(123));
  printf("%lu\n", ciche_hash_32(101));
  printf("%lu\n", ciche_hash_32(0));
  puts("");

  printf("%lu\n", ciche_hash_64(0));
  printf("%lu\n", ciche_hash_64(123));
  printf("%lu\n", ciche_hash_64(101));
  printf("%lu\n", ciche_hash_64(0));
  puts("");

  printf("%lu\n", ciche_hash_str("abc"));
  printf("%lu\n", ciche_hash_str("acb"));
  printf("%lu\n", ciche_hash_str("what is ligma?"));
  printf("%lu\n", ciche_hash_str("abc"));
  puts("");
  
  return EXIT_SUCCESS;
}

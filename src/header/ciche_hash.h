#ifndef CICHE_HASH_H
#define CICHE_HASH_H

#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

uint64_t ciche_hash_8(bool reset, uint8_t byte) {
  static long counter = 0;
  static int64_t hash = 0;
  
  if (reset) {
    counter = 0;
    hash = 0;
  }

  if (counter == 0) {
    for (int i = 0; i < 7; ++i) {
      hash += i % 2 ? (int64_t) byte : (int64_t) ~byte;
      hash <<= 8;
    }
    hash += (int64_t) byte;
  }
  
  int64_t tmp = ((int64_t) byte * primes[counter % 10]) % UCHAR_MAX;
  tmp <<= 8 * (counter % 8);
  hash ^= tmp;

  counter ++;
  
  return hash;
}

uint64_t ciche_hash_16(uint16_t word) {
  uint64_t hash = 0;
  uint32_t mask = 0x00FF;

  hash = ciche_hash_8(true, (uint8_t) (word & mask));
  word >>= 8;
  hash = ciche_hash_8(false, (uint8_t) (word & mask));

  return hash;
}

uint64_t ciche_hash_32(uint32_t dword) {
  uint64_t hash = 0;
  uint32_t mask = 0x000000FF;

  hash = ciche_hash_8(true, (uint8_t) (dword & mask));
  dword >>= 8;
  for (int i = 1; i < 4; ++i) {
    hash = ciche_hash_8(false, (uint8_t) (dword & mask));
    dword >>= 8;
  }

  return hash;
}

uint64_t ciche_hash_64(uint64_t qword) {
  uint64_t hash = 0;
  uint64_t mask = 0x00000000000000FF;

  hash = ciche_hash_8(true, (uint8_t) (qword & mask));
  qword >>= 8;
  for (int i = 1; i < 8; ++i) {
    hash = ciche_hash_8(false, (uint8_t) (qword & mask));
    qword >>= 8;
  }

  return hash;
}

uint64_t ciche_hash_str(char *str) {
  uint64_t hash = 0;

  if (*str)
    hash = ciche_hash_8(true, (uint8_t) *(str++));
  
  while (*str)
    hash = ciche_hash_8(false, (uint8_t) *(str++));

  return hash;
}

#endif /* CICHE_HASH_H */

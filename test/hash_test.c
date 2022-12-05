#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../headers/rules.h"
#include "../headers/io.h"
#include "../headers/hash.h"
#include "../headers/words.h"

void test_murmur3_32() {
  unsigned int hash = murmur3_32("hola\n", 4);
  assert(hash == 919191312);
}

void test_createHashTable() {
  HashTable dictionary = createHashTable(INITIAL_DICC_LENGTH, 0);
  assert(*dictionary->chargeFactor == 0.0);
  assert(dictionary != NULL);
  assert(dictionary->elems != NULL);
  assert(dictionary->elems[0] == NULL);
  assert(dictionary->length == INITIAL_DICC_LENGTH);
  assert(dictionary->length != INITIAL_SUGG_LENGTH);
  deleteTable(dictionary, 0);
}

void test_rehashTable() {
  HashTable dictionary = createHashTable(INITIAL_DICC_LENGTH, 0);
  dictionary = rehashTable(dictionary, 0);
  assert(dictionary != NULL);
  assert(dictionary->length == 2*INITIAL_DICC_LENGTH);
  deleteTable(dictionary, 0);
}

int main() {
  test_murmur3_32();
  test_createHashTable();
  test_rehashTable();
  printf("Test de hash ejecutados correctamente.\n");
  return 0;
}
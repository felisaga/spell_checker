#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/hash.h"
#include "../headers/resources.h"


// cambiar este tipo a unsigned int y uint8 a char
uint32_t murmur3_32(char *key, uint32_t len) {
  static const uint32_t c1 = 0xcc9e2d51;
  static const uint32_t c2 = 0x1b873593;
  static const uint32_t r1 = 15;
  static const uint32_t r2 = 13;
  static const uint32_t m = 5;
  static const uint32_t n = 0xe6546b64;

  uint32_t hash = 5381; //nro primo

  const int nblocks = len / 4;
  const uint32_t *blocks = (const uint32_t *) key;
  int i;
  for (i = 0; i < nblocks; i++) {
      uint32_t k = blocks[i];
      k *= c1;
      k = (k << r1) | (k >> (32 - r1));
      k *= c2;

      hash ^= k;
      hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
  }

  const uint8_t *tail = (const uint8_t *) (key + nblocks * 4);
  uint32_t k1 = 0;

  switch (len & 3) {
  case 3:
      k1 ^= tail[2] << 16;
  case 2:
      k1 ^= tail[1] << 8;
  case 1:
      k1 ^= tail[0];

      k1 *= c1;
      k1 = (k1 << r1) | (k1 >> (32 - r1));
      k1 *= c2;
      hash ^= k1;
  }

  hash ^= len;
  hash ^= (hash >> 16);
  hash *= 0x85ebca6b;
  hash ^= (hash >> 13);
  hash *= 0xc2b2ae35;
  hash ^= (hash >> 16);

  return hash;
}

HashTable createHashTable(unsigned int len) {
  HashTable table = malloc(sizeof(_HashTable));
  table->elems = calloc(len, sizeof(List));
  table->length = len;
  table->chargeFactor = malloc(sizeof(float));
  *table->chargeFactor = 0.000001; //
  return table;
}

HashTable addElementToTable(HashTable table, char *word, int wordLen) {
  unsigned int hash = murmur3_32(word, wordLen);
  unsigned int index = hash % table->length;
  table->elems[index] = addElementToList(table->elems[index], word, wordLen, hash, table->chargeFactor, table->length);

  if(*(table->chargeFactor) > 0.7) table = rehashTable(table);

  return table;
}

void deleteTable(HashTable table) {
  for(int i = 0; i < table->length; i++) {
    deleteList(table->elems[i]);
    // free(table->elems[i]);
  }
  free(table->elems);
  free(table->chargeFactor);
  free(table);
}

HashTable rehashTable(HashTable table) {
  unsigned int newLength = table->length * 2;
  HashTable newTable = createHashTable(newLength);

  for(int i = 0; i < table->length; i++) {
    if(table->elems[i] != NULL) {
      List aux = table->elems[i];
      while(aux != NULL) {
        // unsigned int hash = murmur3_32(aux->elem, aux->len);
        // unsigned int index = hash % newLength;
        // newTable->elems[index] = addElementToList(newTable->elems[index], aux->elem, aux->len, hash, table->chargeFactor, newLength);
        char *pelado = malloc(sizeof(char) * aux->len);
        strcpy(pelado, aux->elem);
        newTable = addElementToTable(newTable, pelado, aux->len);

        aux = aux->next;
      }
    }
  }

  deleteTable(table);

  return newTable;
}


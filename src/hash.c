#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/hash.h"
#include "../headers/resources.h"
#include "../headers/words.h"
#include "../headers/suggestions.h"

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

HashTable createHashTable(unsigned int len, int type) {
  HashTable table = malloc(sizeof(_HashTable));
  table->elems = calloc(len, sizeof(List));
  table->length = len;
  table->chargeFactor = malloc(sizeof(float));
  // *table->chargeFactor = 0.000001; //
  *table->chargeFactor = 0.0; //
  table->type = type;
  return table;
}

void deleteTable(HashTable table, int type) {
  for(int i = 0; i < table->length; i++) {
    deleteList(table->elems[i], type);
  }
  free(table->elems);
  free(table->chargeFactor);
  free(table);
}

HashTable rehashTable(HashTable table, int type) {
  unsigned int newLength = table->length * 2;
  HashTable newTable = createHashTable(newLength, type);

  for(int i = 0; i < table->length; i++) {
    if(table->elems[i] != NULL) {
      List aux = table->elems[i];
      while(aux != NULL) {
        if (!type) {
          char *copy = malloc(sizeof(char) * aux->len);
          strcpy(copy, ((WordPointer)(aux->elem))->word);
          newTable = addWordToTable(newTable, copy, aux->len, type);
        } else {
          char *copy = malloc(sizeof(char) * aux->len);
          strcpy(copy, ((SuggestionPointer)(aux->elem))->word);
          char **array = malloc(sizeof(char*) * ((SuggestionPointer)(aux->elem))->lenSuggestions);
          for(int i = 0; i < ((SuggestionPointer)(aux->elem))->lenSuggestions; i++) {
            strcpy(array[i], ((SuggestionPointer)(aux->elem))->suggestions[i]);
          }
          newTable = addSuggestionToTable(newTable, copy, array, ((SuggestionPointer)(aux->elem))->lenSuggestions, aux->len, type);
        }
        aux = aux->next;
      }
    }
  }

  deleteTable(table, type);

  return newTable;
}


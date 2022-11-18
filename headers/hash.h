
#ifndef __HASH_H_
#define __HASH_H_

#include <stdint.h>

typedef struct _Node {
  char *elem;
  unsigned int len;     // largo de la palabra
  unsigned int hash;
  // char *suggestions;   // si es la tabla de sugerencias
  // int suggestionsLen;  // cuantas sugerencias hay
  struct _Node *next;
} Node;

typedef Node * List;

typedef struct {
  List * elems;
  // int *max_colissions;   // el largo de la lista mas larga
  float *chargeFactor;  // (ocupados / capacidad)
  unsigned int length;
} _HashTable;

typedef _HashTable* HashTable;

uint32_t murmur3_32(char *key, uint32_t len);

// Crea una tabla hash de un determinado largo e inicializa sus elementos en NULL
HashTable createHashTable(unsigned int len);

// Agrega un elemento en la tabla
HashTable addElementToTable(HashTable table, char *word, int wordLen);

// Funcion que librea la memoria utilizada por una tabla hash
void deleteTable(HashTable table);

// Rehash de una tabla aumentando el tamaño
HashTable rehashTable(HashTable table);


#endif
#ifndef __HASH_H_
#define __HASH_H_

#include <stdint.h>

#define INITIAL_DICC_LENGTH 100000
#define INITIAL_SUGG_LENGTH 10000

typedef struct _Node {
  void *elem; //op1) char* op2) char* + char** + int 
  // char *elem;
  unsigned int len;     // largo de la palabra
  unsigned int hash;
  // int type;               // 0 si es para un diccionario - 1 si es para una sugerencia
  struct _Node *next;
} Node;

typedef Node *List;

typedef struct {
  // void *elems;
  List * elems;
  // int *max_colissions;   // el largo de la lista mas larga
  float *chargeFactor;  // (ocupados / capacidad)
  unsigned int length;
  int type;             // 0 si es para un diccionario - 1 si es para una sugerencia
} _HashTable;

typedef _HashTable *HashTable;

uint32_t murmur3_32(char *key, uint32_t len);

// Crea una tabla hash de un determinado largo e inicializa sus elementos en NULL
HashTable createHashTable(unsigned int len, int type);

// Funcion que librea la memoria utilizada por una tabla hash
void deleteTable(HashTable table, int type);

// Rehash de una tabla aumentando el tamaño
HashTable rehashTable(HashTable table, int type);

#endif
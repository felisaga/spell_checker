#ifndef __HASH_H_
#define __HASH_H_

#include <stdint.h>

#define INITIAL_DICC_LENGTH 1000000
#define INITIAL_SUGG_LENGTH 10000

// Estructura de los elementos que van en la tabla hash
// Listas enlazadas, con un void* de elemento por si se almacenan solo palabras o sugerencias
typedef struct _Node {
  void *elem;           // op1) char* op2) char* + char** + int 
  unsigned int len;     // largo de la palabra
  unsigned int hash;
  struct _Node *next;
} Node;

typedef Node *List;

// Estructura de tabla hash
typedef struct {
  List * elems;
  float *chargeFactor;  // (ocupados / capacidad)
  unsigned int length;
  int type;             // 0 si es para un diccionario - 1 si es para una sugerencias
} _HashTable;

typedef _HashTable *HashTable;

// Dada una palabra y su largo devuelve su hash con esta funcion
// murmur3_32: (char*, uint32_t) -> uint32_t
uint32_t murmur3_32(char *key, uint32_t len);


// Crea una tabla hash de un determinado largo e inicializa sus elementos en NULL
// createHashTable: (unsigned int, int) -> HashTable
HashTable createHashTable(unsigned int len, int type);

// Funcion que librea la memoria utilizada por una tabla hash
// deleteTable: (HashTable, int) -> ()
void deleteTable(HashTable table, int type);

// Rehash de una tabla aumentando el tamaño
// rehashTable: (HashTable, int) -> HashTable
HashTable rehashTable(HashTable table, int type);

#endif
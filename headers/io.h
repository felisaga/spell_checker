#ifndef __IO_H_
#define __IO_H_

#include "./hash.h"

// A partir del archivo diccionario guarda las palabras en una tabla hash
HashTable readDictionary(HashTable table, char *path);

// A partir del archivo de sugerencias las guarda en una tabla hash
HashTable readSuggestions(HashTable table, char* path);

#endif
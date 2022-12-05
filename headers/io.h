#ifndef __IO_H_
#define __IO_H_

#include "./hash.h"
#include "../headers/suggestions.h"

#define MAX_WORD_LENGTH 45

// A partir del archivo diccionario guarda las palabras en una tabla hash
// readDictionary: (HashTable, char*) -> HashTable
HashTable readDictionary(HashTable table, char *path);

// A partir del archivo de sugerencias las guarda en una tabla hash
// readDictionary: (HashTable, char*) -> HashTable
HashTable readSuggestions(HashTable table, char* path);

// A partir de una lista de recomendaciones las imprime en un archivo de correcciones y
// a las nuevas sugerencias las agrega al archivo de sugerencias
// printRecommendations: (RecommendationList, char*, char*) -> ()
void printRecommendations(RecommendationList list, char *oputput, char *suggestions);

#endif
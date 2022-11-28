#ifndef __SUGGESTIONS_H_
#define __SUGGESTIONS_H_

#include <stdint.h>
#include "../headers/hash.h"

typedef struct Suggestion { 
  char *word;
  char **suggestions;
  int lenSuggestions;
} Suggestion;

typedef Suggestion *SuggestionPointer;

// Crea una sugerencia para guardar en la lista
void *createSuggestion(char *word, char **suggestions, int suggestionsLen);

// Agrega una nueva sugerencia a la lista de manera ordenada
List addSuggestionToList(List list, char *word, char **suggestions, int suggestionsLen, int wordLen, unsigned int hash, float *chargeFactor, int tableLength);

// Agrega una nueva sugerencia a una tabla de sugerencias
HashTable addSuggestionToTable(HashTable table, char *word, char **suggestions, int suggestionsLen, int wordLen, int type);

// Elimina la memoria que ocupa una sugerencia
void deleteSuggestions(SuggestionPointer elem);

// Agrega una sugerencia a la lista de sugerencias
char** addSuggestion(char **suggestions, char* suggestion, int len);


#endif
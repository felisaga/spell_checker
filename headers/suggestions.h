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

typedef struct _Recommendation { 
  char *word;
  char **recommendations;
  int lenRecommendations;
  int line;
  int new;
  struct _Recommendation *next;
} Recommendation;

typedef Recommendation *RecommendationList;

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

// Se fija si una palabra tiene sugerencias en la tabla
SuggestionPointer inSuggestions(HashTable suggestions, char *word, int wordLen);

// Se fija si una palabra tiene sugerencias en la lista
SuggestionPointer inSuggestionsList(List list, char *word, unsigned int hash);

// Agrega una recomendacion a la lista de recomendaciones
RecommendationList addToRecommendations(RecommendationList list, char *word, char **recommendations, int lenRecommendations, int line, int new);

// Elimina el espacio ocupado por la lista de recomendaciones
void freeRecommendations(RecommendationList list);

char** addWordToReccomendation(char **recommedations, char *word, int *lenRecommendations);

void deleteRecommendations(RecommendationList list);


#endif
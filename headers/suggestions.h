#ifndef __SUGGESTIONS_H_
#define __SUGGESTIONS_H_

#include <stdint.h>
#include "../headers/hash.h"

// Estructura utilizada para guardar una palabra con sus sugerencias
typedef struct Suggestion { 
  char *word;
  char **suggestions;
  int lenSuggestions;
} Suggestion;

typedef Suggestion *SuggestionPointer;

// Estructura para guardar las palabras que estan mal escritas y sus sugerencias
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
// createSuggestion: (char*, char**, int) -> void*
void *createSuggestion(char *word, char **suggestions, int suggestionsLen);

// Agrega una nueva sugerencia a la lista de manera ordenada
// addSuggestionToList: (List, char*, char **, int, int, unsigned int, floar*, int) -> List
List addSuggestionToList(List list, char *word, char **suggestions, int suggestionsLen, int wordLen, unsigned int hash, float *chargeFactor, int tableLength);


// Agrega una nueva sugerencia a una tabla de sugerencias
// addSuggestionToTable: (HashTable, char*, char**, int, int, int) -> HashTable
HashTable addSuggestionToTable(HashTable table, char *word, char **suggestions, int suggestionsLen, int wordLen, int type);

// Elimina la memoria que ocupa una sugerencia
// deleteSuggestions: (SuggestionPointer) -> ()
void deleteSuggestions(SuggestionPointer elem);

// Agrega una sugerencia a la lista de sugerencias
// addSuggestion: (char **, char*, int) -> char**
char** addSuggestion(char **suggestions, char* suggestion, int len);

// Se fija si una palabra tiene sugerencias en la tabla
// inSuggestions: (HashTable, char*, int) -> SuggestionPointer
SuggestionPointer inSuggestions(HashTable suggestions, char *word, int wordLen);

// Se fija si una palabra tiene sugerencias en la lista
// inSuggestionList: (List, char*, unsigned int) -> SuggestionPointer
SuggestionPointer inSuggestionsList(List list, char *word, unsigned int hash);

// Agrega una recomendacion a la lista de recomendaciones
// addToRecommendations: (RecommendationList, char*, char**, int, int, int) -> RecommendationList
RecommendationList addToRecommendations(RecommendationList list, char *word, char **recommendations, int lenRecommendations, int line, int new);

// Elimina el espacio ocupado por la lista de recomendaciones
// freeRecommendations: (RecommendationList) -> ()
void freeRecommendations(RecommendationList list);

// Agrega una palabra al array de recomendaciones o lo crea si no existe y le agrega la palabra
// addWordToRecommendation: (char**, char*, int*) -> char**
char** addWordToReccomendation(char **recommedations, char *word, int *lenRecommendations);

// Libera la memoria utilizada por una lista de recomendaciones
// deleteRecommendations: (RecommendationList) -> ()
void deleteRecommendations(RecommendationList list);

// Se fija si una palabra ya esta en la lista de recomendaciones para no agregar las repetidas
// inReccomendations: (char**, int, char*) -> int
int inReccomendations(char **array, int arrayLen, char* word);

#endif
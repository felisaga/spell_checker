#ifndef __CHECKER_H_
#define __CHECKER_H_

#include "./hash.h"
#include "./suggestions.h"

// A partir de un archivo de texto a cada palabra que este mal escrita le intenta encontrar
// posibles sugerencias de correcciones
// chackSpell: (char*, HashTable, HashTable*) -> RecommendationList
RecommendationList checkSpell(char *path, HashTable dictionary, HashTable *suggestions);

// Dada una palabra le intenta buscar a lo sumo 5 sugerencias de palabras que si esten en el diccionario
// searchRecommendations: (RecommendationList, char*, HashTable, int, int, HashTable*) -> RecommendationList
RecommendationList searchRecommendations(RecommendationList list, char *word, HashTable dictionary, int wordLen, int line, HashTable *suggestions);

#endif

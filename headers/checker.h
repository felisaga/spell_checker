#ifndef __CHECKER_H_
#define __CHECKER_H_

#include "./hash.h"
#include "./suggestions.h"

RecommendationList checkSpell(char *path, HashTable dictionary, HashTable suggestions); // si es null es porque no se abrio el archivo o no hay recomendaciones

RecommendationList searchRecommendations(RecommendationList list, char *word, HashTable dictionary, int wordLen, int line, HashTable suggestions);

#endif

#ifndef __RULES_H_
#define __RULES_H_

#include "./hash.h"
#include "./suggestions.h"

char** splitWord(char *word, HashTable dictionary, HashTable stepTable, int wordLen, int *lenRecommendations, char **recommendations, int line, int step);

char** deleteLetters(char *word, HashTable dictionary, HashTable stepTable, int wordLen, int *lenRecommendations, char **recommendations, int line, int step);

char** swtichLetters(char *word, HashTable dictionary, HashTable stepTable, int wordLen, int *lenRecommendations, char **recommendations, int line, int step);

char** replaceLetters(char *word, HashTable dictionary, HashTable stepTable, int wordLen, int *lenRecommendations, char **recommendations, int line, int step);

char** insertLetters(char *word, HashTable dictionary, HashTable stepTable, int wordLen, int *lenRecommendations, char **recommendations, int line, int step);

#endif

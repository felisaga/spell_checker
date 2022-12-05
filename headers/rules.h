#ifndef __RULES_H_
#define __RULES_H_

#include "./hash.h"
#include "./suggestions.h"

//  Dada una palabra intenta encontrar sugerencias poniendo espacios entre cada letra
// splitWord: (char*, HashTable, HashTable, int, int*, char**, int, int) -> char**
char** splitWord(char *word, HashTable dictionary, HashTable stepTable, int wordLen, int *lenRecommendations, char **recommendations, int line, int step);

// Dada una palabra intenta encontrar sugerencias eliminando de a una letra de la palabra
// deleteLetters: (char*, HashTable, HashTable, int, int*, char**, int, int) -> char**
char** deleteLetters(char *word, HashTable dictionary, HashTable stepTable, int wordLen, int *lenRecommendations, char **recommendations, int line, int step);

// Dada una palabra intenta encontrar sugerencias intercambiando cada par de letras adyacentes de la palabra
// switchLetters: (char*, HashTable, HashTable, int, int*, char**, int, int) -> char**
char** swtichLetters(char *word, HashTable dictionary, HashTable stepTable, int wordLen, int *lenRecommendations, char **recommendations, int line, int step);

// Dada una palabra intenta encontrar sugerencias reemplazando cada letra de la palabra por una entre la 'a' y la 'z'
// replaceLetters: (char*, HashTable, HashTable, int, int*, char**, int, int) -> char**
char** replaceLetters(char *word, HashTable dictionary, HashTable stepTable, int wordLen, int *lenRecommendations, char **recommendations, int line, int step);

// Dada una palabra intenta encontrar sugerencias insertando letras de la 'a' a la 'z' entre cada par de letras
// insertLetters: (char*, HashTable, HashTable, int, int*, char**, int, int) -> char**
char** insertLetters(char *word, HashTable dictionary, HashTable stepTable, int wordLen, int *lenRecommendations, char **recommendations, int line, int step);

#endif

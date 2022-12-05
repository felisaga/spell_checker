#ifndef __WORDS_H_
#define __WORDS_H_

#include <stdint.h>
#include "../headers/hash.h"

// Estructura utilizada en las tablas con solo palabras
typedef struct Word { 
  char *word;
} Word;

typedef Word *WordPointer;

// Crea una palabra para guardar en la lista
// createWord: (char*) -> WordPointer
WordPointer createWord(char *word);

// Agrega una nueva palabra a la lista de manera ordenada
// addWordToList: (List, char *, int, unsigned int, float*, int) -> List
List addWordToList(List list, char *word, int wordLen, unsigned int hash, float *chargeFactor, int tableLength);

// Agrega una nueva palabra a una tabla de palabras
// addWordToTable: (HashTable, char*, int, int) -> HashTable
HashTable addWordToTable(HashTable table, char *word, int wordLen, int type);

// Elimina la memoria que ocupa una palabra
// deleteWord: (WordPointer) -> ()
void deleteWord(WordPointer elem);

// Se fija si una palabra esta dentro del diccionario
// inDictionary(HashTable, char*, int) -> int
int inDictionary(HashTable dicc, char *word, int wordLen);

// Se fija si una palabra esta dentro de una lista de palabras
// inWordList(List, char*, unsigned int) -> int
int inWordList(List list, char *word, unsigned int hash);

#endif
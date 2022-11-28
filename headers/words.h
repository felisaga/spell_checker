#ifndef __WORDS_H_
#define __WORDS_H_

#include <stdint.h>
#include "../headers/hash.h"

typedef struct Word { 
  char *word;
} Word;

typedef Word *WordPointer;

// Crea una palabra para guardar en la lista
WordPointer createWord(char *word);

// Agrega una nueva palabra a la lista de manera ordenada
List addWordToList(List list, char *word, int wordLen, unsigned int hash, float *chargeFactor, int tableLength);

// Agrega una nueva palabra a una tabla de palabras
HashTable addWordToTable(HashTable table, char *word, int wordLen, int type);

// Elimina la memoria que ocupa una palabra
void deleteWord(WordPointer elem);

#endif
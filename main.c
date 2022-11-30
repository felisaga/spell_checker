
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/hash.h"
#include "./headers/io.h"
#include "./headers/words.h"
#include "./headers/suggestions.h"

#define INITIAL_DICC_LENGTH 100000
#define INITIAL_SUGG_LENGTH 10000

int main(int argc, char *argv[]) { // argv = [ejecutable, archivo de entrada, archivo de salida, diccionario, sugerencias]
  HashTable dictionary = createHashTable(INITIAL_DICC_LENGTH, 0);
  dictionary = readDictionary(dictionary, argv[3]);

  if (dictionary == NULL) { // si no se puede abrir el archivo diccionario termina el programa
    return 0;
  }

  printf("\nlargo: %d - factor de carga: %f\n", dictionary->length, *dictionary->chargeFactor);


  HashTable suggestions = createHashTable(INITIAL_SUGG_LENGTH, 1);
  suggestions = readSuggestions(suggestions, argv[4]);
  // if (suggestions == NULL) { // si no se puede abrir el archivo con sugerencias termina el programa
  //   return 0;
  // }

  // for(int i=0; i<suggestions->length;i++) {
  //   if(suggestions->elems[i] != NULL) {
  //     List aux = suggestions->elems[i];
  //     while (aux != NULL) {
  //     // printf("palabra: |%s|\n", ((SuggestionPointer)(suggestions->elems[i]->elem))->word);
  //     printf("palabra: |%s|\n", ((SuggestionPointer)(aux->elem))->word);
  //     printf("sugerencias: ");
  //     for (int j = 0; j < ((SuggestionPointer)(aux->elem))->lenSuggestions; j++) {
  //       printf("|%s|, ", ((SuggestionPointer)(aux->elem))->suggestions[j]);
  //     }
  //     printf("\n");
  //     aux = aux->next;
  //     }
  //   }
  // }

  printf("\nlargo: %d - factor de carga: %f\n", suggestions->length, *suggestions->chargeFactor);
  
  deleteTable(dictionary, 0);
  deleteTable(suggestions, 1);

  return 0;
}
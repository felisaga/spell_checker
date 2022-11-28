
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
  FILE *f = fopen(argv[1], "rb");
  if (f == NULL) { // si no se puede abrir el archivo de entrada termina el programa
		printf("Error al abrir el archivo de texto.\n");
    return 0;
  }
  HashTable dictionary = createHashTable(INITIAL_DICC_LENGTH, 0);
  dictionary = readDictionary(dictionary, argv[3]);
  printf("\nlargo: %d - factor de carga: %f\n", dictionary->length, *dictionary->chargeFactor);

  // int caca = 0;
  // for (int i = 0; i < dictionary->length; i++)
  // {
  //   if(dictionary->elems[i] != NULL) {
  //     List aux = dictionary->elems[i];
  //     while (aux != NULL){
  //     caca++;
  //     aux = aux->next;
  //     }
  //   }
  // }
  // printf("%d palabras", caca);
  

  deleteTable(dictionary, 0);

  HashTable suggestions = createHashTable(INITIAL_SUGG_LENGTH, 1);
  suggestions = readSuggestions(suggestions, argv[4]);

  // for(int i=0; i<suggestions->length;i++) {
  //   if(suggestions->elems[i] != NULL) {
  //     List aux = suggestions->elems[i];
  //     while (aux != NULL) {
  //     // printf("palabra: |%s|\n", ((SuggestionPointer)(suggestions->elems[i]->elem))->word);
  //     // printf("palabra: |%s|\n", ((SuggestionPointer)(aux->elem))->word);
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
  deleteTable(suggestions, 1);

  // HashTable table = malloc(sizeof(HashTable));
  // table->elems = calloc(1, sizeof(List));

  // free(table->elems);
  // free(table->elems[0]);
  // HashTable table = createHashTable(INITIAL_TABLE_LENGTH);
  // deleteTable(table);

  // free(table);

  fclose(f);

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/hash.h"
#include "./headers/io.h"
#include "./headers/words.h"
#include "./headers/suggestions.h"
#include "./headers/checker.h"

int main(int argc, char *argv[]) { // argv = [ejecutable, archivo de entrada, archivo de salida, diccionario, sugerencias]
  HashTable dictionary = createHashTable(INITIAL_DICC_LENGTH, 0);
  dictionary = readDictionary(dictionary, argv[3]);
  if (dictionary == NULL) { // si no se puede abrir el archivo diccionario termina el programa
    return 0;
  }

  // for (int i = 0; i < dictionary->length; i++)
  // {
  //   if(dictionary->elems[i] != NULL) {
  //     List aux = dictionary->elems[i];
  //     while (aux != NULL)
  //     {
  //       if(strcmp(((WordPointer)(aux->elem))->word, "hola") == 0) {
  //         printf("HOLAAA!!! |%s|%d-%u|%p|len|%d|\n",((WordPointer)(aux->elem))->word, i, aux->hash, dictionary->elems[i], aux->len);
  //         printf("||||||%d|||||||\n",inDictionary(dictionary, "hola", 4));
  //       }
  //       aux = aux->next;
  //     }
      
  //   }
  // }

  // printf("\nlargo: %d - factor de carga: %f\n", dictionary->length, *dictionary->chargeFactor);

  HashTable suggestions = createHashTable(INITIAL_SUGG_LENGTH, 1);
  suggestions = readSuggestions(suggestions, argv[4]);
  RecommendationList recommendations = checkSpell(argv[1], dictionary, &suggestions);

  // RecommendationList aux = recommendations;
    
  //   while(aux != NULL) {
  //     // printf("WHILE!! agrego sugg para |%s| linea: |%d| sugerencias count |%d|\n", aux->word, aux->line, aux->lenRecommendations);
  //     printf("palabra mal: |%s| linea: %d, sugerencias:\n", aux->word, aux->line);
  //     printf("new?: |%d|\n", aux->new);
  //     for (int i = 0; i < aux->lenRecommendations; i++)
  //     {
  //       printf("|%s|, ", aux->recommendations[i]);
  //     }
  //     printf("\n");
  //     aux = aux->next;
  //   }


  // if(recommendations != NULL) free(recommendations);
  // printf("_________________________________\n");

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

  // printf("\nlargo: %d - factor de carga: %f\n", suggestions->length, *suggestions->chargeFactor);
  
  // printf("asdasddasdasdasd111111111111111\n");
  // printf("antes de dicc\n");
  // printf("asdasddasdasdasd222222222222\n");
  //   for(int i=0; i<suggestions->length;i++) {
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
  printRecommendations(recommendations, argv[2], argv[4]);
  deleteTable(dictionary, 0);
  deleteTable(suggestions, 1);
  deleteRecommendations(recommendations);
  return 0;
}
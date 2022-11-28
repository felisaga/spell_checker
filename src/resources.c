#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/hash.h"
#include "../headers/suggestions.h"
#include "../headers/words.h"

// void addWordToList(List list, char *word) {
//   WordPointer new = malloc(sizeof(Word));
//   new->word = word;
//   list->elem = new;
//   printf("Asd\n");
// }

// void *addWordToList(char *word) {
//   WordPointer new = malloc(sizeof(Word));
//   new->word = word;
//   return new;
// }

// void *addSuggestionToList(char *word, char **suggestions, int suggestionsLen) {
//   SuggestionPointer new = malloc(sizeof(Suggestion));
//   new->word = word;
//   new->suggestions = malloc(sizeof(char*) * suggestionsLen);
//   new->lenSuggestions = suggestionsLen;
//   return new;
// }

// List addElementToList(List list, char *word, int wordLen, unsigned int hash, float *chargeFactor, int tableLength, int type) {
//   if(list == NULL || (list->hash >= hash && strcmp(list->elem, word) != 0)) { // si la lista esta vacia o agrego el elemento primero
//     List new = malloc(sizeof(Node));
//     // new->elem = word;
//     // addWordToList(list, word);
//     if(type)
//       new->elem = addSuggestionToList(word);
//     else
//       new->elem = addWordToList(word);
//     new->hash = hash;
//     new->len = wordLen;
//     new->next = list;
//     if (list == NULL) {
//       *chargeFactor = *chargeFactor + (1.0 / tableLength);  // si era (elementos/capacidad) ahora es ((elementos+1)/capacidad)
//       }
//     return new;
//   } else {
//     List aux = list;
//     for(;aux->next != NULL && aux->hash < hash; aux = aux->next);  // busco la posicion adecuada por el orden
//     if(strcmp(aux->elem, word) != 0) {
//       List new = malloc(sizeof(Node));
//       // new->elem = word;
//       // addWordToList(new->elem, word);
//       if(type)
//         new->elem = addSuggestionToList(word);
//       else
//         new->elem = addWordToList(word);
//       new->hash = hash;
//       new->len = wordLen;
//       new->next = aux->next;
//       aux->next = new;
//     }
//   }
//   return list;
// }

void deleteList(List list, int type) {
  if(list != NULL) {
    if(!type) {
      deleteWord(list->elem);
    } else {
      deleteSuggestions(list->elem);
    }
    free(list->elem);
    deleteList(list->next, type);
    free(list);
  }
}

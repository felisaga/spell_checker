#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/hash.h"
#include "../headers/suggestions.h"

void *createSuggestion(char *word, char **suggestions, int suggestionsLen) {
  SuggestionPointer new = malloc(sizeof(Suggestion));
  new->word = word;
  // printf("%d\n", suggestionsLen);
  new->suggestions = suggestions;
  new->lenSuggestions = suggestionsLen;  
  return new;
}

List addSuggestionToList(List list, char *word, char **suggestions, int suggestionsLen, int wordLen, unsigned int hash, float *chargeFactor, int tableLength) {
  if(list == NULL || (list->hash >= hash && strcmp(list->elem, word) != 0)) { // si la lista esta vacia o agrego el elemento primero
    List new = malloc(sizeof(Node));
    // new->elem = word;
    new->elem = createSuggestion(word, suggestions, suggestionsLen);
    new->hash = hash;
    new->len = wordLen;
    new->next = list;
    if (list == NULL) {
      *chargeFactor = *chargeFactor + (1.0 / tableLength);  // si era (elementos/capacidad) ahora es ((elementos+1)/capacidad)
    }
    return new;
  } else {
    List aux = list;
    for(;aux->next != NULL && aux->hash < hash; aux = aux->next);  // busco la posicion adecuada por el orden
    if(strcmp(aux->elem, word) != 0) {
      List new = malloc(sizeof(Node));
      // new->elem = word;
      new->elem = createSuggestion(word, suggestions, suggestionsLen);
      new->hash = hash;
      new->len = wordLen;
      new->next = aux->next;
      aux->next = new;
    }
    
  }
  return list;
}

HashTable addSuggestionToTable(HashTable table, char *word, char **suggestions, int suggestionsLen, int wordLen, int type) {
  unsigned int hash = murmur3_32(word, wordLen);
  unsigned int index = hash % table->length;
  table->elems[index] = addSuggestionToList(table->elems[index], word, suggestions, suggestionsLen, wordLen, hash, table->chargeFactor, table->length);

  if(*(table->chargeFactor) > 0.7) table = rehashTable(table, type);

  return table;
}

void deleteSuggestions(SuggestionPointer elem) {
  // if(elem == NULL) printf("elem NULL\n");
  // if(elem->word == NULL) printf("elem->word NULL\n");
  for(int i=0; i < elem->lenSuggestions; i++) {
    // if(elem->suggestions[i] == NULL) printf("elem->suggestions NULL 11111\n");
    free(elem->suggestions[i]);
  }
  // if(elem->suggestions == NULL) printf("elem->suggestions NULL\n");
  free(elem->suggestions);
  free(elem->word);
}

char** addSuggestion(char **suggestions, char* suggestion, int len) {
  if(suggestions[0] == NULL) {
    // char **array = malloc(sizeof(char*));
    // array[len] = suggestion;
    // return array;
    suggestions[len] = suggestion;
    return suggestions;
  } else {
    char **array = realloc(suggestions, sizeof(char*) * (len + 1));
    array[len] = suggestion;
    // printf("|%s|-|%s|\n", array[len] , suggestion);
    return array;
  }
}
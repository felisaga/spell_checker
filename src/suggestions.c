#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/hash.h"
#include "../headers/suggestions.h"

void *createSuggestion(char *word, char **suggestions, int suggestionsLen) {
  SuggestionPointer new = malloc(sizeof(Suggestion));
  new->word = word;
  new->suggestions = suggestions;
  new->lenSuggestions = suggestionsLen;  
  return new;
}

List addSuggestionToList(List list, char *word, char **suggestions, int suggestionsLen, int wordLen, unsigned int hash, float *chargeFactor, int tableLength) {
  if(list == NULL || (list->hash >= hash && strcmp(((SuggestionPointer)(list->elem))->word, word) != 0)) { // si la lista esta vacia o agrego el elemento primero
    List new = malloc(sizeof(Node));
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
    if(strcmp(((SuggestionPointer)(aux->elem))->word, word) != 0) {
      List new = malloc(sizeof(Node));
      new->elem = createSuggestion(word, suggestions, suggestionsLen);
      new->hash = hash;
      new->len = wordLen;
      new->next = aux->next;
      aux->next = new;
      return list;
    } else {
      free(word);
      for (int i = 0; i < suggestionsLen; i++) {
        free(suggestions[i]);
      }
      free(suggestions);
    }
  }
  return list;
}

HashTable addSuggestionToTable(HashTable table, char *word, char **suggestions, int suggestionsLen, int wordLen, int type) {
  if(table == NULL) {
    table = createHashTable(INITIAL_SUGG_LENGTH, 1);
  }
  // printf("tiene sugerencias|%s|\n", word);
  unsigned int hash = murmur3_32(word, wordLen);
  unsigned int index = hash % table->length;
  // printf("|%s-%d//%d-%d|len:%d\n", word, index, hash, table->length,wordLen);
  table->elems[index] = addSuggestionToList(table->elems[index], word, suggestions, suggestionsLen, wordLen, hash, table->chargeFactor, table->length);

  if(*(table->chargeFactor) > 0.7) table = rehashTable(table, type);

  return table;
}

void deleteSuggestions(SuggestionPointer elem) {
  for(int i=0; i < elem->lenSuggestions; i++) {
    // printf("%s\n", elem->suggestions[i]);
    free(elem->suggestions[i]);
    // printf("%s\n", elem->suggestions[i]);

  }

  free(elem->suggestions);
  free(elem->word);
}

char** addSuggestion(char **suggestions, char* suggestion, int len) {
  if(suggestions[0] == NULL) {
    suggestions[len] = suggestion;
    return suggestions;
  } else {
    char **array = realloc(suggestions, sizeof(char*) * (len + 1));
    array[len] = suggestion;
    return array;
  }
}

SuggestionPointer inSuggestions(HashTable suggestions, char *word, int wordLen) {
  unsigned int hash = murmur3_32(word, wordLen);
  unsigned int index = hash % suggestions->length;
  // printf("%s-%d//%d-%d len:%d\n", word, index, hash, suggestions->length, wordLen);

  if(suggestions->elems[index] == NULL) {
    return NULL;
  }
  else
    return inSuggestionsList(suggestions->elems[index], word, hash);
  return NULL;
}

SuggestionPointer inSuggestionsList(List list, char *word, unsigned int hash) {
  List aux = list;
  while(aux != NULL) {
    if(aux->hash == hash && strcmp(word, ((SuggestionPointer)(aux->elem))->word) == 0) {
      return aux->elem;
    }
    if(aux->hash > hash)
      return NULL;
    aux = aux->next;
  }
  return NULL;
}

RecommendationList addToRecommendations(RecommendationList list, char *word, char **recommendations, int lenRecommendations, int line, int _new) {
  if(list == NULL) {
    RecommendationList new = malloc(sizeof(Recommendation));
    new->word = word;
    new->recommendations = recommendations;
    new->lenRecommendations = lenRecommendations;
    new->line = line;
    new->new = _new;
    new->next = NULL;

    list = new;
  } else {
    RecommendationList aux = list;
    while (aux->next != NULL) { aux = aux->next; }
    RecommendationList new = malloc(sizeof(Recommendation));
    new->word = word;
    new->recommendations = recommendations;
    new->lenRecommendations = lenRecommendations;
    new->line = line;
    new->new = _new;
    new->next = NULL;

    aux->next = new;
  }
  return list;
}

void freeRecommendations(RecommendationList list) {
  if(list == NULL) {
    return;
  } else {
    free(list);
    freeRecommendations(list->next);
  }
}

char** addWordToReccomendation(char **recommedations, char *word, int *lenRecommendations) {
  if(recommedations == NULL) {
    recommedations = malloc(sizeof(char*));
  } else {
    recommedations = realloc(recommedations, sizeof(char*) * ((*lenRecommendations)+1));
  }
  recommedations[(*lenRecommendations)] = word;
  (*lenRecommendations)++;
  return recommedations;
}

void deleteRecommendations(RecommendationList list) {
  if(list == NULL) {
    return;
  }
  deleteRecommendations(list->next);
  // if(list->new == 1) free(list->word);
  free(list);
}
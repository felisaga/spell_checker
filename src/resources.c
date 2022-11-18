#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/hash.h"

List addElementToList(List list, char *word, int wordLen, unsigned int hash, float *chargeFactor, int tableLength) {
  if(list == NULL || (list->hash >= hash && strcmp(list->elem, word) != 0)) { // si la lista esta vacia o agrego el elemento primero
    List new = malloc(sizeof(Node));
    new->elem = word;
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
    // printf("%s %s\n", aux->elem, word);
    if(strcmp(aux->elem, word) != 0) {
      List new = malloc(sizeof(Node));
      new->elem = word;
      new->hash = hash;
      new->len = wordLen;
      new->next = aux->next;
      aux->next = new;
    }
  }
  return list;
}

void deleteList(List list) {
  if(list != NULL) {
    free(list->elem);
    deleteList(list->next);
    free(list);
  }
}

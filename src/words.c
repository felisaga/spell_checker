#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/hash.h"
#include "../headers/words.h"

WordPointer createWord(char *word) {
  WordPointer new = malloc(sizeof(Word));
  new->word = word;
  return new;
}

List addWordToList(List list, char *word, int wordLen, unsigned int hash, float *chargeFactor, int tableLength) {
  if(list == NULL || (list->hash >= hash && strcmp(list->elem, word) != 0)) { // si la lista esta vacia o agrego el elemento primero
    List new = malloc(sizeof(Node));
    new->elem = createWord(word);
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
      new->elem = createWord(word);
      new->hash = hash;
      new->len = wordLen;
      new->next = aux->next;
      aux->next = new;
    }
  }
  return list;
}

HashTable addWordToTable(HashTable table, char *word, int wordLen, int type) {
  unsigned int hash = murmur3_32(word, wordLen);
  unsigned int index = hash % table->length;
  table->elems[index] = addWordToList(table->elems[index], word, wordLen, hash, table->chargeFactor, table->length);

  if(*(table->chargeFactor) > 0.7) table = rehashTable(table, type);

  return table;
}

void deleteWord(WordPointer elem) {
  free(elem->word);
}

int inDicctionary(HashTable dicc, char *word, int wordLen) {
  unsigned int hash = murmur3_32(word, wordLen);
  unsigned int index = hash % dicc->length;
  if(dicc->elems[index] == NULL)
    return 0;
  else
    return inWordList(dicc->elems[index], word, hash);
}

int inWordList(List list, char *word, unsigned int hash) {
  List aux = list;
  while (aux != NULL) {
    if(aux->hash == hash && strcmp(word, ((WordPointer)(aux->elem))->word) == 0) {
      return 1;
    }
    if(aux->hash > hash)
      return 0;
    aux = aux->next;
  }
  // return 0;
}
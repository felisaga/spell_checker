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
  // printf("word|%s|%p|%d|-hash|%d|-chargeFactor|%f|", word, word, wordLen, hash, *chargeFactor);
  // printf("asdasdasd\n");
  if(list == NULL || (list->hash >= hash && strcmp(((WordPointer)(list->elem))->word, word) != 0)) { // si la lista esta vacia o agrego el elemento primero
    // printf("FIN\n");
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
    // printf("aca\n");
    List aux = list;
    for(;aux->next != NULL && aux->hash < hash; aux = aux->next);  // busco la posicion adecuada por el orden
    if(strcmp(((WordPointer)(aux->elem))->word, word) != 0) {
      // printf("FIN22222\n");
      List new = malloc(sizeof(Node));
      new->elem = createWord(word);
      new->hash = hash;
      new->len = wordLen;
      new->next = aux->next;
      aux->next = new;
      return list;
    }
    free(word);
  }
  return list;
}

HashTable addWordToTable(HashTable table, char *word, int wordLen, int type) {
  // printf("%s\n", word);
  unsigned int hash = murmur3_32(word, wordLen);
  unsigned int index = hash % table->length;
  // printf("word|%s|%d|-hash|%d|-chargeFactor|%f|\n", word, wordLen, hash, *table->chargeFactor);
  // printf("FIN\n");
  table->elems[index] = addWordToList(table->elems[index], word, wordLen, hash, table->chargeFactor, table->length);

  if(*(table->chargeFactor) > 0.7) table = rehashTable(table, type);

  return table;
}

void deleteWord(WordPointer elem) {
  // if(&(elem->word) == 0x5613c211ed70) printf("aca no llego1 |%s|%p|\n", elem->word, elem->word);
  // printf("arriba\n");
  free(elem->word);
  // printf("abajo\n");
  // printf("aca no llego1.5 |%s|\n", elem->word);
}

int inDictionary(HashTable dicc, char *word, int wordLen) {
  unsigned int hash = murmur3_32(word, wordLen);
  unsigned int index = hash % dicc->length;
  // printf("|%s|%d-%u|%p|\n",word, index, hash, dicc->elems[index]);
  if(dicc->elems[index] == NULL){
    return 0;
  }
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
  return 0;
}
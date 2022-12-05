#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../headers/rules.h"
#include "../headers/io.h"
#include "../headers/hash.h"
#include "../headers/words.h"

void test_createWod() {
  WordPointer wp = createWord("hola\0");
  assert(wp != NULL);
  assert(strcmp(wp->word,"hola") == 0);
  free(wp);
}

void test_addWordToList() {
  List l = NULL;
  float f = 0.0;
  l = addWordToList(l, "hola\0", 4, 528, &f, INITIAL_DICC_LENGTH);
  assert(l != NULL);
  assert(l->hash == 528);
  assert(l->next == NULL);
  assert(f != 0.0);
  assert(strcmp(((WordPointer)(l->elem))->word, "hola") == 0);

  free(l->elem);
  free(l);
}

void test_addWordToTable() {
  HashTable t = createHashTable(INITIAL_DICC_LENGTH,0);
  char *word = malloc(sizeof(char) * 5);
  word[0] = 'h';
  word[1] = 'o';
  word[2] = 'l';
  word[3] = 'a';
  word[4] = '\0';
  t = addWordToTable(t, word, 4, 0);
  assert(strcmp(((WordPointer)(t->elems[91312]->elem))->word, "hola") == 0);
  deleteTable(t, 0);
}

void test_inDicctionary() {
  HashTable dictionary = createHashTable(INITIAL_DICC_LENGTH, 0);
  dictionary = readDictionary(dictionary, "./test/testdictionary.txt");
  int x = inDictionary(dictionary, "banana\0", 6);
  assert(x == 1);
  x = inDictionary(dictionary, "banano\0", 6);
  assert(x == 0);
  deleteTable(dictionary, 0);
}

void test_inWordList() {
  List l = NULL;
  float f = 0.0;
  l = addWordToList(l, "hola\0", 4, 528, &f, INITIAL_DICC_LENGTH);
  int x = inWordList(l, "hola\0", 528);
  assert(x == 1);
  x = inWordList(l, "banana\0", 528);
  assert(x == 0);
  free(l->elem);
  free(l);
}

int main() {
  test_createWod();
  test_addWordToList();
  test_addWordToTable();
  test_inDicctionary();
  test_inWordList();
  printf("Test de words ejecutados correctamente.\n");
  return 0;
}
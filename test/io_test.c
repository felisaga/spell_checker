#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../headers/rules.h"
#include "../headers/io.h"
#include "../headers/hash.h"
#include "../headers/words.h"

void test_readDictionary() {
  HashTable dictionary = createHashTable(INITIAL_DICC_LENGTH, 0);
  dictionary = readDictionary(dictionary, "./test/testdictionary.txt");
  assert(inDictionary(dictionary, "holxa\0", 5) == 1);
  assert(inDictionary(dictionary, "banana\0", 6) == 1);
  deleteTable(dictionary, 0);

  HashTable dictionary2 = createHashTable(INITIAL_DICC_LENGTH, 0);
  dictionary2 = readDictionary(dictionary2, "./test/error.txt");
  assert(dictionary2 == NULL);
}

void test_readSuggestions() {
  HashTable suggestions = createHashTable(INITIAL_DICC_LENGTH, 1);
  suggestions = readSuggestions(suggestions, "./test/testsuggestions.txt");
  SuggestionPointer recommendations = NULL;
  recommendations = inSuggestions(suggestions, "papx\0", 4);
  assert(strcmp(recommendations->word, "papx") == 0);

  recommendations = inSuggestions(suggestions, "papa\0", 4);
  assert(recommendations == NULL);
  deleteTable(suggestions, 1);

  HashTable suggestions2 = createHashTable(INITIAL_DICC_LENGTH, 1);
  suggestions2 = readSuggestions(suggestions2, "./test/error.txt");
  assert(suggestions2 == NULL);
}

int main() {
  test_readDictionary();
  test_readSuggestions();
  printf("Test de io ejecutados correctamente.\n");
  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../headers/rules.h"
#include "../headers/io.h"
#include "../headers/hash.h"
#include "../headers/words.h"
#include "../headers/checker.h"

void test_checkSpell() {
  HashTable dictionary = createHashTable(INITIAL_DICC_LENGTH, 0);
  dictionary = readDictionary(dictionary, "./test/testdictionary.txt");
  HashTable suggestions = createHashTable(INITIAL_DICC_LENGTH, 1);
  suggestions = readSuggestions(suggestions, "./test/testsuggestions.txt");
  RecommendationList recommendations = checkSpell("./test/testinput.txt", dictionary, &suggestions);
  assert(recommendations != NULL);
  assert(strcmp(recommendations->recommendations[0], "hola") == 0);
  assert(strcmp(recommendations->recommendations[1], "holxa") == 0);
  assert(recommendations->lenRecommendations == 2);
  SuggestionPointer sugg = NULL;
  sugg = inSuggestions(suggestions, "holx\0", 4);
  assert(strcmp(sugg->word, "holx") == 0);
  assert(strcmp(sugg->suggestions[0], "hola") == 0);
  assert(strcmp(sugg->suggestions[1], "holxa") == 0);

  deleteTable(dictionary, 0);
  deleteTable(suggestions, 1);
  free(recommendations);
}

void test_searchRecommendations() {
  HashTable dictionary = createHashTable(INITIAL_DICC_LENGTH, 0);
  dictionary = readDictionary(dictionary, "./test/testdictionary.txt");
  RecommendationList list = NULL;
  HashTable suggestions = createHashTable(INITIAL_DICC_LENGTH, 1);
  suggestions = readSuggestions(suggestions, "./test/testsuggestions.txt");
  list = searchRecommendations(list, "holx\0", dictionary, 4, 1, &suggestions);
  assert(list != NULL);
  assert(list->lenRecommendations == 2);
  assert(strcmp(list->recommendations[0], "hola") == 0);
  assert(strcmp(list->recommendations[1], "holxa") == 0);

  deleteTable(dictionary, 0);
  free(list);

}

int main() {
  test_checkSpell();
  test_searchRecommendations();
  printf("Test de checker ejecutados correctamente.\n");
  return 0;
}
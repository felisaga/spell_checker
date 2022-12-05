#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../headers/rules.h"
#include "../headers/io.h"
#include "../headers/hash.h"
#include "../headers/words.h"

void test_createSuggestion() {
  char **array = malloc(sizeof(char*));
  char *sug1 = malloc(sizeof(char) * 5);
  sug1[0] = 'h';
  sug1[1] = 'o';
  sug1[2] = 'l';
  sug1[3] = 'a';
  sug1[4] = '\0';
  array[0] = sug1;
  void* sugg = createSuggestion("holx\0", array, 1);
  assert(strcmp(((SuggestionPointer)(sugg))->word, "holx") == 0);
  assert(((SuggestionPointer)(sugg))->lenSuggestions == 1);
  assert(strcmp(((SuggestionPointer)(sugg))->suggestions[0], "hola") == 0);
  free(sug1);
  free(array);
  free(sugg);
}

void test_addSuggestionToList() {
  List l = NULL;
  char **array = malloc(sizeof(char*));
  char *sug1 = malloc(sizeof(char) * 5);
  sug1[0] = 'h';
  sug1[1] = 'o';
  sug1[2] = 'l';
  sug1[3] = 'a';
  sug1[4] = '\0';
  array[0] = sug1;
  float x = 0.0;
  l = addSuggestionToList(l, "holx\0", array, 1, 4, 123, &x, INITIAL_DICC_LENGTH);
  assert(l != NULL);
  assert(l->hash == 123);
  assert(l->next == NULL);
  assert(x != 0.0);
  assert(strcmp(((SuggestionPointer)(l->elem))->word, "holx") == 0);
  assert(strcmp(((SuggestionPointer)(l->elem))->suggestions[0], "hola") == 0);
  free(l->elem);
  free(l);
  free(array);
  free(sug1);
}

void test_addSuggestionToTable() {
  HashTable t = createHashTable(INITIAL_SUGG_LENGTH, 1);
  char *word = malloc(sizeof(char) * 5);
  word[0] = 'h';
  word[1] = 'o';
  word[2] = 'l';
  word[3] = 'x';
  word[4] = '\0';
  char **array = malloc(sizeof(char*));
  char *sug1 = malloc(sizeof(char) * 5);
  sug1[0] = 'h';
  sug1[1] = 'o';
  sug1[2] = 'l';
  sug1[3] = 'a';
  sug1[4] = '\0';
  array[0] = sug1;
  t = addSuggestionToTable(t, word, array, 1, 4, 1);
  assert(strcmp(((SuggestionPointer)(t->elems[8902]->elem))->word, "holx") == 0);
  assert(strcmp(((SuggestionPointer)(t->elems[8902]->elem))->suggestions[0], "hola") == 0);
  assert(((SuggestionPointer)(t->elems[8902]->elem))->lenSuggestions == 1);
  deleteTable(t, 1);
}

void test_inSuggestions() {
  SuggestionPointer suggs = NULL;
  HashTable suggestions = createHashTable(INITIAL_DICC_LENGTH, 1);
  suggestions = readSuggestions(suggestions, "./test/testsuggestions.txt");
  suggs = inSuggestions(suggestions, "pepe\0", 4);
  assert(suggs == NULL);
  suggs = inSuggestions(suggestions, "papx\0", 4);
  assert(strcmp(suggs->word, "papx") == 0);
  assert(strcmp(suggs->suggestions[3], "papu") == 0);
  assert(suggs->lenSuggestions == 4);
  deleteTable(suggestions, 1);
}

void test_inSuggestionList() {
  List l = NULL;
  char **array = malloc(sizeof(char*));
  char *sug1 = malloc(sizeof(char) * 5);
  sug1[0] = 'h';
  sug1[1] = 'o';
  sug1[2] = 'l';
  sug1[3] = 'a';
  sug1[4] = '\0';
  array[0] = sug1;
  float x = 0.0;
  l = addSuggestionToList(l, "holx\0", array, 1, 4, 123, &x, INITIAL_DICC_LENGTH);
  SuggestionPointer suggs = NULL;
  suggs = inSuggestionsList(l, "banana\0", 200);
  assert(suggs == NULL);
  suggs = inSuggestionsList(l, "banana\0", 123);
  assert(suggs == NULL);
  suggs = inSuggestionsList(l, "holx\0", 200);
  assert(suggs == NULL);
  suggs = inSuggestionsList(l, "holx\0", 123);
  assert(suggs != NULL);
  assert(suggs->lenSuggestions == 1);
  assert(strcmp(suggs->word, "holx") == 0);
  assert(strcmp(suggs->suggestions[0], "hola") == 0);
  free(l->elem);
  free(l);
  free(array);
  free(sug1);
}

void test_addToRecommendations() {
  RecommendationList l = NULL;
  char **array = malloc(sizeof(char*));
  char *sug1 = malloc(sizeof(char) * 5);
  sug1[0] = 'h';
  sug1[1] = 'o';
  sug1[2] = 'l';
  sug1[3] = 'a';
  sug1[4] = '\0';
  array[0] = sug1;
  char *word = malloc(sizeof(char) * 5);
  word[0] = 'h';
  word[1] = 'o';
  word[2] = 'y';
  word[3] = 'o';
  word[4] = '\0';
  l = addToRecommendations(l, word, array, 1, 1, 0);
  assert(l != NULL);
  assert(strcmp(l->word, "hoyo") == 0);
  assert(strcmp(l->recommendations[0], "hola") == 0);
  assert(l->line == 1);
  assert(l->lenRecommendations == 1);
  assert(l->new == 0);
  free(l);
  free(word);
  free(array);
  free(sug1);
}

void test_addWordToRecommendation() {
  char **array = malloc(sizeof(char*));
  char *sug1 = malloc(sizeof(char) * 5);
  sug1[0] = 'h';
  sug1[1] = 'o';
  sug1[2] = 'l';
  sug1[3] = 'a';
  sug1[4] = '\0';
  array[0] = sug1;
  char *word = malloc(sizeof(char) * 5);
  word[0] = 'h';
  word[1] = 'o';
  word[2] = 'y';
  word[3] = 'o';
  word[4] = '\0';
  int x = 1;
  array = addWordToReccomendation(array, word, &x);
  assert(strcmp(array[1], "hoyo") == 0);
  assert( x == 2);
  free(word);
  free(array);
  free(sug1);
}

void test_inRecommendations() {
  char **array = NULL;
  int x = 0;
  array = addWordToReccomendation(array, "hola\0", &x);
  array = addWordToReccomendation(array, "holx\0", &x);
  int f = inReccomendations(array, x, "hola");
  assert(f == 1);
  f = inReccomendations(array, x, "pera");
  assert(f == 0);
  free(array);
}

int main() {
  test_createSuggestion();
  test_addSuggestionToList();
  test_addSuggestionToTable();
  test_inSuggestions();
  test_inSuggestionList();
  test_addToRecommendations();
  test_addWordToRecommendation();
  test_inRecommendations();
  printf("Test de suggestions ejecutados correctamente.\n");
  return 0;
}
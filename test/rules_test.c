#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../headers/rules.h"
#include "../headers/io.h"
#include "../headers/hash.h"
#include "../headers/words.h"

void test_splitWord() {
  HashTable dictionary = createHashTable(INITIAL_DICC_LENGTH, 0);
  dictionary = readDictionary(dictionary, "./test/testdictionary.txt");
  HashTable stepTable = createHashTable(INITIAL_DICC_LENGTH, 0);
  int lenRecommendations = 0;
  char **recommendations = NULL;
  recommendations = splitWord("bananapera\0", dictionary, stepTable, 10, &lenRecommendations, recommendations, 1, 1);
  assert(strcmp(recommendations[0], "banana pera") == 0);
  assert(inDictionary(stepTable, "banana pera\0", 11) == 0);  // esta regla no mete palabras en la step table

  deleteTable(dictionary,0);
  deleteTable(stepTable,0);
  free(recommendations[0]);
  free(recommendations);
}

void test_deleteLetters() {
  HashTable dictionary = createHashTable(INITIAL_DICC_LENGTH, 0);
  dictionary = readDictionary(dictionary, "./test/testdictionary.txt");
  HashTable stepTable = createHashTable(INITIAL_DICC_LENGTH, 0);
  int lenRecommendations = 0;
  char **recommendations = NULL;
  recommendations = deleteLetters("holax\0", dictionary, stepTable, 5, &lenRecommendations, recommendations, 1, 1);
  assert(strcmp(recommendations[0], "hola") == 0);
  assert(inDictionary(stepTable, "hola\0", 4) == 1);  // esta regla mete palabras en la step table
  
  deleteTable(stepTable,0);
  free(recommendations[0]);
  free(recommendations);

  HashTable stepTable2 = createHashTable(INITIAL_DICC_LENGTH, 0);
  int lenRecommendations2 = 0;
  char **recommendations2 = NULL;
  recommendations2 = deleteLetters("holax\0", dictionary, stepTable, 5, &lenRecommendations2, recommendations2, 1, 3);
  assert(inDictionary(stepTable2, "hola\0", 4) == 0);  // si es paso 3 no se deben meter las palabras

  deleteTable(dictionary,0);
  deleteTable(stepTable2,0);
  free(recommendations2[0]);
  free(recommendations2);
}

void test_switchLetters() {
  HashTable dictionary = createHashTable(INITIAL_DICC_LENGTH, 0);
  dictionary = readDictionary(dictionary, "./test/testdictionary.txt");
  HashTable stepTable = createHashTable(INITIAL_DICC_LENGTH, 0);
  int lenRecommendations = 0;
  char **recommendations = NULL;
  recommendations = switchLetters("holax\0", dictionary, stepTable, 5, &lenRecommendations, recommendations, 1, 1);
  assert(strcmp(recommendations[0], "holxa") == 0);
  assert(inDictionary(stepTable, "holxa\0", 5) == 1);  // esta regla mete palabras en la step table

  deleteTable(dictionary,0);
  deleteTable(stepTable,0);
  free(recommendations[0]);
  free(recommendations);
}

void test_replaceLetters() {
  HashTable dictionary = createHashTable(INITIAL_DICC_LENGTH, 0);
  dictionary = readDictionary(dictionary, "./test/testdictionary.txt");
  HashTable stepTable = createHashTable(INITIAL_DICC_LENGTH, 0);
  int lenRecommendations = 0;
  char **recommendations = NULL;
  recommendations = replaceLetters("pero\0", dictionary, stepTable, 4, &lenRecommendations, recommendations, 1, 1);
  assert(strcmp(recommendations[0], "pera") == 0);
  assert(inDictionary(stepTable, "pera\0", 4) == 1);  // esta regla mete palabras en la step table

  deleteTable(dictionary,0);
  deleteTable(stepTable,0);
  free(recommendations[0]);
  free(recommendations);
}

void test_insertLetters() {
  HashTable dictionary = createHashTable(INITIAL_DICC_LENGTH, 0);
  dictionary = readDictionary(dictionary, "./test/testdictionary.txt");
  HashTable stepTable = createHashTable(INITIAL_DICC_LENGTH, 0);
  int lenRecommendations = 0;
  char **recommendations = NULL;
  recommendations = insertLetters("hola\0", dictionary, stepTable, 4, &lenRecommendations, recommendations, 1, 1);
  assert(strcmp(recommendations[0], "holxa") == 0);
  assert(inDictionary(stepTable, "holxa\0", 5) == 1);  // esta regla mete palabras en la step table

  deleteTable(dictionary,0);
  deleteTable(stepTable,0);
  free(recommendations[0]);
  free(recommendations);
}

int main() {
  test_splitWord();
  test_deleteLetters();
  test_switchLetters();
  test_replaceLetters();
  test_insertLetters();
  printf("Test de rules ejecutados correctamente.\n");
  return 0;
}
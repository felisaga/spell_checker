
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/hash.h"
#include "./headers/io.h"
#include "./headers/words.h"
#include "./headers/suggestions.h"
#include "./headers/checker.h"

int main(int argc, char *argv[]) { // argv = [ejecutable, archivo de entrada, archivo de salida, diccionario, sugerencias]
  HashTable dictionary = createHashTable(INITIAL_DICC_LENGTH, 0);
  dictionary = readDictionary(dictionary, argv[3]);
  if (dictionary == NULL) { // si no se puede abrir el archivo diccionario termina el programa
    return 0;
  }

  HashTable suggestions = createHashTable(INITIAL_SUGG_LENGTH, 1);
  suggestions = readSuggestions(suggestions, argv[4]);

  RecommendationList recommendations = checkSpell(argv[1], dictionary, &suggestions);

  printRecommendations(recommendations, argv[2], argv[4]);
  
  deleteTable(dictionary, 0);
  deleteTable(suggestions, 1);
  deleteRecommendations(recommendations);
  return 0;
}
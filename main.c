
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./headers/hash.h"
#include "./headers/io.h"

#define INITIAL_TABLE_LENGTH 100000

int main(int argc, char *argv[]) { // argv = [ejecutable, archivo de entrada, archivo de salida, diccionario, sugerencias]
  FILE *f = fopen(argv[1], "rb");
  if (f == NULL) { // si no se puede abrir el archivo de entrada termina el programa
		printf("Error al abrir el archivo de texto.\n");
    return 0;
  }
  HashTable dictionary = createHashTable(INITIAL_TABLE_LENGTH);

  dictionary = readDictionary(dictionary, argv[3]);

  printf("\nlargo: %d - factor de carga: %f\n", dictionary->length, *dictionary->chargeFactor);

  deleteTable(dictionary);

  // HashTable table = malloc(sizeof(HashTable));
  // table->elems = calloc(1, sizeof(List));

  // free(table->elems);
  // free(table->elems[0]);
  // HashTable table = createHashTable(INITIAL_TABLE_LENGTH);
  // deleteTable(table);

  // free(table);

  fclose(f);

  return 0;
  
}
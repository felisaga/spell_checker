#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../headers/hash.h"

#define MAX_WORD_LENGTH 100

HashTable readDictionary(HashTable table, char* path) {
	FILE *f = fopen(path, "rb");
  if (f == NULL) { // si no se puede abrir el diccionario devuelvo NULL
		printf("Error al abrir el diccionario.\n");
    return NULL;
  }
  int i = 0, flag = 1;
  char wordBuff[MAX_WORD_LENGTH], c;

  while(flag) {
    c = getc(f);
    if(c != '\n' && c != EOF && c != 13) {
		  wordBuff[i++] = tolower(c);
    }
    // if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) wordBuff[i++] = tolower(c);
    else if (c != 10) {//10 inicio de linea
      wordBuff[i] = '\0';
      char *word = malloc(sizeof(char) * (i + 2));
      strcpy(word, wordBuff);
      table = addElementToTable(table, word, i + 1);
      i = 0;
    }
    if(c == EOF) flag = 0;
  }
  
  fclose(f);
  return table;
}


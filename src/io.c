#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// #include "../headers/hash.h"
#include "../headers/words.h"
#include "../headers/suggestions.h"

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
      char *word = malloc(sizeof(char) * (i + 1));
      strcpy(word, wordBuff);
      // table = addElementToTable(table, word, i + 1, 0);
      table = addWordToTable(table, word, i + 1, 0);
      i = 0;
    }
    if(c == EOF) flag = 0;
  }
  
  fclose(f);
  return table;
}

HashTable readSuggestions(HashTable table, char* path) {
  FILE *f = fopen(path, "rb");
  if (f == NULL) { // si no se puede abrir el archivo de sugerencias devuelvo NULL
		printf("Error al abrir el archivo de sugerencias.\n");
    return NULL;
  }
  int i = 0, flag = 1, wordFlag = 1, len = 0, wordLen = 0;
  char wordBuff[MAX_WORD_LENGTH], c;
  // char **array = NULL;
  char **array = calloc(1,sizeof(char*));
  char *word = malloc(sizeof(char));

  while(flag) {
    c = getc(f);
    // printf("|%c| -- %d\n", c, c);
    if(c != ',' && c != '\n' && c != 13 && c != EOF && c != 10 && c != ' ') {
      wordBuff[i++] = c;
    } else if (c != ' ') {//10 inicio de linea - 13 retorno de linea //' ' despues de la coma
      wordBuff[i] = '\0';
      if(wordFlag) {
        word = realloc(word, sizeof(char) * (i + 1));
      // char *word = malloc(sizeof(char) * (i + 1));
      strcpy(word, wordBuff);
        wordLen = i + 1;
        i = 0;
        wordFlag = 0;
      } else {
        char *sugg = malloc(sizeof(char) * (i + 1));
        strcpy(sugg, wordBuff);
        array = addSuggestion(array, sugg, len);
        len ++;
        i = 0;
      }
    } 
    // else {
    if(c == '\n' || c == 13 || c == 10) { //si encuentra un \n o retorno de carro
      table = addSuggestionToTable(table, word, array, len, wordLen, 1);      
      len = 0;
      wordFlag = 1;
      word = malloc(sizeof(char));
      array = calloc(1,sizeof(char*));
    } 
    if(c == EOF) flag = 0;
  }


  fclose(f);
  return table;
}

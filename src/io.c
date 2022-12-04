#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// #include "../headers/hash.h"
#include "../headers/words.h"
#include "../headers/suggestions.h"
#include "../headers/io.h"

HashTable readDictionary(HashTable table, char* path) {
	FILE *f = fopen("./dictionary.txt", "rb");
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
      table = addWordToTable(table, word, i, 0);
      i = 0;
    }
    if(c == EOF) flag = 0;
  }
  
  fclose(f);
  return table;
}

HashTable readSuggestions(HashTable table, char* path) {
  FILE *f = fopen("./suggestions.txt", "rb");
  if (f == NULL) { // si no se puede abrir el archivo de sugerencias devuelvo NULL
		printf("Error al abrir el archivo de sugerencias.\n");
    return NULL;
  }
  int i = 0, flag = 1, wordFlag = 1, len = 0, wordLen = 0;
  char wordBuff[MAX_WORD_LENGTH], c;
  char **array = calloc(1,sizeof(char*));
  char *word = malloc(sizeof(char));

  while(flag) {
    c = getc(f);
    if(c != ',' && c != '\n' && c != 13 && c != EOF && c != 10) {
      if(c == ' ' && i != 0) wordBuff[i++] = c;       //para evitar los espacios despues de la coma
      else if(c != ' ') wordBuff[i++] = c;
    } else if (c != ' ') {                            //10 inicio de linea - 13 retorno de linea //' ' despues de la coma
      wordBuff[i] = '\0';
      if(wordFlag) {
        word = realloc(word, sizeof(char) * (i + 1));
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
    if(c == '\n' || c == 13 || c == 10 || c == EOF) { //si encuentra un \n o retorno de carro
      table = addSuggestionToTable(table, word, array, len, wordLen-1, 1);
      len = 0;
      wordFlag = 1;
      word = malloc(sizeof(char));                    //para las siguientes sugerencias que pueda haber
      array = calloc(1,sizeof(char*));
    } 
    if(c == EOF) {
      flag = 0;
      free(word);                                     //si no hay mas sugerencias
      free(array[0]);
      free(array);
    }
  }
  fclose(f);
  return table;
}

void printRecommendations(RecommendationList list, char *path) {
  if(list == NULL) return;
  FILE *corrections = fopen("./corrections.txt", "w");
  FILE *suggestions = fopen(path, "a+");
  RecommendationList aux = list;
  while (aux != NULL) {
    fprintf(corrections, "Linea %d, \"%s\" no esta en el diccionario.", aux->line, aux->word);
    if(aux->recommendations == NULL) {
      fprintf(corrections, "\nNo se encontraron sugerencias.\n");
    } else {
      if(aux->new) fprintf(suggestions, "\n%s, ", aux->word);
      fprintf(corrections, "\nQuizas quiso decir: ");
      for (int i = 0; i < aux->lenRecommendations-1; i++) {
        fprintf(corrections,"%s, ", aux->recommendations[i]);
        if(aux->new) fprintf(suggestions,"%s, ", aux->recommendations[i]);
      }
      fprintf(corrections,"%s\n", aux->recommendations[aux->lenRecommendations - 1]);
      if(aux->new) fprintf(suggestions,"%s", aux->recommendations[aux->lenRecommendations - 1]);
    }
    aux = aux->next;
  }
  fclose(corrections);
  fclose(suggestions);
}

// void printNewSuggestions(RecommendationList list, char *path) {
//   FILE *f = fopen(path, "a+");
//   fclose(f);
// }

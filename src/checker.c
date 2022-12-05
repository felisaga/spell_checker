#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../headers/hash.h"
#include "../headers/words.h"
#include "../headers/suggestions.h"
#include "../headers/io.h"
#include "../headers/rules.h"
#include "../headers/checker.h"

RecommendationList checkSpell(char *path, HashTable dictionary, HashTable *suggestions) { // si es null es porque no se abrio el archivo o no hay recomendaciones
  FILE *f = fopen(path, "rb");
  if (f == NULL) { // si no se puede abrir el texto devuelvo NULL
		printf("Error al abrir el archivo de texto.\n");
    fclose(f);
    return NULL;
  }
  int i = 0, line = 1, sugg = 1, flag=1;
  if((*suggestions) == NULL) {
    sugg = 0;
  }
  char c, wordBuff[MAX_WORD_LENGTH];
  SuggestionPointer recommendations = NULL;
  RecommendationList list = NULL;

  while(flag) {
    c=getc(f);
    if (c != '\n' && c != '!' && c != '?' && c != '.' && c != ',' && c != ';' && c != ':' && c != ' ' && c != EOF) {
		  wordBuff[i++] = tolower(c);
    } else if(i != 0) {      
      wordBuff[i] = '\0';
      char *word = malloc(sizeof(char) * i + 1);
      strcpy(word, wordBuff);

      if(sugg && (recommendations = inSuggestions((*suggestions), word, i)) != NULL) {
        list = addToRecommendations(list, recommendations->word, recommendations->suggestions, recommendations->lenSuggestions, line, 0);
        free(word);
      } else {
        if(!inDictionary(dictionary, word, i)) {
          list = searchRecommendations(list, word, dictionary, i, line, suggestions);
        } else {
          free(word);
        }
      }

      i=0;
      if (c == '\n') line++;
    }
    if(c == EOF) flag = 0;
  }
  
  fclose(f);
  return list;
}

RecommendationList searchRecommendations(RecommendationList list, char *word, HashTable dictionary, int wordLen, int line, HashTable *suggestions) {
  HashTable step1Table = createHashTable(INITIAL_DICC_LENGTH, 0);
  HashTable step2Table = createHashTable(INITIAL_DICC_LENGTH, 0);
  int lenSuggestions = 0;
  char **recommendations = NULL;
  for(int step = 1; step < 4 && lenSuggestions < 5; step++) {
    if(step == 1) {
      recommendations = splitWord(word, dictionary, step1Table, wordLen, &lenSuggestions, recommendations, line, step);
      recommendations = deleteLetters(word, dictionary, step1Table, wordLen, &lenSuggestions, recommendations, line, step);
      recommendations = switchLetters(word, dictionary, step1Table, wordLen, &lenSuggestions, recommendations, line, step);
      recommendations = replaceLetters(word, dictionary, step1Table, wordLen, &lenSuggestions, recommendations, line, step);
      recommendations = insertLetters(word, dictionary, step1Table, wordLen, &lenSuggestions, recommendations, line, step);
    }

    if(step == 2) {
      for(unsigned int i = 0; i < step1Table->length && lenSuggestions < 5; i++) {
        if(step1Table->elems[i] != NULL) {
          List aux = step1Table->elems[i];
          while(aux != NULL) {
            int auxWordLen = aux->len;
            recommendations = splitWord(((WordPointer)(aux->elem))->word, dictionary, step2Table, auxWordLen, &lenSuggestions, recommendations, line, step);
            recommendations = deleteLetters(((WordPointer)(aux->elem))->word, dictionary, step2Table, auxWordLen, &lenSuggestions, recommendations, line, step);
            recommendations = switchLetters(((WordPointer)(aux->elem))->word, dictionary, step2Table, auxWordLen, &lenSuggestions, recommendations, line, step);
            recommendations = replaceLetters(((WordPointer)(aux->elem))->word, dictionary, step2Table, auxWordLen, &lenSuggestions, recommendations, line, step);
            recommendations = insertLetters(((WordPointer)(aux->elem))->word, dictionary, step2Table, auxWordLen, &lenSuggestions, recommendations, line, step);
            aux = aux->next;
          }
        }
      }
    }
    if(step == 3) {
      for(unsigned int i = 0; i < step2Table->length && lenSuggestions < 5; i++) {
        if(step2Table->elems[i] != NULL) {
          List aux = step2Table->elems[i];
          while(aux != NULL) {
            int auxWordLen = aux->len;
            recommendations = splitWord(((WordPointer)(aux->elem))->word, dictionary, step2Table, auxWordLen, &lenSuggestions, recommendations, line, step);
            recommendations = deleteLetters(((WordPointer)(aux->elem))->word, dictionary, step2Table, auxWordLen, &lenSuggestions, recommendations, line, step);
            recommendations = switchLetters(((WordPointer)(aux->elem))->word, dictionary, step2Table, auxWordLen, &lenSuggestions, recommendations, line, step);
            recommendations = replaceLetters(((WordPointer)(aux->elem))->word, dictionary, step2Table, auxWordLen, &lenSuggestions, recommendations, line, step);
            recommendations = insertLetters(((WordPointer)(aux->elem))->word, dictionary, step2Table, auxWordLen, &lenSuggestions, recommendations, line, step);
            aux = aux->next;
          }
        }
      }
    }
  }
  deleteTable(step1Table, 0);
  deleteTable(step2Table, 0);
  if (recommendations != NULL) {
    list = addToRecommendations(list, word, recommendations, lenSuggestions, line, 1);
    *suggestions = addSuggestionToTable((*suggestions), word, recommendations, lenSuggestions, wordLen, 1);
  } else {
    list = addToRecommendations(list, word, recommendations, lenSuggestions, line, 1);
    *suggestions = addSuggestionToTable(*suggestions, word, recommendations, lenSuggestions, wordLen, 1);
  }
  return list;
}

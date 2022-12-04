#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/hash.h"
#include "../headers/suggestions.h"
#include "../headers/words.h"

char** splitWord(char *word, HashTable dictionary, HashTable stepTable, int wordLen, int *lenRecommendations, char **recommendations, int line, int step) {
  for(int i = 1; i < wordLen && (*lenRecommendations) < 5; i++) {
    char *part1 = malloc(sizeof(char) * (wordLen + 2));
    memcpy(part1, word, i);
    part1[i] = '\0';
    char *part2 = word + i;
    if(inDictionary(dictionary, part1, i) && inDictionary(dictionary, part2, wordLen-i)) {
      part1[i] = ' ';
      memcpy(part1+i+1, word+i, wordLen-i);
      part1[wordLen+1] = '\0';
      recommendations = addWordToReccomendation(recommendations, part1, lenRecommendations);
    } else {
      free(part1);
    }
  }
  return recommendations;
}

char** deleteLetters(char *word, HashTable dictionary, HashTable stepTable, int wordLen, int *lenRecommendations, char **recommendations, int line, int step) {
    // printf("%s\n", word);
  for(int i = 0; i < wordLen && (*lenRecommendations) < 5; i++) {
    char *sample = malloc(sizeof(char) * (wordLen+1));
    // memcpy(sample, word, i);
    // memcpy(sample + i , word + i + 1, wordLen - (i + 1));
    // sample[wordLen - 1] = '\0';

        for (int j = 0; j < wordLen; j++)
            if (j < i)
                sample[j] = word[j];
            else
                sample[j] = word[j + 1];
        sample[wordLen] = '\0';
    if(inDictionary(dictionary, sample, wordLen-1)) {
      recommendations = addWordToReccomendation(recommendations, sample, lenRecommendations);
      if(step != 3) {
      char *copy = malloc(sizeof(char) * (wordLen+1));
      strcpy(copy, sample);
      stepTable = addWordToTable(stepTable, copy, wordLen-1, 0);
      }
    } else {
      if(step != 3) {
        // printf("biennnn!!!|%s|\n", sample);
        stepTable = addWordToTable(stepTable, sample, wordLen-1, 0);
      } else {
        free(sample);
      }
    }
  }
  return recommendations;
}

char** swtichLetters(char *word, HashTable dictionary, HashTable stepTable, int wordLen, int *lenRecommendations, char **recommendations, int line, int step) {
  for(int i = 0; i < (wordLen - 1) && (*lenRecommendations) < 5; i++) {
    char c = word[i];
    char *sample = malloc(sizeof(char) * (wordLen+1));
    memcpy(sample, word, wordLen);
    sample[i] = word[i+1];
    sample[i+1] = c;
    sample[wordLen] = '\0';
    if(inDictionary(dictionary, sample, wordLen-1)) {
      recommendations = addWordToReccomendation(recommendations, sample, lenRecommendations);
      if(step != 3) {
      char *copy = malloc(sizeof(char) * (wordLen+1));
      strcpy(copy, sample);
      stepTable = addWordToTable(stepTable, copy, wordLen, 0);
      }
    } else {
      if(step != 3) {
        stepTable = addWordToTable(stepTable, sample, wordLen, 0);  
      } else {
        free(sample);
      }
    }
  }
  return recommendations;
}

char** replaceLetters(char *word, HashTable dictionary, HashTable stepTable, int wordLen, int *lenRecommendations, char **recommendations, int line, int step) {
  for(int i = 0; i < wordLen && (*lenRecommendations) < 5; i++) {
    for(char c = 'a'; c <= 'z' && (*lenRecommendations) < 5 ; c++) {
      char *sample = malloc(sizeof(char) * (wordLen+1));
      // memcpy(sample, word, wordLen);
      strcpy(sample, word);
      sample[i] = c;
      sample[wordLen] = '\0';
      if(inDictionary(dictionary, sample, wordLen)) {
        recommendations = addWordToReccomendation(recommendations, sample, lenRecommendations);
        if(step != 3) {
        char *copy = malloc(sizeof(char) * (wordLen+1));
        strcpy(copy, sample);
        stepTable = addWordToTable(stepTable, copy, wordLen, 0);
        }
        // free(sample);
      } else {
        if(step != 3) {
          stepTable = addWordToTable(stepTable, sample, wordLen, 0);
        } else {
          free(sample);
        }
      }
    }
  }
  return recommendations;
}

char** insertLetters(char *word, HashTable dictionary, HashTable stepTable, int wordLen, int *lenRecommendations, char **recommendations, int line, int step) {
  for (int i = 0; i < (wordLen + 1) && (*lenRecommendations) < 5; i++) {
    for (char c = 'a'; c <= 'z' && (*lenRecommendations) < 5 ; c++) {
      char *sample = malloc(sizeof(char) * (wordLen + 2));
      memcpy(sample, word, i);
      memcpy(sample + i + 1, word + i, wordLen - i);
      sample[i] = c;
      sample[wordLen + 1] = '\0';
      if(inDictionary(dictionary, sample, wordLen-1)) {
        recommendations = addWordToReccomendation(recommendations, sample, lenRecommendations);
        if(step != 3) {
        char *copy = malloc(sizeof(char) * (wordLen+2));
        strcpy(copy, sample);
        stepTable = addWordToTable(stepTable, copy, wordLen+1, 0);
        }
      } else {
        if(step != 3) {
          stepTable = addWordToTable(stepTable, sample, wordLen+1, 0);
        } else {
          free(sample);
        }
      }
    }
  }
  return recommendations;
}

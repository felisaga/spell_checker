#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "../headers/hash.h"
#include "../headers/words.h"
#include "../headers/suggestions.h"
#include "../headers/io.h"

RecommendationList checkSpell(char *path, HashTable dicctionary, HashTable suggestions) { // si es null es porque no se abrio el archivo o no hay recomendaciones
  FILE *f = fopen(path, "rb");
  if (f == NULL) { // si no se puede abrir el texto devuelvo NULL
		printf("Error al abrir el archivo de texto.\n");
    return NULL;
  }
  int i = 0, line = 1, sugg = 1;
  if(suggestions == NULL) sugg = 0;
  char c, wordBuff[MAX_WORD_LENGTH];
  SuggestionPointer recommendations = NULL;
  RecommendationList list = NULL;

  while(c=getc(f) !=  EOF) {
    if (c != '\n' && c != '!' && c != '?' && c != '.' && c != ',' && c != ';' && c != ':' && c != ' ') {
		  wordBuff[i++] = tolower(c); 
    } else {
      if (c == '\n') line++;
      wordBuff[i] = '\0';
      char *word = malloc(sizeof(char) * i + 1);
      strcpy(word, wordBuff);

      if(!inDicctionary(dicctionary, word, i)) {
        if(list == NULL) list = malloc(sizeof(RecommendationList));

        if(sugg && (recommendations = inSuggestions(suggestions, word, i) != NULL)) {
          addToRecommendations(list, recommendations->word, recommendations->suggestions, recommendations->lenSuggestions, line, 0);
        } else {
          // searchRecommendations();
        }
      }
    }

  } 
}

/*
  insuggestions devuelve el array copiado
  si no esta en las sugerencias los metodos me devuelven un array
  y lo meto en la tabla de sugerencias
*/
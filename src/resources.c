#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/hash.h"
#include "../headers/suggestions.h"
#include "../headers/words.h"

void deleteList(List list, int type) {
  if(list != NULL) {
    if(!type) {
      deleteWord(list->elem);
    } else {
      deleteSuggestions(list->elem);
    }
    free(list->elem);
    deleteList(list->next, type);
    free(list);
  }
}

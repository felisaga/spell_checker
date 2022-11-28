#ifndef __RESOURCES_H_
#define __RESOURCES_H_

#include "./hash.h"

// Funcion que agrega un elemento a una lista enlazada de manera ordenada dependiendo de su hash y modifica el factor de carga si es necesario
// List addElementToList(List list, char *word, int wordLen, unsigned int hash, float *chargeFactor, int tableLength, int type);


// Funcion que libera la memoria ocupada por una lista
void deleteList(List list, int type);

// void *addWordToList(char *word, int type);

#endif
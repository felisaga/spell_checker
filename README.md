## Trabajo Practico Estructuras y Algoritmos 1


# Felipe Sagarraga

Implementación de un corrector ortográfico en lenguaje C.

## Instrucciones de uso

Para utilizar el programa es necesario tener en el mismo directorio un archivo "dictionary.txt" que contiene las palabras del diccionario y un archivo  "input.txt" que contiene el texto a corregir.
De manera opcional se puede tener un archivo de sugerencias "suggestions.txt".

El diccionario tiene que tener el siguiente formato:
palabra1

palabra2

palabra3

...

Las sugerencias deben tener el siguiente formato:

Palabra, nro_sugerencias, sugerencia_1, ..., sugerencia_n
...

Para compilar el programa usar:
```
make compile
```
Para compilar y ejecutar el programa usar:
```
make check_spell
```
De manera manual se puede compilar y correr el programa de la siguiente manera:
```
gcc -g -Wall -std=c99 main.c -Wall ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c ./src/rules.c -o check_spell.out
./check_spell.out [input] [output] [dictionary] [suggestions]
```
Donde input es el archivo de texto a corregir, output es el archivo donde se guardaran las correcciones, dictionary es el archivo de diccionario, suggestions es el archivo que contiene las sugerencias (y se le agregan mas si se encuentran)

Para correr todos los test usar:
```
make test_all
```
Y para correr individualmente cada test usar
```
make [parte]_test
```
Donde [parte] puede ser "rules", "io", "checker", "hash", "words", "suggestions",

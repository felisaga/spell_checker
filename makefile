check_spell: main.c ./src/checker.c ./src/hash.c ./src/io.c ./src/resources.c
	- gcc -g -Wall -std=c99 main.c ./src/hash.c ./src/checker.c ./src/io.c ./src/resources.c -o check_spell
	- ./check_spell input.txt output.txt dictionary.txt suggestions.txt

valgrind: main.c ./src/checker.c ./src/hash.c ./src/io.c ./src/resources.c
	- gcc -g -Wall -std=c99 main.c ./src/hash.c ./src/checker.c ./src/io.c ./src/resources.c -o check_spell
	- valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./check_spell input.txt output.txt dictionary.txt suggestions.txt
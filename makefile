check_spell: main.c ./src/checker.c ./src/hash.c ./src/io.c ./src/resources.c
	- gcc -g -Wall -std=c99 main.c ./src/hash.c ./src/checker.c ./src/io.c ./src/resources.c -o check_spell.out
	- ./check_spell.out input.txt output.txt dictionary.txt suggestions.txt

compile: main.c ./src/checker.c ./src/hash.c ./src/io.c ./src/resources.c ./src/words.c ./src/suggestions.c
	- gcc -g -Wall -std=c99 main.c ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c -o check_spell.out
	- ./check_spell.out input.txt output.txt dictionary.txt suggestions.txt

valgrind: main.c ./src/checker.c ./src/hash.c ./src/io.c ./src/resources.c
	- gcc -g -Wall -std=c99 main.c ./src/hash.c ./src/checker.c ./src/io.c ./src/resources.c -o check_spell.out
	- valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./check_spell.out input.txt output.txt dictionary.txt suggestions.txt

balgrind: main.c ./src/checker.c ./src/hash.c ./src/io.c ./src/resources.c ./src/words.c ./src/suggestions.c
	- gcc -g -Wall -std=c99 main.c ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c -o check_spell.out
	- valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./check_spell.out input.txt output.txt dictionary.txt suggestions.txt
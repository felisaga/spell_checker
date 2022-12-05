compile: main.c ./src/checker.c ./src/hash.c ./src/io.c ./src/resources.c ./src/words.c ./src/suggestions.c ./src/rules.c
	- gcc -g -Wall -std=c99 main.c -Wall ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c ./src/rules.c -o check_spell.out

check_spell: main.c ./src/checker.c ./src/hash.c ./src/io.c ./src/resources.c ./src/words.c ./src/suggestions.c ./src/rules.c
	- gcc -g -Wall -std=c99 main.c -Wall ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c ./src/rules.c -o check_spell.out
	- ./check_spell.out input.txt output.txt dictionary.txt suggestions.txt

valgrind: main.c ./src/checker.c ./src/hash.c ./src/io.c ./src/resources.c ./src/words.c ./src/suggestions.c ./src/rules.c
	- gcc -g -Wall -std=c99 main.c ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c ./src/rules.c -o check_spell.out
	- valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./check_spell.out input.txt output.txt dictionary.txt suggestions.txt

rules_test: ./test/rules_test.c ./src/checker.c ./src/hash.c ./src/io.c ./src/resources.c ./src/words.c ./src/suggestions.c ./src/rules.c
	- gcc -g -Wall -std=c99 -Wall ./test/rules_test.c ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c ./src/rules.c -o rules_test.out
	- ./rules_test.out

io_test: ./test/io_test.c ./src/checker.c ./src/hash.c ./src/io.c ./src/resources.c ./src/words.c ./src/suggestions.c ./src/rules.c
	- gcc -g -Wall -std=c99 -Wall ./test/io_test.c ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c ./src/rules.c -o io_test.out
	- ./io_test.out

checker_test: ./test/checker_test.c ./src/checker.c ./src/hash.c ./src/io.c ./src/resources.c ./src/words.c ./src/suggestions.c ./src/rules.c
	- gcc -g -Wall -std=c99 -Wall ./test/checker_test.c ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c ./src/rules.c -o checker_test.out
	- ./checker_test.out

hash_test: ./test/hash_test.c ./src/checker.c ./src/hash.c ./src/io.c ./src/resources.c ./src/words.c ./src/suggestions.c ./src/rules.c
	- gcc -g -Wall -std=c99 -Wall ./test/hash_test.c ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c ./src/rules.c -o hash_test.out
	- ./hash_test.out

words_test: ./test/words_test.c ./src/checker.c ./src/hash.c ./src/io.c ./src/resources.c ./src/words.c ./src/suggestions.c ./src/rules.c
	- gcc -g -Wall -std=c99 -Wall ./test/words_test.c ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c ./src/rules.c -o words_test.out
	- ./words_test.out

suggestions_test: ./test/suggestions_test.c ./src/checker.c ./src/hash.c ./src/io.c ./src/resources.c ./src/words.c ./src/suggestions.c ./src/rules.c
	- gcc -g -Wall -std=c99 -Wall ./test/suggestions_test.c ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c ./src/rules.c -o suggestions_test.out
	- ./suggestions_test.out

test_all: ./src/hash.c ./src/io.c ./src/resources.c ./src/words.c ./src/suggestions.c ./src/rules.c ./test/rules_test.c ./test/io_test.c ./test/checker_test.c ./test/hash_test.c ./test/words_test.c ./test/suggestions_test.c
	- gcc -g -Wall -std=c99 -Wall ./test/rules_test.c ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c ./src/rules.c -o rules_test.out
	- gcc -g -Wall -std=c99 -Wall ./test/io_test.c ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c ./src/rules.c -o io_test.out
	- gcc -g -Wall -std=c99 -Wall ./test/checker_test.c ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c ./src/rules.c -o checker_test.out
	- gcc -g -Wall -std=c99 -Wall ./test/hash_test.c ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c ./src/rules.c -o hash_test.out
	- gcc -g -Wall -std=c99 -Wall ./test/words_test.c ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c ./src/rules.c -o words_test.out
	- gcc -g -Wall -std=c99 -Wall ./test/suggestions_test.c ./src/hash.c ./src/words.c ./src/suggestions.c ./src/checker.c ./src/io.c ./src/resources.c ./src/rules.c -o suggestions_test.out
	- ./rules_test.out ; ./io_test.out ; ./checker_test.out ; ./hash_test.out ; ./words_test.out ; ./suggestions_test.out
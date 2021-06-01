compile: ep1.c
	gcc -o ep1 ep1.c

run_test: ep1
	./ep1 digrafo.txt

test: compile run_test

clean: ep1
	rm ep1

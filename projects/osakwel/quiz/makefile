default: prog

prog:
	gcc -Wall -std=c99 -coverage -fpic -lm -o prog compare.c bst.c main.c
	./prog	
clean:
	rm prog

cleanall: 
	rm prog 
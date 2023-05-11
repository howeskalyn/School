make: test.o
	gcc -std=c99 -lcrypt test.o -o make

test.o: test.c
	gcc -std=c99 -c -lcrypt test.c

clean:
	rm -rf *o make

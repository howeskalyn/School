# makefile

comm: communication.o
	mpicc -std=c99 -o communication communication.c


main: matrix.o main.o
	mpicc -std=c99 -o main matrix.o main.o

main.o: main.c
	mpicc -std=c99 -lm -Wall -c main.c 

# results in matrix.o
matrix.o: matrix.c
	mpicc -std=c99 -lm -Wall -c matrix.c 

clean:
	rm -f *.o
	rm -f main



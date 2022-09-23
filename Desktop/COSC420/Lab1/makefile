program: hello.o
	mpicc hello.o -o main
	mpirun -n 5 ./main

hello.o: hello.c
	mpicc -c hello.c

prime: primality.o
	mpicc primality.o -o prime
	# mpirun -n 5 ./prime 20
	# mpirun -n 5 ./prime 19


primality.o: primality.c
	# mpicc -c -lm primality.c
	mpicc -std=c99 -lm primality.c

clean:
	rm -f *.o
	rm -f main


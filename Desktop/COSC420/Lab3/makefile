# makefile

program: main.o
	mpicc -std=c99 main.o -o matrixMain
	mpirun -n 3 ./matrixMain

main.o: main.c matrixFunctions.h
	mpicc -std=c99 -c main.c

time: timing.o
	mpicc -std=c99 timing.o -o time		
	time mpirun -n 5 ./time

timing.o: timing.c matrixFunctions.h
	mpicc -std=c99 -c timing.c

test:
	mpirun -n 10 ./time 7000 7000

# commitTest:
# 	git add timing.txt
# 	git commit -m"send timing"
# 	git push

clean:
	rm *.o
	rm time
	rm matrixMain
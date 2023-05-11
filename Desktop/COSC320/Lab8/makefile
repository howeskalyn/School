CC = g++
Exec = Lab8.exe

Include = include
CFLAGS = -Wall -std=c++11

all: $(Exec)
Lab8.exe: Instantiation.o
		$(CC) -o $(Exec) Instantiation.o #$(Libs)
Instantiation.o: Instantiation.cpp
		$(CC) -c $(CFLAGS) Instantiation.cpp -g
clean:
		rm -f $(Exec) Instantiation.o
rebuild:
		make clean
		make

val:
	make
	valgrind ./Lab8.exe

check:
	make
	valgrind --leak-check=full ./Lab8.exe

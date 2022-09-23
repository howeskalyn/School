CC = g++
Exec = Lab10.exe

Include = include
CFLAGS = -Wall -std=c++11

all: $(Exec)
Lab10.exe: Instantiation.o
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
	valgrind ./Lab10.exe

check:
	make
	valgrind --leak-check=full ./Lab10.exe

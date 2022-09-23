CC = g++
Exec = Lab11.exe

Include = include
CFLAGS = -Wall -std=c++11

all: $(Exec)
Lab11.exe: Instantiation.o
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
	valgrind ./Lab11.exe

check:
	make
	valgrind --leak-check=full ./Lab11.exe

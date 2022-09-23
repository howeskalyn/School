CC = g++
Exec = Project2EC.exe

Include = include
CFLAGS = -Wall -std=c++11

all: $(Exec)
Project2EC.exe: Instantiation.o
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
	valgrind ./Project2EC.exe

check:
	make
	valgrind --leak-check=full ./Project2EC.exe
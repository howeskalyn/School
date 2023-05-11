CC = g++
Exec = Lab6.exe

Include = include
CFLAGS = -Wall -std=c++11

all: $(Exec)
Lab6.exe: Instantiation.o
		$(CC) -o $(Exec) Instantiation.o #$(Libs)
Instantiation.o: Instantiation.cpp
		$(CC) -c $(CFLAGS) Instantiation.cpp -g
clean:
		rm -f $(Exec) Instantiation.o
rebuild:
		make clean
		make
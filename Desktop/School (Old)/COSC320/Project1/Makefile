CC = g++
#Exec = Driver.exe
Exec = Project1.exe

Include = include
CFLAGS = -Wall -std=c++11

all: $(Exec)
#Driver.exe: Instantiation.o
Project1.exe: Instantiation.o
		$(CC) -o $(Exec) Instantiation.o #$(Libs)
Instantiation.o: Instantiation.cpp
		$(CC) -c $(CFLAGS) Instantiation.cpp -g
clean:
		rm -f $(Exec) Instantiation.o
rebuild:
		make clean
		make
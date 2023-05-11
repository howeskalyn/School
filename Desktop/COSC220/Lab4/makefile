all: LinkFile

LinkFile: Node.o LinkedList.o Lab4.o
	g++ Node.o LinkedList.o Lab4.o -o LinkFile

Node.o: Node.cpp
	g++ -c Node.cpp
LinkedList.o: LinkedList.cpp
	g++ -c LinkedList.cpp
Lab4.o: Lab4.cpp
	g++ -c Lab4.cpp

clean:
	rm -rf *o LinkFile

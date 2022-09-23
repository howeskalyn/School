all: LinkFile

LinkFile: linkedList.o linkFun.o
	g++ linkedList.o linkFun.o -o LinkFile

linkedList.o: linkedList.cpp
	g++ -c linkedList.cpp

linkFun.o: linkFun.cpp
	g++ -c linkFun.cpp

clean:
	rm -rf *o LinkFile

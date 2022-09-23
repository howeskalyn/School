// Kalyn Howes
// 4.22.21
// Lab 10
// Graph - header file

#ifndef Graph_H
#define Graph_H

#include <iostream>
#include <map>
#include<vector>
#include <queue>
#include <fstream>

class Graph {

    private:
        enum color_t {
            WHITE,
            GRAY,
            BLACK
        };

        std::map<int, std::vector<int> > vertices; // maps an int to a list (vector) of its neighbors
        int numVertices, numEdges;

        std::vector<color_t> color;
	    std::vector<int> distance;
	    std::vector<int> parent;

        // nodes in the graph will be identified as integers

    public:
        Graph(); // constructor
        ~Graph(); // destructor

        void addVertex(int, bool); // add a vertex to the graph
        void addEdge(int, int, bool); // add an undirected edge to the graph
        void printAdjList(); // prints the adjacency list of each vertex, to show the structure
        void printVertices(); 
        void printBfs(int); // prints the vertices discovered by a BFS, starting at a given vertex

        bool inGraph(int);
        int mapIndex(int);
};

#endif

// Kalyn Howes
// 4.29.21
// Lab 11
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
        const int type; // immutable graph type: 0 for undirected & 1 for directed
    
        std::vector<color_t> color;
	    std::vector<int> distance;
	    std::vector<int> parent;

        // nodes in the graph will be identified as integers

    public:
        std::vector<int> finishTimes; // holds finish times
       std::vector<int> finishTimePals; // holds vertices of the finish times
    
        Graph (int a) : type(a) { numVertices = 0; numEdges = 0;} // constructor

        Graph (const Graph& G) : type(G.type) { numVertices = G.numVertices; numEdges = G.numEdges; 
        vertices = G.vertices; } // copy constructor

        ~Graph(); // destructor
        void reportType(); // reports type of graph

        int getNumV() {return numVertices;}

        void addVertex(int, bool); // add a vertex to the graph
        void addEdge(int, int, bool); // add an undirected edge to the graph
        void printAdjList(); // prints the adjacency list of each vertex, to show the structure
        void printVertices(); 

        void printBFS(int); // prints the vertices discovered by a BFS, starting at a given vertex
        bool DFS(bool, bool);
        bool DFSvisit(int, std::map<int, int>&, std::map<int, int>&, std::map<int, color_t>&, std::map<int, int>&, bool, bool);

        bool isDAG();
        void topologicalSort();
        void reportSCC(Graph);
        void SCCDFS(bool);

        bool inGraph(int);
        int mapIndex(int);  // careful with the "mapIndex" function:
                            // instead, make d,p,c maps that just directly use the int of the vertex label to 
                            // index into the map. (if you want to start on vertex 5, you'd do color[5] = WHITE; and d[5] = 0; p[5] = -1)
};

#endif

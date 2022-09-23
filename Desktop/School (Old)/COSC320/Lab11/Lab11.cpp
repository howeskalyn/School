// Kalyn Howes
// 4.29.21
// Lab 11
// Graphs: demonstrate the correctness of each of the Graph functions
// reads the graph adjacency list from a file for testing purposes - the format expected in documented (README)

#include "Graph.h"
#include <iostream>
#include <cstdlib> // timing
#include <ctime> // timing
#include <chrono> // timing
#include <fstream> // files
#include <stdlib.h> // rand
#include <time.h> // reset for rand
#include <fstream> // files
#include <string>

// colored output
#define RESET "\033[0m"
#define RED "\033[31m"

using namespace std;

int main() {
    srand(time(NULL));
    /*
    // file prep:
    ifstream inputFile;
    string file = "";
    cout << "Enter the name of the file you would like to open: ";
    cin >> file;

    inputFile.open(file);
    if (inputFile)
        cout << "\nFile is open." << endl;
    else
        cout << RED << "\nError opening file." << RESET << endl;

    // bringing in info from file
    int type = 0;
    inputFile >> type; // first number in file determines graph type
    Graph G(type); // create graph - 0 is undirected & 1 is directed
    G.reportType(); // test graph type

    string line = "", divider = "";
    inputFile >> divider; // move past divider
    int v = 0, v2 = 0;
    // adding vertices
    cout << "\n--- Adding Vertices --- " << endl;
    for (int i = 0; i < 6; i++) { // find divider between vertices and edges
        inputFile >> v;
        G.addVertex(v, true);
    }
    inputFile >> divider; // move past next divider
    // adding edges
    cout << "\n--- Adding Edges --- " << endl;
    while (inputFile) {
        inputFile >> v;
        inputFile >> v2;
        G.addEdge(v, v2, true);
    }

    cout << "\n--- Printing the adjacency list ---" << endl;
    G.printAdjList();

    cout << "\n--- Running DFS ---" << endl;
    G.DFS(false, true); // no dag, but print

    cout << "\nIs the graph a DAG?" << endl;
    bool DAG = G.isDAG();
    
    if (DAG == true)
        cout << YELLOW << "The graph is a DAG - it is directed & acyclic." << RESET << std::endl;
    else 
        cout << RED << "The graph is NOT a DAG " << RESET << " - it is either undirected or has cycles." << std::endl;

    cout << "\n--- Topological Sort ---" << endl;
    G.topologicalSort();

    cout << "\n--- Reporting SCC's --- " << endl;
    G.reportSCC(G);

*/

    Graph G(0); // undirected
    for (int i = 0; i < 8; i++) 
        G.addVertex(i, true);
    
    G.addEdge(0, 4, true);
    G.addEdge(0, 3, true);
    G.addEdge(0, 2, true);
    G.addEdge(2, 1, true);
    G.addEdge(1, 6, true);
    G.addEdge(4, 6, true);
    G.addEdge(4, 7, true);
    G.addEdge(3, 5, true);
    G.addEdge(3, 7, true);

    //cout << "\n---BFS---" << endl;
    //G.printBFS(0);
    cout << "\n---DFS---" << endl;
    G.DFS(false, true);
    








    return 0;
}
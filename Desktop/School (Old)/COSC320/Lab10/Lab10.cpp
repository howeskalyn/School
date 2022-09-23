// Kalyn Howes
// 4.22.21
// Lab 10
// Graphs: demonstrate the correctness of each of the Graph functions

#include "Graph.h"
#include <iostream>
#include <cstdlib> // timing
#include <ctime> // timing
#include <chrono> // timing
#include <fstream> // files
#include <stdlib.h> // rand
#include <time.h> // reset for rand
#include <fstream>

// colored output
#define RESET "\033[0m"
#define RED "\033[31m"

using namespace std;

int main() {
    srand(time(NULL));

    // file prep:
    ofstream outputFile;
    outputFile.open("timing.txt");

    if (outputFile)
        cout << "\nFile is open." << endl;
    else
        cout << RED << "\nError opening file." << RESET << endl;


    Graph G; // create graph

    // EMPTY TESTING:
    cout << "\n-- Empty graph tests! --" << endl;
    G.printAdjList();
    G.printBfs(0);
    
    // TESTING:
    cout << "\n-- Adding vertices starts now --\n" << endl;
    auto start = std::chrono::system_clock::now();

    int startVertex = 1, vertices = 10;
    G.addVertex(startVertex, true); // manually insert 1 starting vertex
    G.addVertex(startVertex + 1, true); // manually insert 2nd starting vertex to ensure an edge later on
    // fill with random vertices between 1 & 15
    for (int i = startVertex; i < vertices; i++) {
        G.addVertex(rand() % 15 + 1, true);
    }
   
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    outputFile << "Adding " << vertices << " vertices took: " << elapsed_seconds.count() << endl;

    // fill with edges
    cout << "\n-- Adding edges starts now -- \n" << endl;
    start = std::chrono::system_clock::now();

    G.addEdge(startVertex, 2, true); // start edge to ensure there is one
    int edges = 10;
    for (int i = startVertex; i < edges; i++)
        G.addEdge(rand() % 15 + 1, rand() % 15 + 1, true);

    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    outputFile << "Adding " << edges << " edges took: " << elapsed_seconds.count() << endl;

    /* These cases end up being tested anyways during the run above.
    cout << "\nTesting adding a vertex that is already in the graph: " << endl;
    G.addVertex(startVertex, true);
    cout << "\nTesting adding an edge that does not have both vertices: " << endl;
    G.addEdge(startVertex, 20, true);
    */

    cout << "\nPrinting the adjacency list: " << endl;
    G.printAdjList();

    // timing BFS
    start = std::chrono::system_clock::now();

    cout << "\nPrinting BFS: " << endl;
    G.printBfs(startVertex);

    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    outputFile << "BFS took: " << elapsed_seconds.count() << endl;
   
    return 0;
}
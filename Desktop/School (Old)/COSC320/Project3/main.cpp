/*
Kayln Howes & Chloe VanCory 
Project 3 
Graph Coloring and Chromatic Numbers 

GOALS:
1. be exposed to the breadth of problem domains in graph theory and computer science
2. develop the skills needed to research a problem, understand its motivations and potential solutions, 
3. be exposed to the genesis of a problem and its historical solutions,
4. practice communicating complicated material in computer science and applied mathematics.

*/


#include <iostream>
#include <stdio.h>
#include <chrono>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <unistd.h>
#include <fstream>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h> // defines s_iread and s_iwrite
#include <string> 

#include "Graph.h"

using namespace std;

int main(){

    srand(time(NULL));
    // file prep:
    ofstream outputFile;
    outputFile.open("timing.txt");

    if (outputFile)
        cout << "\nFile is open." << endl;
    else
        cout << RED << "\nError opening file." << RESET << endl;

    // ----------GREEDY COLORING ALG----------------
    // EXAMPLE 1
    Graph  <string> A;
    A.addVertex("MD");
    A.addVertex("DE");
    A.addVertex("PA");
    A.addVertex("NJ");
    A.addVertex("WV");
    A.addVertex("OH");
    A.addVertex("VA");

    A.addEdge("MD", "DE");
    A.addEdge("MD", "WV");
    A.addEdge("MD", "PA");
    A.addEdge("DE", "NJ");
    A.addEdge("PA", "NJ");
    A.addEdge("PA", "OH");
    A.addEdge("PA", "WV");
    A.addEdge("VA", "WV");
    A.print();

    auto start = std::chrono::system_clock::now();
    A.greedyColor();
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    outputFile << "Greedy coloring of state example (7 vertices) took: " << elapsed_seconds.count() << endl;

    // EXAMPLE 3:
    Graph <string> C;
    C.addVertex("COSC117");
    C.addVertex("MATH210");
    C.addVertex("BIO101");
    C.addVertex("ENG101");
    C.addVertex("HIST103");
    C.addVertex("GEO104");
    C.addVertex("CADR201");
    C.addEdge("BIO101", "MATH210");
    C.addEdge("ENG101", "HIST103");
    C.addEdge("HIST103", "GEO104");
    C.addEdge("GEO104", "COSC117");
    C.addEdge("COSC117", "MATH210");
    C.print();

    start = std::chrono::system_clock::now();
    C.greedyColor();
    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    outputFile << "Greedy coloring of class example (7 vertices) took: " << elapsed_seconds.count() << endl;
    

    // RANDOMS
    // Graph <int> G;
    // int numVertices = 12, numEdges = 12;
    // // fill with vertices
    // for (int i = 0; i < numVertices; i++) {
    //     G.addVertex(i);
    // }
    // // fill with edges
    // for (int i = 0; i < numEdges; i++) {
    //     G.addEdge(i, rand() % 50 + 1); // edge w i and random num
    // }

    // start = std::chrono::system_clock::now();
    // G.greedyColor();
    // end = chrono::system_clock::now();
    // elapsed_seconds = end - start;
    // outputFile << "Greedy coloring of random example (approx " << numVertices << " vertices & " << numEdges << " edges) took: " << elapsed_seconds.count() << endl;
    
    // ----------CHROMATIC NUMBER ALG----------------
    cout << "\n\n--------Chromatic Number Timing--------" << endl;
    start = std::chrono::system_clock::now();
    A.color(false);
    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    outputFile << "Chromatic number of state example (7 vertices) took: " << elapsed_seconds.count() << endl;

    start = std::chrono::system_clock::now();
    C.color(false);
    end = chrono::system_clock::now();
    elapsed_seconds = end - start;
    outputFile << "Chromatic number of class example (7 vertices) took: " << elapsed_seconds.count() << endl;

    // outputFile << "Chromatic timing starting now." << endl;
    // auto start = std::chrono::system_clock::now();
    // G.color(false);
    // auto end = chrono::system_clock::now();
    // chrono::duration<double> elapsed_seconds = end - start;
    // outputFile << "Chromatic color of random example (approx " << numVertices << " vertices & " << numEdges << " edges) took: " << elapsed_seconds.count() << endl;
    
    return 0;

}
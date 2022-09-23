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

    // Graph  <int> G;
    // G.addVertex(1);
    // G.addVertex(2);
    // G.addVertex(3);
    // G.addVertex(4);

    // G.addEdge(1,2);
    // G.addEdge(3,1);
    // G.addEdge(3,4);

    // // G.print();

    // G.color();

    


    // Graph  <string> A;
    // A.addVertex("MD");
    // A.addVertex("MD");
    // A.addVertex("DE");
    // A.addVertex("PA");
    // A.addVertex("NJ");
    // A.addVertex("WV");
    // A.addVertex("OH");
    // A.addVertex("VA");

    // A.addEdge("MD", "DE");
    // A.addEdge("MD", "WV");
    // A.addEdge("MD", "PA");
    // A.addEdge("DE", "NJ");
    // A.addEdge("PA", "NJ");
    // A.addEdge("PA", "OH");
    // A.addEdge("PA", "WV");
    // A.addEdge("VA", "WV");


    // A.print();
    // A.greedyColor();
    // A.findChromatic();



    // example from chromatic number algorithm
    // Graph <int > B;
    // B.addVertex(1);
    // B.addVertex(2);
    // B.addVertex(3);
    // B.addVertex(4);

    // // B.addEdge(1,2);
    // // B.addEdge(1,4);
    // // B.addEdge(2,4);
    // // B.addEdge(4,3);

    // B.print();
    // // B.greedyColor();

    // B.color();


// example from chromatic number algorithm
    Graph <string > C;
    C.addVertex("A");
    C.addVertex("B");
    C.addVertex("C");
    C.addVertex("D");

    C.addEdge("A","B");
    C.addEdge("A","C");
    C.addEdge("A","D");
    C.addEdge("B","C");
    
    // C.print();
    // C.greedyColor();

    C.color();

    

}
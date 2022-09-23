
#ifndef GRAPH_H 
#define GRAPH_H 

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stdio.h>
#include <unistd.h>
#include <list>
#include <string>
#include <stdlib.h>  
#include <unordered_map>
#include <math.h>
#include <algorithm> 


using namespace std;



// used in findDegree function to return data to the smallMIS function
template <class T >
struct degreePair{
    T vertexValue;
    int degree;

};

template <class T >
class Graph{
    private:
        /* will map an int to a list of its neighbors */
        map <T, vector<T> > vertices;
        void greedyColor(T);
        // void printColor(int index);

    public:
        Graph();
        void addVertex(T vertex);
        void addEdge(T , T);
        void greedyColor(); // greedy algorithm to color graph 

        map<string, Graph<T>>  genSubgraphs(); // 
        Graph<T> makeSubgraph(Graph &, bool);

        void genSets(int n, vector< vector<T> > & );
        vector< vector<T> > checkIndependentSets(Graph , vector< vector<T> >);
        bool areConnected(Graph subGraph, T node1 , T node2);
        vector<T> get_verticesSet(Graph current);

        string get_binary(vector<T> current); // takes the verticies and converts it to bin 
        string binValue(int);

        //helper func for Lawler alg
        int degree(Graph , T ); // returns the degree of a graph and vertex 
        // void populateDegrees(Graph ,  map< T  , int> &); // calls degree on all verticies in graph 
        degreePair<T> findDegree(Graph);
        // T returnNeighbor(Graph , T); /// maybe do no thave to use 

        vector <T> symDiff( vector <T> , vector<T> );
        vector <T> setUnion( vector <T> , vector<T> );

        // Eppstein Algorithms 
        //int chromaticNumber();
        void  prepMIS(Graph , vector <vector<T>>& );
        void  smallMIS(Graph, vector <vector<T> > &,  vector <T> , vector<T> , int );
        void color(bool);

        void print();

        // makeSubsetgraph(Graph original , graph subset )


};




#endif
#include "Graph.cpp"




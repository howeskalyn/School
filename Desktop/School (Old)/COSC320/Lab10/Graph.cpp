// Kalyn Howes
// 4.22.21
// Lab 10
// Graph - implementation file

#include "Graph.h"
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <fstream>

// colored output
#define RESET "\033[0m"
#define RED "\033[31m"

// constructor
Graph::Graph() {
    numVertices = 0;
    numEdges = 0;
}

Graph::~Graph() {

}

// adds a vertex to the graph
// checks to make sure a duplicate node isn’t entered, and then add it to the
//      map, vertices, with an empty vector of neighbors
// there is a boolean input that determines whether or not to print each step of the process
void Graph::addVertex(int v, bool print) {
    numVertices++;

    // check if vertex is already in graph
    for (auto it = vertices.begin(); it != vertices.end(); it++) {

        // if vertex is found
        if (it->first == v) {
			if (print)
            	std::cout << RED << "Vertex " << v << " is already in the graph." << RESET << std::endl;
            return; // leave
        }
    }

    // if it is not found:
	if (print)
    	std::cout << "Vertex " << v << " is being added to the graph." << std::endl;

    // insert the given value, with no neighbors (empty vector)
    vertices.emplace(v, std::vector<int>());

}

// adds an undirected edge to the graph
// adds an edge between two vertices (if it doesn’t already exist), and since this
//      is an undirected graph, will need to add it to both adjacency lists
// there is a boolean input that determines whether or not to print each step of the process
void Graph::addEdge(int v, int v2, bool print) {
	numEdges++;

	bool Visin = false, V2isin = false;
	// check if vertices are in graph
    for (auto it = vertices.begin(); it != vertices.end(); it++) {
        // if vertex is found
        if (it->first == v)
            Visin = true;
		if (it->first == v2)
			V2isin = true;
    }

	if (numVertices > 0 && Visin && V2isin) { // if there are vertices & they are in the graph
		bool path1 = false;

		if (print)
			std::cout << "Adding edge " << v << "--" << v2 << " to the graph." << std::endl;

		// go through mapping 
		for (auto it = vertices.begin(); it != vertices.end(); it++) {

			// if first given vertex is found
			if (it->first == v) {

				// search through its neighbors
				for (int i = 0; i < it->second.size(); i++) {

					// if second given vertex is found
					if (it->second[i] == v2)
						path1 = true;
				}

				// if not path 1, add second given vertex
				if (!path1) 
					it->second.push_back(v2); 

			}
		}
	} else {
			if (!Visin && print)
				std::cout << RED << v << " is NOT in the graph." << RESET << std::endl;
			if (!V2isin && print)
				std::cout << RED << v2 << " is NOT in the graph." << RESET << std::endl;
			std::cout << RED << "Edge " << v << "--" << v2 << " could not be added." << RESET << std::endl;
	}
}

// prints the adjacency list of each vertex, to show the structure
void Graph::printAdjList() {

    if (numVertices > 0) {
		std::queue<int> Q = std::queue<int>(); 	// create an empty queue

		// for all vertices
		for (auto it = vertices.begin(); it != vertices.end(); it++) {

			// add it to the queue
			Q.push(it->first);
			int prev = Q.front();
			std::cout << "Nodes neighboring " << it->first << ": " << std::endl;
			std::cout << "{ ";
			for (int v : vertices[prev])
				std::cout << v << ", ";

			std::cout << "}" << std::endl;
			Q.pop(); // iterator moves forward
		}
	}
	else
		std::cout << RED << "\nThere are NO vertices in this graph." << RESET << std::endl;  
}

// prints just the vertices of the graph
void Graph::printVertices() {
	if (numVertices > 0) {
		int i = 0;
		for (std::map<int, std::vector<int> >::iterator it = vertices.begin(); it != vertices.end(); it++) {
			std::cout << "Vertex #" << i + 1 << ": " << it->first << std::endl;
			i++;
		}
	}
	else
		std::cout << RED << "There are NO vertices in this graph." << RESET << std::endl;
}

// prints the vertices discovered by a BFS, starting at a given vertex
// executes a version of the BFS algorithm
// queue Q holds all gray vertices (vertices we have seen but are still not done with)
// (runs in O(|V| + |E|) time)
void Graph::printBfs(int s) {

    if (numVertices == 0)
		std::cout << RED << "The graph is empty." << RESET << std::endl;
	else {
		std::vector<int> visited; // vector of visited nodes (gray)
		std::map<int, std::vector<int> >::iterator it = vertices.find(s); // index of where start is at

		// if start is in the graph
		if (it != vertices.end()) {

			// initialize the starting node
			std::cout << "Number of nodes in this graph: " << numVertices << std::endl;
			
			// initialize vectors
			std::vector<int> d, p; // distances, parents
			std::vector<color_t> c; // colors
			for (int i = 0; i < numVertices; i++) {
				d.push_back(-1);
				p.push_back(-1);
				c.push_back(WHITE);
			}

			// override old data
			distance = d;
			parent = p;
			color = c;

			std::queue<int> neighbors; // define a queue called neighbors
			
			int k = mapIndex(s); // find corresponding map index to the start
			color[k] = GRAY; // start visited color gray
			distance[k] = 0; // 0 distance to itself
			neighbors.push(s); // add this node to the queue
		
			// while the queue is not empty
			while (!neighbors.empty()) {
				
				// remove the element in the queue currently
				int dequeuedVal = neighbors.front(); //  holds the value dequeued
				std::cout << "Dequeuing " << dequeuedVal << std::endl;
				neighbors.pop(); // remove dequeuedVal

				int h = mapIndex(dequeuedVal); // index of the current vertex

				// for all the vertices connected to the one we are at (wasinqueue)
				for (int v : vertices[dequeuedVal]) {
					//std::cout << "v: " << v << std::endl; // now find what i corresponds to that v
					int i = mapIndex(v); // index of the vertex we are interested in
					
					// not visited node
					if (color[i] == WHITE) {
						color[i] = GRAY; // visited i
						distance[i] = distance[h] + 1; // distance to i is distance to dequeuedVal+1
						parent[i] = dequeuedVal; // v came from dequeuedVal

						neighbors.push(v); // add v to the queue
					}
				}
				color[dequeuedVal] = BLACK; //done visiting wasinqueue enitrely
			}

			// reset colors
			for (int i = 0; i < numVertices; i++)
				color[i] = WHITE;

			neighbors.push(s);

            // while the queue is not empty
			while (!neighbors.empty()) {
				// remove the element in the queue currently
				int dequeuedVal = neighbors.front(); // dequeuedVal holds the value dequeued
				neighbors.pop(); // remove dequeuedVal

				int h = mapIndex(dequeuedVal); // index of the current vertex of question

				// report the distance from start
				std::cout << "Distance from " << s << " to " << dequeuedVal << ": " << distance[h] << std::endl;

				// for all the vertices connected to the one we are at (dequeuedVal)
				for (int v : vertices[dequeuedVal]) {
					// now find what i corresponds to that v
					int i = mapIndex(v); // index of the vertex we are interested in

					// not visited node
					if (color[i] == WHITE) {
						color[i] = GRAY; // visited i
						neighbors.push(v); // add v to the queue
					}
				}
			}
		}
	}
}

// determines if the given vertex is in the graph
bool Graph::inGraph(int v) {
	bool in = false;
	if (numVertices > 0) {
		for (std::map<int, std::vector<int> >::iterator it = vertices.begin(); it != vertices.end(); it++)
			if (it->first == v)
				in = true;
	}
	else
		std::cout << RED << "There are NO vertices in this graph." << RESET << std::endl;
	return in;
}

// returns the corresponding map index to the given vertex, v
int Graph::mapIndex(int v) {
	int j = 0;
	if (inGraph(v)) {
		for (std::map<int, std::vector<int> >::iterator it = vertices.begin(); it != vertices.end(); it++) {
			if (it->first == v)
				return j;
			else
				j++;
		}
	}
	return -1;
}
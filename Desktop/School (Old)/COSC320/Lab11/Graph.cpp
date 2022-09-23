// Kalyn Howes
// 4.29.21
// Lab 11
// Graph - implementation file

#include "Graph.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <stack>
#include <fstream>

// colored output
#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m" // undirected
#define YELLOW "\033[33m" // directed
#define GREEN "\033[32m"

/* constructor: defined in header because of constant variable, "type"
// directed or undirected - specified as a parameter & is constant
Graph::Graph(int t) {
    numVertices = 0;
    numEdges = 0;
	type = t;
}*/ 

// destructor
Graph::~Graph() {

}

// reports type pf graph - undirected or directed
void Graph::reportType() {
	if (type == 0)
		std::cout << "The graph is " << BLUE << "undirected." << RESET << std::endl;
	else if (type == 1)
		std::cout << "The graph is " << YELLOW << "directed." << RESET << std::endl;
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
// adds an edge between two vertices (if it doesn’t already exist), & takes into
// 		account whether the graph needs to be directed or undirected
// 		(specifically, if it is undirected, both directions of the edge should be added!)
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
			std::cout << "Adding edge " << v << "--" << v2 << " to the graph." << RESET << std::endl;

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

		if (type == 0) { // if undirected, both edges should be added
			if (print) {
				std::cout << "The graph is " << BLUE << "undirected " << RESET "- ";
				std::cout << "adding edge " << v2 << "--" << v << " to the graph as well." << std::endl;
			}

			for (auto it = vertices.begin(); it != vertices.end(); it++) {

				// if second given vertex is found
				if (it->first == v2) {

					// search through its neighbors
					for (int i = 0; i < it->second.size(); i++) {

						// if first given vertex is found
						if (it->second[i] == v)
								path1 = true;
					}

					// if not path 1, add first given vertex
					if (!path1) 
						it->second.push_back(v); 

				}
			} // end for
		} // end if undirected

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
void Graph::printBFS(int s) {

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

// prints the vertices discovered by a DFS
// takes in bool to decide whether or not to see if the graph is a DAG
// takes in bool to print finish times/not
int timeDFS = 0; // global time variable
bool Graph::DFS(bool findDAG, bool print) {
	finishTimes.clear(); // reset finishTimes each call
	bool ret = true;

	if (numVertices == 0)
		std::cout << RED << "The graph is empty." << RESET << std::endl;
	else {
		std::map<int, color_t> color;
		std::map<int, int> parent;
		std::map<int, int> discover;
		std::map<int, int> finish;

		// for all vertices
		for (auto it = vertices.begin(); it != vertices.end(); it++) {
			color.emplace(it->first, WHITE);
			parent.emplace(it->first, -1);
			discover.emplace(it->first, -1);
			finish.emplace(it->first, -1);
		}

		timeDFS = 0;

    	for (auto it = vertices.begin(); it != vertices.end(); it++) {
			if (color.find(it->first)->second == WHITE)
				ret = DFSvisit(it->first, discover, finish, color, parent, findDAG, print);
			if (findDAG) {
				if (ret == false)
					return false;
			}
		}
	}
	return ret;
}

// DFS helper method
bool Graph::DFSvisit(int u, std::map<int, int> &discover, std::map<int, int> &finish, 
std::map<int, color_t> &color, std::map<int, int> &parent, bool findDAG, bool print)  {
	bool ret = true; // claiming it is acyclic until one is found

	timeDFS++;
	discover[u] = timeDFS;
	color[u] = GRAY;

	// for all vertices
	for (int i: vertices[u]) {
		if (color[i] == WHITE) {
			parent[u] = i;
			DFSvisit(i, discover, finish, color, parent, findDAG, print);
		}
		if (findDAG) {
			if (color[i] == GRAY)
				return false;
		}
	}

	color[u] = BLACK;
	timeDFS++;
	finish[u] = timeDFS; // this is doing nothing....
	finishTimes.push_back(timeDFS);
	finishTimePals.push_back(u);

	if (print)
		std::cout << "Vertex " << u << " finish time: " << timeDFS << std::endl;

	return ret;
}

// reports whether the graph is both directed and acyclic (contains no cycles) - DAG
// a modified DFS to determine whether it is acyclic: during the search, if any gray nodes (other
// 		than the “parent”) are encountered during a single DFS-visit, then the algorithm has found a cycle
bool Graph::isDAG() {
	bool ret = true; // no cycles detected yet

	if (type == 0) // if undirected it is false immediately
		return false;

	else if (type == 1) { // if directed
		// DFS but during search if any gray nodes are found, it has a cycle - true for finding DAG, false for no printing
		ret = DFS(true, false);
	}

	return ret;
}

// topological sort algorithm & reports a valid topological ordering if one exists (the graph must be a DAG)
// determine a valid topological sort by first performing DFS, then ordering the vertices by decreasing finish times 
// 		if there is no such ordering (because it is not a DAG), an error should be reported.
void Graph::topologicalSort() {

	if (isDAG()) { // graph must be a DAG
		std::cout << YELLOW << "The graph is directed and acyclic (DAG) - topological sort starts now." << RESET << std::endl;
		DFS(false, false); // no DAG & no print

		// order finish times by descreasing order - if this doesnt exist - error
		sort(finishTimes.begin(), finishTimes.end(), std::greater<int>());

		// print sorted finishTimes
		for (auto i: finishTimes)
      		std::cout << i << " " << std::endl;

	} else 
		std::cout << RED << "The graph is NOT a DAG - topological sort cannot occur." << RESET << std::endl;

}

// reports each fully connected component of the graph using DFS
// first DFS the graph to compute the finish times, then reverse all the edges 
// 		(using a copy of the graph with a copy constructor) and perform DFS on the
// 		reversed graph (aka the transpose graph) where the nodes are visited in order of descending finish time
// each DFS tree in the resulting forest computed by the second DFS contains exactly one fully connected component of the graph
// (the graph does not have to be acyclic for this procedure)
void Graph::reportSCC(Graph G) {

	std::cout << GREEN << "\n-First DFS Run-" << RESET << std::endl;
	DFS(false, true); // no DAG check & no print

	std::cout << GREEN << "\n-Reversing Edges- " << RESET << std::endl;
	Graph G2(G); // create new graph as copy of the original -- all vertices are already in it
	std::queue<int> Q = std::queue<int>(); 	// create an empty queue

	// reverse edges:
	for (auto it = vertices.begin(); it != vertices.end(); it++) {
		std::vector<int> neighbors; // holds neighbors

		//std::cout << "Current vertex: " << it->first << std::endl;

		// find neighbors of current vertex
		for (int v : vertices[it->first])
			neighbors.push_back(v);

		//std::cout << "Neighbors: " << std::endl;
		//for (int i = 0; i < neighbors.size(); i++)
			//std::cout << neighbors[i] << " ";

		// add new edges in reversed order
		//std::cout << "\nReversing edges: " << std::endl;
		for (int i = 0; i < neighbors.size(); i++) {
			G.addEdge(neighbors[i], it->first, true);
		}
	}

	// testing finishTimePals 
	std::cout << GREEN << "\n -Finish times & their vertices- " << RESET << std::endl;
	for (int i = 0; i < finishTimes.size(); i++) {
		std::cout << "Vertex: " << finishTimePals[i] << " has time: " << finishTimes[i] << std::endl;
	}

	G2.finishTimes = finishTimes;
	G2.finishTimePals = finishTimePals;

	// bubble sort finishTimes & finishTimePals the same way by descending order
	for (int i = 0; i < finishTimes.size() - 1; i++) {
		for (int j = 0; j < finishTimes.size() - 1 - i; j++) {
			if (finishTimes[j] < finishTimes[j + 1]) {
				// swap finishTimes
				int temp = finishTimes[j];
				finishTimes[j] = finishTimes[j + 1];
				finishTimes[j + 1] = temp;
				// swap finishTimePals
				temp = finishTimePals[j];
				finishTimePals[j] = finishTimePals[j + 1];
				finishTimePals[j + 1] = temp;
			}
		}
	}

	std::cout << GREEN << "\n-Checking Sort-" << RESET << std::endl;
	for (int i = 0; i < finishTimes.size(); i++)
		std::cout << "Vertex: " << finishTimePals[i] << " has time: " << finishTimes[i] << std::endl;

	// DFS the revsersed graph, but in the main loop, consider the vertices in order of decreasing finish times
	std::cout << GREEN << "\n-Second DFS Run-" << RESET << std::endl;
	G2.SCCDFS(true); // true for print

	// each DFS tree contains 1 SCC
	// output the vertices of each tree as a separate SCC
}

// DFS for reporting SCCs - goes through vertices in decreasing finish times
void Graph::SCCDFS(bool print) {

	if (numVertices == 0)
		std::cout << RED << "The graph is empty." << RESET << std::endl;
	else {
		std::map<int, color_t> color;
		std::map<int, int> parent;
		std::map<int, int> discover;
		std::map<int, int> finish;

		int size = finishTimes.size();

		// for all vertices
		for (int i = 0; i < size; i++) {
			color.emplace(finishTimePals[i], WHITE);
			parent.emplace(finishTimePals[i], -1);
			discover.emplace(finishTimePals[i], -1);
			finish.emplace(finishTimePals[i], -1);
		}

		timeDFS = 0;

    	for (int i = 0; i < size; i++) {
			if (color[finishTimePals[i]] == WHITE)
				DFSvisit(finishTimePals[i], discover, finish, color, parent, false, print);
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
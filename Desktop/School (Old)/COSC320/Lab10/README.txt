Kalyn Howes
4.22.21
Lab 10 - README

(a) 
	In the Graph.h header file, I included here is a map of integers to a vector of integers that keeps track of the integers neighboring vertices. I created a color_t type with colors White, Gray, and Black for the purposes of the Breadth-First-Search algorithm. Also for the BFS, I created 3 more maps to hold the colors, distances, and parent nodes for the vertices. I also decided to keep track of the number of vertices (nodes) and edges here as well. 
	In the Graph.cpp file, the constructor simply sets the number of vertices and edges to 0. The function addVertex first checks for duplicates and then proceeds to add the vertex. The function addEdge first checks to make sure the two input vertices are in the graph, and then adds the edge. I have included a function to print the adjacency list for easy review, and also a print for just the vertices for testing reasons. The printBFS conducts the Breadth-First-Search algorithm and prints information regarding the input index. In my runs, I have it taking in the startVertex value (1) so the printBFS is only reporting the distances to that startVertex (1).
	Some helpers I have included are inGraph and mapIndex. inGraph determines if the given vertex is in the graph and mapIndex returns the corresponding map index number to the given vertex.

	The main first shows what happens if the user tries to print an empty graph. Then a start vertex value (which is currently set at 1) is added along with another vertex value to ensure we have an edge later on. The graph is then filled with random vertices depending on the size of "vertices". For the edges, I created the first edge manually and then once again used the random number generator. Then the adjacency list and the BFS are printed. The main sends timing to the "timing.txt" file.

(b)
	The theoretical time complexity of addVertex is O(|v|) since it checks if the given vertex is already in the graph first. Otherwise this function is constant. The addEdge function also checks to make sure each vertex is in the graph before starting, but it then goes through the map "vertices" AND each of its neighbors. The BFS algorithm theoretically takes O(|V| + |E|) time. 
	I included some timing in the file "Graph Timing Sheet" which shows test of the above three functions on differing numbers of vertices and edges. In general, the trends increase as the number of vertices & edges increase, as expected. The addEdge took the longer than addVertex which makes sense based on what I said above. Overall each function is very fast.


(c)
	I feel like I am missing something but I can't quite figure out what. Other than that I feel my main could be more organized and take in some user input or something. 
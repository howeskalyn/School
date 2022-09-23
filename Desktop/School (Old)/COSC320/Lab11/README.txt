Kalyn Howes
4.29.21
Lab 11 - README.txt

(a)
	The main asks the user for a file input of the graphs adjacency list. This file must include one integer on the first line (either 0 or 1) to determine the type of the graph. Then, the next line of the file must be a "-" to divide the type from the vertices. The next six lines are the vertices that will be added to the graph. This program only allows 6 vertices to be added. The next line has another "-" divider and then each line after includes the edges in the form "vertex1 vertex2". There can be as many edges as you want.
	Once the vertices and edges are added, the adjacency list is printed, a run of DFS is printed, the program checks if it is a DAG, a topological sort is done, and the SCCs are found. The SCC function is kind of a mess, so I'll explain. reportSCC prints the first run of the DFS normal, then the edges are reversed and printed as they are added. The finishTimePals vector holds the vertices that correspond to the finishTimes from the 1st DFS. Even though this is a perfect place to use a map, I couldn't get it to work so I just have 2 vectors. The finish times and their vertices are printed again for clarification. Next, I used a typical (and slow) bubble sort to order the finish times (and their pals) by descending order, and they are printed again to check the sort. Finally, DFS is run again, but I call SCCDFS since the DFS needs to be done in descending order.
	

(b)
	DFS has a runtime of theta(|V| + |E|), which means it is anywhere from n to n^2, when |V| = n. The function to determine if the graph is a DAG is constant itself, but runs DFS, making it have the same runtime as DFS. The same goes for the topological sort function. The reportSCC function has to go through each edge (|E|), bubble sort (n^2), and DFS 2 times. 
	

(c)
	I could have been more efficient with the way I stored different variables, and picked a different sort for the finish times so it was quicker.



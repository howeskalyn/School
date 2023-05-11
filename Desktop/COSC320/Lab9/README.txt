Kalyn Howes
4.15.21
Lab 9 - README

(a)

	After many issues with pointers and memory leaks, my code is safe! One of the biggest problems was bringing in an RBTree as a parameter into an RBTree class function. This caused the tree to be passed in as copy, which meant the tree got destructed when the function ended. Obviously this is not what I wanted to happen. Along with that error, I was creating TreeNode structs with the 'new' command which means the constructor was called after the memory was allocated, when it was unnecessary. 
	Other than memory issues, the lab was pretty easy to construct overall. Most of the main code was taken from my Lab 8 main since they needed to do the same things. Of course there were some major differences between the BST and RBT functions since color, rotations, and fix-ups come into play. Also, the new idea of having a 'nil' created some issues as well. One of my early realizations was that when I was finding the minimum, maximum, successor, and more, the nil nodes had to be ignored or else they were included in finding these.m

(b)
	  The theoretical time complexity of the search algorithm is O(h), where h is the height of the tree. The insert, delete, and successor functions also all have complexities of O(h). If there are n nodes in the tree, the height is: logn <= h <= n. This means each of these functions have time complexities of O(logn) in certain cases. The transplant algorithm has a constant time complexity for all cases.

(c) 
	 There is a file called 'timing.txt' which includes the output of the timing runs in the main. I timed the insert by counting the number of seconds it took to insert n nodes into the tree. The search is timed by searching for 1 node in a tree of size n. The remove is also timed this way, by removing 1 node in a tree of size n. The graph of these times is included in the .docx file included in the zip. Looking at the times, it is odd that the search showed up as taking 0 seconds several times... maybe this is because it went so quickly? The insert data made the most sense, as the number of nodes increased, so did the time taken. The remove data was also very quick, as the time taken was so close to 0 it looks like 0 on the graph. Also, the insert function is run n times, however the search and remove only need to traverse n times and are only run once. This is obviously a big difference.

(d) 
	The print method I have included is very basic and does not show the levels of the tree. This should be improved to better display the trees parts, however the tree is colored at least.
	There are multiple instances in the main where the user-facing methods are returning and taking in TreeNode objects. This is an issue because the user could badly alter the structure of the tree. 





Kalyn Howes
4.1.21
Lab 8
README

(a)
        Creating a BinaryTree class allows for all of the functions invloved to be in one, easy to reach place. This class includes 
    functions such as insert a node, search for a node, remove a node, and other helper functions. Within this class there is a struct
    for a TreeNode. Each TreeNode has a integer key, a pointer to its left child, a pointer to its right child, and a pointer to its parent node.
    Also within the BinaryTree class, there is a TreeNode already created that holds the root of the tree.

        Since several functions in the BinaryTree class take in TreeNodes as parameters, I had to create helper functions to be used in the main.
    'For example, removeMain' and 'successorMain' allow the user to send in an integer in the main rather than a whole TreeNode. Without this, 
    the user would need to create an entire TreeNode when they really only need to focus on the key (value) of the node. These functions create 
    a TreeNode based on the users integer input and send that node to the actual function.


(b) 
        The theoretical time complexity of the search algorithm is O(h), where h is the height of the tree. The insert, delete, and successor functions
    also all have complexities of O(h). If there are n nodes in the tree, the height is: logn <= h <= n. This means eahc of these functions have time complexities
    of O(logn) in certain cases. The transplant algorithm has a constant time complexity for all cases.

(c) 
        There is a file called 'timing.txt' which includes the output of the timing runs in the main. I timed the insert by counting the number of seconds it took to
    insert n nodes into the tree. The search is timed by searching for 1 node in a tree of size n. The remove is also timed this way, by removing 1 node in a tree
    of size n. The graph of these times is included in the .docx file included in the zip. Looking at the times, it is odd that the search showed up as taking 0 seconds
    several times... maybe this is because it went so quickly? The insert data made the most sense, as the number of nodes increased, so did the time taken. The remove
    data was very odd, as the time taken actually got faster as the number of nodes increased. Possibly this is because I did not go up in size by enough. Also, I am
    realizing that the insert function is run n times, however the search and remove only need to traverse n times and are only run once. This is obviously a big difference.


(d) 
        The print method I have included is very basic and does not show the levels of the tree. This should be improved to better display the trees parts.
    I also noticed seg faults in random cases, but they only happen on occasion which is weird.
    In addition, I coded a destructor however when I run it, the program seg faults after the test remove in the first part of the main. For this reason, I have it 
    commented out at the moment but I know it is important and should not be left out. This is obviously a big issue with my code.
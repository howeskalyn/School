Kalyn Howes
3.4.21
Lab 5
README.txt


(a)
	Using a matrix class keeps all of the necessary functions organized. The matrix class had 3 private variables that include the amount of rows, n, the amount of columns, m and a dynamic array. Apart from the main functions for matrix operations, I also overloaded multiple operators and created some helper functions, like sets and gets, to make life easier. 
	As of right now, in my Lab5.cpp file, there are functions to make different types of matrices such as diagonal, triangular, identity, random, and a vector. I will most likely end up moving these to the matrix class itself, however I started with them in the separate file while I was working everything out.
	As a bonus function (and for bonus points), I included an operator overload for '*' to act as scalar multiplication of a matrix. This function is tested and used along with the other three, main operations.
	In order to make changes and re-run this program, a make clean command is required. 



(b)
	Included in this zip is a MatrixOperations.docx file that shows a graph representing the time in seconds it took for each matrix operation for differing sizes. Looking specifically at random, square matrices, the subtraction operation took longer than the others. However for the 1000x1000 matrix, the multiplication took ~6 seconds which could not be included on the graph without skewing it. This shows that the multiplication will most likely pass subtraction in number of seconds as the matrix size increases. Addition was in the middle, and the scalar operation took the least amount of time.
	Of course overall, as the size of the matrices increase, so will the number of seconds taken to complete the matrix operation.



(c)
	The addition operation has a time complexity of theta(n^2), when done on two square matrices.This is due to the 2 for loops that go from i to n with constants inside. 

	The subtraction operation has a time complexity of theta(n^2), when done on two square matrices. This is due to the 2 for loops that go from i to n with constants inside.

	The multiplication operation has a time complexity of theta(n^3), when done on two square matrices. This is due to the 3 for loops that go from i to n with constants inside.

	For the three operations above, if the matrices were not square, they would have a time complexities of theta(1) if the size of the matrices were not compatible. If the sizes were compatible, the timing would be theta(n*m) for addition & subtraction, and theta(n*m*k) for multiplication (when A is a nxm and B is a mxk).

	The scalar operation has a time complexity of theta(n^2), when done on two square matrices. This is due to the 2 for loops that go from i to n with constants inside.
	

(d) 
	There aren't many improvements to make to the code. The functions that create different types of matrices can be moved to the matrix class instead of the main file, but that is about all I see at the moment.
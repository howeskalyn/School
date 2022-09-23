Kalyn Howes
Project 1 
3.14.21
README.txt

-----------------------------------------------------------------------------------------------

At the moment, I do not know how to create a makefile that produces 2 usable executables. Because of this, to run each individual main, you have to comment out the other main in the makefile.
-----------------------------------------------------------------------------------------------
Driver.cpp

A call of make clean is required before every make of this file.

	The Driver.cpp program demonstrates the various individual matrix operations. These operations include the addition, subtraction, multiplication, and scalar multiplication of matrices, which can be found in the matrix class I created. The main operation being tested is the inverse function which finds the inverse of a square matrix. This function is also included in my matrix class. The inverse algorithm includes the usage of all the other matrix operations, therefore when testing the inverse, the other operations were being tested as well.
	
	The Driver.cpp main also includes timing tests of the inverse function/algorithm. There is a .docx file within the zip called 'Project1Graphs' which includes two graphs. The first displays how long in seconds it took to invert a matrix of various sizes and types, while the second shows the number of operations made for the same instances. As usual, as the matrix size increases so does the amount of time the inverse took to complete and the number of operations included. Looking at the first graph, there is an odd pattern between the matrices that were random and the matrices that were diagonal. For each change in matrix dimensions the matrix type that took less time switches between random and diagonal. As for the number of operations, each matrix type had almost the same amount of basic arithmetic used for each size. 
	There was one data point not included on the graphs in case it became an outlier. The matrix size of this data piece was 51x51, but the time to invert it was still under one second. This is very impressive considering a 51x51 matrix has 2601 elements within it. Also, the number of operations was only 2003 which isn't too many more than the matrix of size 11x11. Overall this algorithm seems to preform quickly, and perhaps the 51x51 data could've been included on the graph after all.

	
BONUS:
	As a bonus function, there is a determinant calculator in my matrix class. Along with this is a cofactor function which uses the cofactor expansion method to find the determinant of any size, square matrix. This function is also demonstrated in the Driver.cpp file to ensure its correctness.
	While working with the inverse algorithm and testing, I found a special case. If the top-left portion, B, of the matrix is 0, the inverse of B comes out as 0 which throws off the rest of the inverse algorithm. Because of this, I created an if statement to check if there is a 2x2 matrix with 0 in the [0][0] position being sent into the inverse function. If this rare case occurs, I called the determinant function to find the inverse of the 2x2 matrix using the determinant I created:
1/det * (d -b)
        (-c a)
If you're curious, I found this special case by inverting a symmetric 4x4 matrix with the following values:
(1 0 1 2)
(0 2 2 4)
(1 2 3 4)
(2 4 4 4)
There is probably another way to fix this by just using the algorithm itself, but I figured my idea wasn't a bad way to do it and I got to test my determinant function.


-----------------------------------------------------------------------------------------------
Project1.cpp

	A call of make clean is required before every make of this file.

	The Project1.cpp reads in the economy data and reports the production needed. The program should reports to the user how much of each product is needed to simultaneously satisfy all economic demands. This file must be run using a two part command line. For example if the input file was names input2.txt, to call the main on this file you would use the command: ./Project1.exe input2.txt

The input files must be in the following form:

Coal
Electricity
Produce
---
0.6 0.02 0.1
0.3 0.2 0.4
0.2 0.4 0.3
---
20
34
80

This means the number of products listed at the top must be equal to the dimension of the matrix after the '---' sector and the number of elements in the vector after the second '---' must also be equal to this number. The file I created to test a different product amount is stored in input2.txt. Since I randomly created the products and numbers myself, it doesn't make much sense, but it gets the job done for testing. The correct answer includes negative numbers... but my program outputs the correct answer so it works as it should. I also tested it on the input file given and shown above and the output was the same as in the Project1 Instructions given.
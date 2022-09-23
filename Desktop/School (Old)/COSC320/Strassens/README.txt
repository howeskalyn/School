Kalyn Howes
3.14.21
Project1 - BONUS
README

	A make clean command is required to compile the Strassens.cpp main.

	This zip file includes the same matrix class from Project1, but has an implementation of Strassen’s algorithm for matrix multiplication. I implemented this extra credit in a different folder in fear of ruining my original matrix class.

	To compare Strassens algorithm to the typical Matrix Multiplication algorithm, I did some timing tests. For a 2x2 matrix, I found the average time for multiplication was 0.0000154, while for a 3x3 it was 0.0000636. As for Strassens the 2x2 had an average of 0.0000402 and for 3x3 0.000111.

	Just looking at 2x2 and 3x3 there is not much of a difference in timing. Because of this, it is necessary to try bigger matrices. In the zip file, there is a .docx file which consists of a graph that shows the comparison between the time taken to multiply a square matrix by the original matrix multiplication algorithm vs with Strassen’s algorithm. The graph/data I collected does not match the theoretical time complexity we found in class. Instead of Strassen's being faster, it actually becomes much slower and the matrices increase in dimension. Perhaps this is because of the way I implemented the algorithm in my code considering the Strassen function itself needs about 12 other helper functions for it to work. 

	
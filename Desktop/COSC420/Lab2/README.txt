README
Kalyn Howes
Lab 2
10.10.21
____________________________________________________________________________________

(a/b) The times should get lower as it is run on more processors but obviously I did not see that happen with my timing. The fact it is seg faulting and that I have no storage on my Mac are definitely contributors to this. I have included Lab2 Timing anyways. The times listed are form the "total" when running time mpirun -n 5 ./main.

(c) Matrices are very commonly used data structures for many things. Having simple operations such as addition, subtraction, transpose, and multiplication could all be very helpful when working with matrices of data. Since running on multiple processors (should) improve efficiency, this lab could be very useful when dealing with large matrices/large data sets.

(d)
1) It would be great if it worked - segfaulting on the last gather (matrix multiplication)
2) The matrix subroutines should really return matrix types and not just integer arrays.
3) There should be a subroutine created for the scatter set up & initialization code.

Chloe VanCory & Kalyn Howes
Lab 4
COSC 420
11.7.21
__________________________________________________________________________________

Comparing Version1 & Version2:

Based from our timing on (at most) 10,000x10,000 matrices, running on 2 or 3 nodes, it seems Version1 is slightly faster than Version2. The timing for these are in Timing.txt

__________________________________________________________________________________

(a) One iteration of the Power Method includes an entire matrix multiplication process, plus some constant calculations and a vector division by a scalar. With this, the time-complexity will be approximately O(n^3), with n being the dimensions of a square matrix. Of course as the matrix size increases, so will the time taken for the Power Method.

(b) Adding more nodes does not perfectly divide the time taken but it does improve it. For example, running Version1 on 10000x10000 on 2 nodes took about 2.3 seconds while it only took 1.6 on 3 nodes.

(c) There are many real-life applications of eigenvalues, which is what the Power Method finds. Eigenvalues are used for finding limits for communication systems, designing bridges, and even stereo systems. Using distributed code such as ours could speed up these processes and allow for more efficient use in engineering and business.

(d) 

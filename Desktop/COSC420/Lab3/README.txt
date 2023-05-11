README
Kalyn Howes & Chloe VanCory
Lab 3
10.31.21
___________________________________________________________________

(a)  The Gauss Jordan Elimination algorithm has a theoretical time complexity of O(n^3) since it could require n divisions, n multiplications, and n subtractions/additions, when the matrix is nxn. 


(b) According to the data, does adding more nodes perfectly divide the time taken by the program?
Adding more nodes does divide the time taken by the program, but not quite perfectly. A 100x100 matrix on 10 nodes took 0.124 seconds while it only took 0.007 on 20 nodes. Similarly, a 1000x1000 matrix took 1.27 seconds on 10 nodes while only 0.188 on 20. Finally, a 10000x10000 matrix took about 9 minutes using 10 nodes but only about 6 on 20 nodes. We only timed matrices larger than 10,000 on 20 nodes since it would take too long otherwise. Even with 20 nodes, a 20000x20000 matrix took about 52 minutes to complete.


(c) Matrices are used for never-ending reasons when it comes to programming. Specifically, Gauss-Jordan elimination is used to solve systems of complex linear equations. In "real-life" Gauss-Jordan Elimination is used for scheduling algorithms and in Robust Fingerprint Image Enhancement. The process is used to enhance the images. Using distributed code such as ours could speed up these processes and allow for more efficient use in business.


(d) The matrix multiplication could be optimized by looking into cache blocking. 
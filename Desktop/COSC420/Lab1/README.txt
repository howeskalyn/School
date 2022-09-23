Kalyn Howes
Lab1 
9/10/21
README.txt

-------------------------------------------------------------------------------------------------
NOTES:

#make
mpicc hello.c

#compile with -std=c99 to get the inline int declaration

#run
./a.out

#run 5 times
mpirun -n 5 ./hello

-------------------------------------------------------------------------------------------------
QUESTIONS:

(a) What is the theoretical time complexity of your sorting algorithms (best and worst case), in terms of the input size?
(b) For this specific task, the structure and flow of your program may drastically influence the runtime. What steps did/can you take to gain performance of the entire process?
(c) According to the data, does adding more nodes perfectly divide the time taken by the program?
(d) Justify/prove the fact that one needs only check up to sqrt(N) in the brute force primality test.
(e) How could the code be improved in terms of usability, efficiency, and robustness?
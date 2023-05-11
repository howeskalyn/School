/* Kalyn Howes
    Lab 2
    9.24.21
    communication.c - practice using MPI_Scatter and MPI_Reduce
*/

#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <string.h>

// subroutine to print an array in a buffered manner, for thread-safety
// returns a char* buffer of a stringified array of integers
// this routine allocates n*5 + 1 bytes which need to be free'd later!
char* printArr(int* arr, int n, int rank){
  char* buf = malloc(n*(4+1) + 1);
  buf[0] = '\0';
  const char* fmt = "%4d ";
  char tmp[4+1 + 1]; // same width as fmt plus a null term

  for(int i=0; i<n; i++){
     sprintf(tmp, fmt, arr[i]);
     strcat(buf, tmp);
  }

  return buf;
}

int main(int argc, char** argv){
  MPI_Init(&argc,  &argv); // initialize the MPI execution environment
  int worldSize, rank;
  MPI_Comm world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &rank);

  // (a) A root node generates two random vectors in high dimension (thousands)
  int N = 10000000;
  char* buf; // for printing

  // vectors - two arrays (one is holding a 'row' and one a 'column')
  int* A = malloc(N * sizeof(int));
  int* sendA = NULL;
  int* B = malloc(N * sizeof(int));
  int* sendB = NULL;

  // only create A & B if its the root
  if (rank == 0) {
    srand(time(0));
    // allocate space for 100 numbers per node - malloc needs its size in bytes
    sendA = malloc(worldSize * N * sizeof(int));
    sendB = malloc(worldSize * N * sizeof(int));
    for (int i = 0; i < N * worldSize; i++) {
      sendA[i] = rand() % 100;
      sendB[i] = rand() % 100;
    }
  }

// (b) “Blocks” of those vectors are then scattered to various nodes, each of which performs a partial inner product
  //printf("Node %d calling Scatter...\n", rank);
  MPI_Scatter(
      sendA,       // sendbuf
      N,           // sendcount
      MPI_INT,     // sendtype
      A,           // recvbuf
      N,           // recvcount
      MPI_INT,     // recvtype
      0,           // root rank
      world        // comm
  );
  MPI_Scatter(
      sendB,       // sendbuf
      N,           // sendcount
      MPI_INT,     // sendtype
      B,           // recvbuf
      N,           // recvcount
      MPI_INT,     // recvtype
      0,           // root rank
      world        // comm
  );
  
  //printf("Rank %d after scatter\n", rank);

  // // report what they received
  // buf = printArr(A, N, rank);
  // printf("Rank %d numbers: %s\n", rank, buf);
  // free(buf); // buf got malloc'd by printArr
  // buf = printArr(B, N, rank);
  // printf("Rank %d numbers: %s\n", rank, buf);
  // free(buf); // buf got malloc'd by printArr

  // find the partial inner product (dot product multiplication)
  int* C = malloc(N * sizeof(int)); // hold resulting inner products
  // for the length of the vectors, N
  for (int i = 0; i < N; i++) {
      C[i] = A[i] * B[i];
  }

  // // testing inner products
  // buf = printArr(C, N, rank);
  // printf("Rank %d numbers: %s\n", rank, buf);
  // free(buf);

  // sum up Cs locally
  int sum = 0;
  for (int i = 0; i < N; i++) {
    sum += C[i];
  }

  // printf("Sum of C: %d\n", sum);

  // (c) The partial inner products are then summed by the root and reported to the user
  int totalsum = 0;
  MPI_Reduce(
    &sum,       // send buffer, an array
    &totalsum,   // recv buffer
    1,          // count
    MPI_INT,    // datatype
    MPI_SUM,    // operation handle
    0,          // rank of root process
    world       // comm
  );

  // // report what it received
  // if( rank == 0 ){
  //   printf("\nTotal sum: %d\n", totalsum);
  // }
  
  free(A);
  free(B);

  if( rank == 0 ) {
    free(sendA);
    free(sendB);
  }

  MPI_Finalize(); // Terminates MPI execution environment
  return 0;
}
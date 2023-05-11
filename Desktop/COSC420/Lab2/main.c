/* Kalyn Howes
    Lab 2
    9.24.21
    main.c - main to text matrix library functions
*/

#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <string.h>

int main (int argc, char** argv) {
  MPI_Init(&argc,  &argv); // initialize the MPI execution environment
  int worldSize, rank;
  MPI_Comm world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &worldSize);
  MPI_Comm_rank(world, &rank);

  // --------- OUTPUT FILE STUFF (unused)----------
  // sends each rank to a different output file for easier reading
  // (the fflush(FILE* fh) function can force a buffer flush through the file)
  // FILE *handle;
  // char fname[256];
  // sprintf(fname, "outfile_%d.txt", rank);
  // handle = fopen(fname, "w+");
  // fprintf(handle, "Begin output from processor %d", rank);

  // --------- MATRIX SET UP ----------
  matrix A, B;
  int N = 10000;
  A.rows = N;
  A.cols = N;
  B.rows = N;
  B.cols = N;

  // only create matrix A and B once
  if (rank == 0) {

    // build and allocate a matrix struct
    A.data = malloc(A.rows*A.cols*sizeof(int));
    B.data = malloc(B.rows*B.cols*sizeof(int));

    // fills matrix A with random nums
    int counter = 0;
    for(int i = 0; i < A.rows; i++){
      for(int j = 0; j < A.cols; j++){
        ACCESS(A,i,j) = rand() % 10;
      }
    }
    // printf("Matrix A:\n");
    // printMatrix(A);

    // fills matrix B with random nums
    counter = 0;
    for(int i = 0; i < B.rows; i++){
      for(int j = 0; j < B.cols; j++){
        ACCESS(B,i,j) = rand() % 10;
      }
    }
    // printf("Matrix B:\n");
    // printMatrix(B);
  }

  //  ----------- SCATTER SET UP -----------
  // assume for simplicity that N < # of rows, N = number of nodes
  // sendcts - how many actual data elements will be sent
  // displacements(displs) - index where each scatter block starts
  int *sendctsA = malloc(worldSize*sizeof(int)); // significant at every node
  int *sendctsB = malloc(worldSize*sizeof(int));

  // only count rows
  int minSendA = A.rows / worldSize; // will round down, # rows to send
  int minSendB = B.rows / worldSize;
  for (int i = 0; i < worldSize; i++) {
      sendctsA[i] = minSendA;
      sendctsB[i] = minSendB;
  }

  // one way: gives last guy more work!
  // sendcts[worldSize - 1] += A.rows % worldSize;
  // OR: tack the extras on 1 by 1 from the 1st
  for (int i = 0; i < A.rows % worldSize; i++) {
      sendctsA[i]++;
  }
  for (int i = 0; i < B.rows % worldSize; i++) {
      sendctsB[i]++;
  }

  // actual sendcts needs to be each one times the columns!
  for (int i = 0; i < worldSize; i++) {
      sendctsA[i] *= A.cols;
  }
  for (int i = 0; i < worldSize; i++) {
      sendctsB[i] *= B.cols;
  }

//   // test printing
//   if (rank == 0) {
//       for (int i = 0; i < worldSize; i++) {
//           printf("A: Will scatter %d elements to rank %d\n", sendctsA[i], i);
//           printf("B: Will scatter %d elements to rank %d\n", sendctsB[i], i);
//       }
//   }

  // need displacements: do cumulative sum of sendcts
  int* displsA = malloc(worldSize*sizeof(int));
  int* displsB = malloc(worldSize*sizeof(int));
  displsA[0] = 0;
  displsB[0] = 0;
  for (int i = 1; i < worldSize; i++) {
      displsA[i] = displsA[i - 1] + sendctsA[i - 1];
      displsB[i] = displsB[i - 1] + sendctsB[i - 1];
  }
  
// test printing
//  if (rank == 0) {
//       for (int i = 0; i < worldSize; i++) {
//           printf("Rank %d -- A: Will start scattering %d elements to rank %d at index %d\n", rank, sendctsA[rank], i, displsA[i]);
//           printf("Rank %d -- B: Will start scattering %d elements to rank %d at index %d\n", rank, sendctsB[rank], i, displsB[i]);
//       }
//  }

  // make room for scattered data
  //int* recvbufA = malloc(sendctsA[rank]*sizeof(int));
  matrix recvA;
  //if (rank == 0) {
  recvA.rows = sendctsA[rank] / A.cols;
  recvA.cols = A.cols;
  recvA.data = malloc(sendctsA[rank]*sizeof(int));
    // printf("recvA rows: %d & cols: %d", recvA.rows, recvA.cols);
    // printf("\nMatrix recvA\n");
    // printMatrix(recvA);
  //}

  MPI_Scatterv (
      A.data,          // sendbuf
      sendctsA,        // send counts
      displsA,         // displacements
      MPI_INT,         // send type
      recvA.data,      // recvbuf
      sendctsA[rank],  // recv count
      MPI_INT,         // recv type
      0,               // root
      world            // comm
  );


  matrix recvB;
  //if (rank == 0) {
  recvB.rows = sendctsB[rank] / B.cols;
  recvB.cols = B.cols;
  recvB.data = malloc(sendctsB[rank]*sizeof(int));
    //printf("recvB Rows: %d & cols: %d", recvB.rows, recvB.cols);
  //}

  MPI_Scatterv (
      B.data,          // sendbuf
      sendctsB,        // send counts
      displsB,         // displacements
      MPI_INT,         // send type
      recvB.data  ,    // recvbuf
      sendctsB[rank],  // recv count
      MPI_INT,         // recv type
      0,               // root
      world            // comm
  );

  // ----------- CALCULATIONS -----------
  // ADDITION
  int *sums; // =  malloc(A.rows*A.cols*sizeof(int)); leaky!!
  // check if addition is possible
  if (recvA.cols == recvB.cols && recvA.rows == recvB.rows) {
    sums = matrixAddition(recvA, recvB, rank);

    // printing
    // char* buf = printArr(sums, (recvA.rows)*(recvA.cols), rank);
    // printf("\nSums received: %s\n", buf);
    // free(buf);

  } else {
    printf("\nMatrix A & B have different dimensions and cannot be added.\n");
  }

  int *finalsums;
  if ( rank == 0 ) finalsums = malloc((A.rows)*(A.cols)*sizeof(int));
  else finalsums = NULL;

  MPI_Gatherv(
      sums,            // sendbuf
      sendctsA[rank],  // sendcount
      MPI_INT,         // sendtype
      finalsums,       // recvbuf
      sendctsA,        // recvcount
      displsA,         // displacement
      MPI_INT,         // recvtype
      0,               // root rank
      world            // comm
  );

  // printing
  // if ( rank == 0 ){
  //   char* buf = printArr(finalsums, (A.rows)*(A.cols), rank);
  //   printf("\nFinal Sums: %s\n", buf);
  //   free(buf);
  // }

  // SUBTRACTION
  int *differences;
  // check if subtraction is possible
  if (recvA.cols == recvB.cols && recvA.rows == recvB.rows) {
    differences = matrixSubtraction(recvA, recvB, rank);

    // printing
    // char* buf = printArr(differences, (recvA.rows)*(recvA.cols), rank);
    // printf("\nDifferences received: %s\n", buf);
    // free(buf);

  } else {
    printf("\nMatrix A & B have different dimensions and cannot be subtracted.\n");
  }

  int *finaldiffs;
  if ( rank == 0 ) finaldiffs = malloc((A.rows)*(A.cols)*sizeof(int));
  else finaldiffs = NULL;

  MPI_Gatherv(
      differences,     // sendbuf
      sendctsA[rank],  // sendcount
      MPI_INT,         // sendtype
      finaldiffs,      // recvbuf
      sendctsA,        // recvcount
      displsA,         // displacement
      MPI_INT,         // recvtype
      0,               // root rank
      world            // comm
  );

  // printing
  // if ( rank == 0 ) {
  //   char* buf = printArr(finaldiffs, (A.rows)*(A.cols), rank);
  //   printf("\nFinal Differences: %s\n", buf);
  //   free(buf);
  // }

  // TRANSPOSE - dont need to use MPI, so send in just A matrix, not recvbufA
  matrix TB;
  TB.cols = B.rows;
  TB.rows = B.cols;
  // if (rank == 0) {
  //   TB = matrixTranspose(B);
  //   puts("\nTranspose of Matrix B: ");
  //   printMatrix(TB);
  // }

  // MULTIPLICATION:
  // A's scatter is fine the way it is
  // scatter the transpose of B & broadcast - gather each row they calculated & add to a final matrix
  // prepare by transposing B & give scatter TB.data

  // ---------- SCATTER SET UP (AGAIN) -----------
  int *sendctsTB = malloc(worldSize*sizeof(int));
  int minSendTB = TB.rows / worldSize;
  for (int i = 0; i < worldSize; i++) {
      sendctsTB[i] = minSendTB;
  }
  for (int i = 0; i < TB.rows % worldSize; i++) {
      sendctsTB[i]++;
  }
  for (int i = 0; i < worldSize; i++) {
      sendctsTB[i] *= TB.cols;
  }
  int* displsTB = malloc(worldSize*sizeof(int));
  displsTB[0] = 0;
  for (int i = 1; i < worldSize; i++) {
      displsTB[i] = displsTB[i - 1] + sendctsTB[i - 1];
  }

  // test printing
  //  if (rank == 0) {
  //       for (int i = 0; i < worldSize; i++) {
  //           printf("Rank %d -- A: Will start scattering %d elements to rank %d at index %d\n", rank, sendctsA[rank], i, displsA[i]);
  //           printf("Rank %d -- B: Will start scattering %d elements to rank %d at index %d\n", rank, sendctsB[rank], i, displsB[i]);
  //       }
  //  }

  matrix recvTB;
  //if (rank == 0) {
    recvTB.rows = sendctsTB[rank] / TB.cols;
    recvTB.cols = TB.cols;
    recvTB.data = malloc(sendctsTB[rank]*sizeof(int));
  //}

  //puts("before scatter...\n");
  // printf("SendctsTB[%d]: %d", rank, sendctsTB[rank]);

  MPI_Scatterv (
    TB.data,          // sendbuf
    sendctsTB,        // send counts
    displsTB,         // displacements
    MPI_INT,          // send type
    recvTB.data  ,    // recvbuf
    sendctsTB[rank],  // recv count
    MPI_INT,          // recv type
    0,                // root
    world             // comm
  );

  //puts("after scatter...\n");

  // BROADCAST
  MPI_Bcast (
    TB.data,            // starting address of buffer (choice)
    TB.rows * TB.cols,  // number of entries in buffer (integer)
    MPI_INT,            // data type of buffer (handle)
    0,                  // rank of broadcast root (integer)
    world               // communicator (handle)
  );

  // printf("\nPrinting recvA: \n");
  // printMatrix(recvA);
  // printf("\n& recvTB: \n");
  // printMatrix(recvTB);

  int *C; //= malloc(recvA.rows * recvTB.cols * sizeof(int));

  //if (A.rows == B.cols) 
  C = matrixMultiplication(recvA, recvTB); // do multiplication with A & the transpose
  //else puts("Matrix dimensions do not match for proper multiplication.");

  // char* buf = printArr(C, recvA.rows * recvTB.cols, rank);
  // printf("\nTemporary product: %s\n", buf);
  // free(buf);

  int *finalproducts;
  if ( rank == 0 ) {
    finalproducts = malloc((recvA.rows)*(recvTB.cols)*sizeof(int));
  } else finalproducts = NULL;

  // GATHER - SEG FAULTING HERE......****
  MPI_Gatherv(
      C,                 // sendbuf
      sendctsTB[rank],   // sendcount
      MPI_INT,           // sendtype
      finalproducts,     // recvbuf
      sendctsTB,         // recvcount
      displsTB,          // displacement
      MPI_INT,           // recvtype
      0,                 // root ranks
      world              // comm
  );

  // printing
  // if ( rank == 0 ) {
  //   char* buf = printArr(finalproducts, (recvA.rows)*(recvTB.cols), rank);
  //   printf("\nFinal Products: %s\n", buf);
  //   free(buf);
  // }

  // fclose(handle); // release the file

  if (rank == 0) {
    free(A.data);
    free(B.data);
    free(TB.data);
    free(recvA.data);
    free(recvB.data);
    free(finalsums);
    free(finaldiffs);
    free(finalproducts);
  }

  free(sums);
  free(differences);
  free(sendctsA);
  free(sendctsB);
  free(displsA);
  free(displsB);
  free(sendctsTB);
  free(displsTB);
  free(recvTB.data);

  MPI_Finalize(); // Terminates MPI execution environment
  return 0;

}
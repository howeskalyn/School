/* Kalyn Howes
    Lab 2
    9.24.21
    matrix.c - write a library to perform the basic matrix operations of addition, subtraction, multiplication, and transpose
*/

#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <string.h>

// prints matrix nicely w/ spacing
void printMatrix(matrix A) {
  for(int i = 0; i < A.rows; i++) {
    for(int j = 0; j < A.cols; j++) {
      printf("%6d ", A.data[A.cols * i + j]);
    }
    printf("\n");
  }
}

// subroutine to print an array in a buffered manner, for thread-safety
// change based on output size!!!
char* printArr(int* arr, int n, int rank){
  char* buf = malloc(n*(6+1) + 1);
  buf[0] = '\0';
  const char* fmt = "%6d ";
  char tmp[6+1 + 1]; // same width as fmt plus a null term

  for(int i=0; i<n; i++){
     sprintf(tmp, fmt, arr[i]);
     strcat(buf, tmp);
  }

  return buf;
}

// // scatter set up & scatterv of 2 matrices
// void scatter() {
//   int *sendctsA = malloc(worldSize*sizeof(int)); // significant at every node
//   int *sendctsB = malloc(worldSize*sizeof(int));

//   int minSendA = A.rows / worldSize; // will round down, # rows to send
//   int minSendB = B.rows / worldSize;
//   for (int i = 0; i < worldSize; i++) {
//       sendctsA[i] = minSendA;
//       sendctsB[i] = minSendB;
//   }

//   for (int i = 0; i < A.rows % worldSize; i++) {
//       sendctsA[i]++;
//   }
//   for (int i = 0; i < B.rows % worldSize; i++) {
//       sendctsB[i]++;
//   }
//   for (int i = 0; i < worldSize; i++) {
//       sendctsA[i] *= A.cols;
//   }
//   for (int i = 0; i < worldSize; i++) {
//       sendctsB[i] *= B.cols;
//   }

//   int* displsA = malloc(worldSize*sizeof(int));
//   int* displsB = malloc(worldSize*sizeof(int));
//   displsA[0] = 0;
//   displsB[0] = 0;
//   for (int i = 1; i < worldSize; i++) {
//       displsA[i] = displsA[i - 1] + sendctsA[i - 1];
//       displsB[i] = displsB[i - 1] + sendctsB[i - 1];
//   }

//   matrix recvA;
//   if (rank == 0) {
//     recvA.rows = sendctsA[rank] / A.cols;
//     recvA.cols = A.cols;
//     recvA.data = malloc(sendctsA[rank]*sizeof(int));
//   }

//   MPI_Scatterv (
//       A.data,          // sendbuf
//       sendctsA,        // send counts
//       displsA,         // displacements
//       MPI_INT,         // send type
//       recvA.data,      // recvbuf
//       sendctsA[rank],  // recv count
//       MPI_INT,         // recv type
//       0,               // root
//       world            // comm
//   );

//   matrix recvB;
//   if (rank == 0) {
//     recvB.rows = sendctsB[rank] / B.cols;
//     recvB.cols = B.cols;
//     recvB.data = malloc(sendctsB[rank]*sizeof(int));
//   }

//   MPI_Scatterv (
//       B.data,          // sendbuf
//       sendctsB,        // send counts
//       displsB,         // displacements
//       MPI_INT,         // send type
//       recvB.data  ,    // recvbuf
//       sendctsB[rank],  // recv count
//       MPI_INT,         // recv type
//       0,               // root
//       world            // comm
//   );
// }

// separate the matrix by the number of processors (remember a matrix is just 1 array here, no 2D)
// need to split up array A.data by number of cols so the addition matches up
int* matrixAddition(matrix A, matrix B, int rank)  {
  int *sums = malloc((A.rows)*(A.cols)*sizeof(int));
  for (int i = 0; i < (A.rows) * (A.cols); i++) { 
    sums[i] = A.data[i] + B.data[i];
  }
  return sums;
}

// subtracts 2 matrices
int* matrixSubtraction(matrix A, matrix B, int rank) {
  int *d = malloc((A.rows)*(A.cols)*sizeof(int));
  for (int i = 0; i < (A.rows) * (A.cols); i++) { 
    d[i] = A.data[i] - B.data[i];
  }
  return d;
}

// matrix multiplication: // nxm * mxk = > nxk
int* matrixMultiplication(matrix A, matrix B) {

  //printf("\nIN MATRIX MULTIPLICATION \n");

  // testing:
  // printf("\nMatrix A: \n");
  // printMatrix(A);
  // printf("\nMatrix B: \n");
  // printMatrix(B);

  // matrix C;
  // C.rows = A.rows;
  // C.cols = B.cols;
  // C.data = malloc(C.rows*C.cols*sizeof(int));

  int *C = malloc(A.rows*B.cols*sizeof(int));

  // printf("A.rows: %d & A.cols = %d\n", A.rows, A.cols);
  // printf("B.rows: %d & B.cols = %d\n", B.rows, B.cols);

  // check to see if multiplication is possible
  int count = 0;
  //if (A.rows == B.cols) { // cant do check here because scatter send differing sizes
    for (int i = 0; i < A.rows; i++) {
      for (int j = 0; j < B.cols; j++) {
        int sum = 0;
        //printf("sum reset\n");
        for (int k = 0; k < A.rows; k++) {
          sum += ACCESS(A, i, k) * ACCESS(B, k, j);
          //printf("current sum: %d \n", sum);
        }
        //ACCESS(C, i, j) = sum;
        C[count++] = sum;
      }
    }
  //} else {
    //printf("\nMatrix A & Matrix B are not able to be multiplied because of their dimensions.\n");
  //}

  // printf("Returning C: \n");
  // for (int i = 0; i < A.rows*B.cols; i++)
  //   printf("%d", C[i]);
  return C;
}

// transposes a single matrix that is stored in an array
matrix matrixTranspose(matrix A) {
  matrix T;
  T.rows = A.cols;
  T.cols = A.rows;
  T.data = malloc(T.rows*T.cols*sizeof(int));

  for (int i = 0; i < T.rows; i++) {
    for (int j = 0; j < T.cols; j++) {
      ACCESS(T, i, j) = ACCESS(A, j, i);
    }
  }

  return T;
}
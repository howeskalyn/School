#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define ROOT 0

#define INDEX(i, j, n, m) i *m + j
#define ACCESS(A, i, j) A.data[INDEX(i, j, A.rows, A.cols)]

typedef struct Matrix {
  int rows;
  int cols;
  double *data;
} Matrix;

typedef struct Vector {
  double *data;
  int length;
} Vector;

void initMatrix(Matrix *A, int rows, int cols) {
  A->rows = rows;
  A->cols = cols;
  A->data = malloc(A->rows * A->cols * sizeof(double));
}

void printMatrix(Matrix A) {
  for(int i = 0; i < A.rows; i++) {
    for(int j = 0; j < A.cols; j++) {
      printf("%6f ", A.data[A.cols * i + j]);
    }
    printf("\n");
  }
}

Matrix matrixMultiplication(Matrix A, Matrix B) {
  Matrix C;
  C.rows = A.rows;
  C.cols = B.cols;
  C.data = malloc(A.rows*B.cols*sizeof(double));
  //int count = 0;

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.cols; j++) {
      double sum = 0;
      //printf("sum reset\n");
      for (int k = 0; k < A.rows; k++) {
        sum += ACCESS(A, i, k) * ACCESS(B, k, j);
        //printf("current sum: %f \n", sum);
      }
      ACCESS(C, i, j) = sum;
      //C[count++] = sum;
    }
  }

  //puts("RESULT:");
  //printMatrix(C);
  return C;
}

/* Kalyn Howes
    Lab 2
    9.24.21
    matrix.h - header file
*/
// Use macros for some speed - this a "function" that takes four arguments
#define INDEX(i,j,n,m) i * m + j
#define ACCESS(A,i,j) A.data[INDEX(i,j,A.rows,A.cols)]

// matrix struct
typedef struct matrix {
  int rows;
  int cols;
  int* data;
} matrix;

void printMatrix(matrix);
char* printArr(int*, int, int);
int* matrixAddition(matrix, matrix, int);
int* matrixSubtraction(matrix, matrix, int);
int* matrixMultiplication(matrix, matrix);
matrix matrixTranspose(matrix);
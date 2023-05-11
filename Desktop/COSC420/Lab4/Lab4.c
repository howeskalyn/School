#include <stdio.h>
#include <math.h>
#include "matrixFunctions.h"

/*
    This works only for a 2x2 matrix at this time.
*/

int main(int argc, char** argv){

    // hardcode test matrix
    Matrix A;
    A.rows = 2;
    A.cols = 2;
    A.data = malloc(A.rows*A.cols*sizeof(double));
    ACCESS(A, 0, 0) = 0;
    ACCESS(A, 0, 1) = 1;
    ACCESS(A, 1, 0) = -2;
    ACCESS(A, 1, 1) = -3;
    puts("MATRIX A:");
    printMatrix(A);

    // hardcode 1s vector
    Matrix x;
    x.rows = 2;
    x.cols = 1;
    x.data = malloc(x.rows*x.cols*sizeof(double));
    ACCESS(x, 0, 0) = 1;
    ACCESS(x, 1, 0) = 1;
    puts("VECTOR X:");
    printMatrix(x);
    puts("\n");

    // hardcode temp for x
    Matrix temp;
    temp.rows = 2;
    temp.cols = 1;
    temp.data = malloc(temp.rows*temp.cols*sizeof(double));

    double e = 10E-16;
    //printf("Threshold: %f\n", e);

    // difference between first values & difference between second values
    double diff1 = 0, diff2 = 0;
    int count = 0;

    // if difference is less than threshold OR there has been 20 iterations
    while (diff1 <= e || diff2 <= e || count <= 10) {
        printf("\ncount: %d\n", count);

        temp = matrixMultiplication(A, x);
        puts("TEMP:");
        printMatrix(temp);

        // normalize: 
        double temp_m = sqrt( (ACCESS(temp, 0, 0)*ACCESS(temp, 0, 0)) + (ACCESS(temp, 1, 0)*ACCESS(temp, 1, 0)) );
        printf("Temp Magnitude: %f\n", temp_m);

        // reset x to new values using temp and magnitude
        ACCESS(x, 0, 0) = ACCESS(temp, 0, 0) / temp_m;
        ACCESS(x, 1, 0) = ACCESS(temp, 1, 0) / temp_m;
        puts("New x:");
        printMatrix(x);

        // differences should be calculated using absolute value - fabs does it for doubles/floats
        diff1 = fabs(ACCESS(x, 0, 0) - ACCESS(temp, 0, 0));
        diff2 = fabs(ACCESS(x, 0, 1) - ACCESS(temp, 0, 1));

        count++;
    }

    // eigen estimate = magnitude(Ax)/magnitude(x)

  return 0;
}
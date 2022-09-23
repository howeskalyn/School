// Kalyn Howes
// 3.4.21
// Lab 5
// Matrix class, matrix.cpp

#include "matrix.h"
#include <iostream>
#include <iomanip> // for setw

// constrcutor - takes in matrix dimensions & a default value
matrix::matrix(std::size_t n, std::size_t m, int defaultval) {
    N = n; 
    M = m;
    arr = new int*[N];

    for (std::size_t i = 0; i < N; i++) {
        arr[i] = new int[M];
        for (std::size_t j = 0; j < M; j++) {
            arr[i][j] = defaultval;
        }
    }
}

//copy constructor
matrix::matrix(const matrix &M1) {
    N = M1.N;
    M = M1.M;

    // copy entire array
    arr = new int*[N];
    for (std::size_t i = 0; i < N; i++) {
        arr[i] = new int[M];
        for (std::size_t j = 0; j < M; j++) {
            arr[i][j] = M1.arr[i][j];
        }
    }
}

// destructor
matrix::~matrix() {
   if (arr) {
        for (std::size_t i = 0; i < N; ++i)
            delete[] arr[i];
        delete[] arr;
    }
    arr = NULL;
}

// overloaded assignment operator
matrix& matrix::operator=(const matrix &M1) { 
    N = M1.N;
    M = M1.M;

    // copy entire array
    arr = new int*[N];
    for (std::size_t i = 0; i < N; i++) {
        arr[i] = new int[M];
        for (std::size_t j = 0; j < M; j++) {
            arr[i][j] = M1.arr[i][j];
        }
    }
    return *this;
}

// overloaded multiplication operator to multiply a matrix by a scalar
//    each entry of the matrix is multiplied by the scalar
matrix& matrix::operator*(const int scalar) {
    for (size_t i = 0; i < getRows(); i++) {
        for (size_t j = 0; j < getCols(); j++) {
            arr[i][j] = arr[i][j] * scalar;
        }
    }
    return *this;
}

// takes in indices in the matrix and sets the
//  given number to that location
void matrix::setAt(std::size_t i, std::size_t j, int num) {
    if ( (i >= 0 && i < N) && (j >= 0 && j < M) )
        arr[i][j] = num;
}

// gets the number in the matrix at the specified indices
int matrix::getAt(std::size_t i, std::size_t j) {
    if ((i >= 0 && i < N) && (j >= 0 && j < M)) 
        return arr[i][j];
}

void matrix::print()const {
    for (std::size_t i = 0; i < N; i++) {
        for (std::size_t j = 0; j < M; j++)
            std::cout << std::left << std::setw(3) << arr[i][j] << " "; // works beacuse of overload in .h
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// adds two matricies together, A & B - the size of the matrices must match in each dimension
// if invalid, abort the addition and throw an exception
matrix matrix::add(matrix B) {
    // get dimensions of A & B - uncessary, but easier to read
    std::size_t rowsA = N;
    std::size_t rowsB = B.getRows();
    std::size_t colsA = M;
    std::size_t colsB = B.getCols();

    matrix C(rowsA, colsA, 0);

    if (rowsA != rowsB || colsA != colsB) {
        std::cout << "\nThe size of the matrices do not match. The addition process has stopped." << std::endl;
        return C; // return empty matrix
    } else {
        for (int i = 0; i < rowsA; i++) {
            for (int j = 0; j < colsA; j++) {
                C.arr[i][j] = arr[i][j] + B.arr[i][j];
            }
        }
    }
    return C;
}

// subtracts two matricies together, A & B - the size of the matrices must match in each dimension
// if invalid, abort the subtraction and throw an exception
matrix matrix::subtract(matrix B) {
    // get dimensions of A & B - uncessary, but easier to read
    std::size_t rowsA = N;
    std::size_t rowsB = B.getRows();
    std::size_t colsA = M;
    std::size_t colsB = B.getCols();

    matrix C(rowsA, colsA, 0);

    if (rowsA != rowsB || colsA != colsB) {
        std::cout << "\nThe size of the matrices do not match. The subtraction process has stopped." << std::endl;
        return C; // return empty matrix
    } else {
        for (int i = 0; i < rowsA; i++) {
            for (int j = 0; j < colsA; j++) {
                C.arr[i][j] = arr[i][j] - B.arr[i][j];
            }
        }
    }
    return C;
}

// multiplies two matricies together, A & B
// only valid when number of columns of A match the number of rows of B
// if invalid, abort the multiplication and throw an exception
matrix matrix::multiply(matrix B) {
    // get dimensions of A & B - uncessary, but easier to read
    std::size_t rowsA = N;
    std::size_t rowsB = B.getRows();
    std::size_t colsA = M;
    std::size_t colsB = B.getCols();

    matrix C(rowsA,colsB, 0); // nxm * mxk = > nxk

    if (colsA != rowsB) {
        std::cout << "\nThe size of the matrices are not compatible. The multiplication process has stopped." << std::endl;
        return C;
    } else {
        for (int i = 0; i < rowsA; i++) {
            for (int j = 0; j < colsB; j++) {
                int sum = 0;
                for (int k = 0; k < colsA; k++) {
                    sum += arr[i][k] * B.arr[k][j]; // 2 operations times rowsA(colsB)(colsA) 
                }
                C.arr[i][j] = sum;
            }
        }
    }
    return C;
}



         
// Kalyn Howes
// 3.4.21
// Lab 5
// Tests matrix class.

#include <iostream>
#include <stdlib.h> // for random numbers
// includes for timing :
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "matrix.h" // include matrix class
using namespace std;

void hardcode();
matrix diagonal(size_t, size_t);
matrix upperTri(size_t, size_t);
matrix lowerTri(size_t, size_t);
matrix identity(size_t, size_t);
matrix vect(size_t);
matrix random(size_t, size_t);

int main() {

    hardcode(); // hardcoded example with 2x2 matrix

    // ---------Different Matrix Types---------
    cout << "\n---- Types ----\n" << endl;
    size_t n = 5;
    size_t m = 5;

    // diagonal:
    matrix D(n ,m, 0);
    D = diagonal(n, m);
    cout << "\nDiagonal:" << endl;
    D.print();

    // upper triangular
    matrix uT(n, m, 0);
    uT = upperTri(n, m);
    cout << "\nUpper Triangular:" << endl;
    uT.print();

    // lower triangular
    matrix lT(n, m, 0);
    lT = lowerTri(n, m);
    cout << "\nLower Triangular:" << endl;
    lT.print();

    // identity
    matrix I(n, m, 0);
    I = identity(n, m);
    cout << "\nIdentity:" << endl;
    I.print();

    // vector
    matrix V(n, m, 0);
    V = vect(n);
    cout << "\nVector:" << endl;
    V.print();

    /* ---- TIMING ----:
    // create 2 matricies:
    size_t dim = 1000;
    matrix R1(dim,dim,0);
    R1 = random(dim,dim);
    matrix R2(dim,dim,0);
    R2 = random(dim,dim);
    // create result matrix:
    matrix result(dim,dim,0);

    cout << "Time starts now: " << endl;

	// The "auto" type determines the correct type at compile-time
	auto start = std::chrono::system_clock::now();

    // do operation
    result = R1.multiply(R2);
    //result = R1 * 10;

    auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = chrono::system_clock::to_time_t(end);
	cout << "\nfinished at " << ctime(&end_time) << "elapsed time: "
			<< elapsed_seconds.count() << "s\n";  
    */

    return 0;
}

// -------- FUNCTIONS --------

// creates a diagonal matrix :
//   all values on main diagonal are randomized
//   all values off the main diagonal are 0
matrix diagonal(size_t n, size_t m) {
    matrix M(n, m, 0);
    for (std::size_t i = 0; i < M.getRows(); i++) {
        for (std::size_t j = 0; j < M.getCols(); j++) {
            if (i == j)
                M.setAt(i, j, rand() % 100);
            else
                M.setAt(i, j, 0);
        }
    }
    return M;
}

// creates an upper triangular matrix :
//   all values below main diagonal are 0
//   all values on & above main diagonal are random
matrix upperTri(size_t n, size_t m) {
    matrix M(n, m, 0);
    for (std::size_t i = 0; i < M.getRows(); i++) {
        for (std::size_t j = 0; j < M.getCols(); j++) {
            if (i == j || i < j)
                M.setAt(i, j, rand() % 100);
            else
                M.setAt(i, j, 0);
        }
    }
    return M;
}

// creates a lower triangular matrix :
//   all values above main diagonal are 0
//   all values on & below main diagonal are random
matrix lowerTri(size_t n, size_t m) {
    matrix M(n, m, 0);
    for (std::size_t i = 0; i < M.getRows(); i++) {
        for (std::size_t j = 0; j < M.getCols(); j++) {
            if (i == j || i > j)
                M.setAt(i, j, rand() % 100);
            else
                M.setAt(i, j, 0);
        }
    }
    return M;
}

// creates an identity matrix :
//   all values on main diagonal are 1
//   all other values are 0
matrix identity(size_t n, size_t m) {
    matrix M(n, m, 0);
    for (std::size_t i = 0; i < M.getRows(); i++) {
        for (std::size_t j = 0; j < M.getCols(); j++) {
            if (i == j)
                M.setAt(i, j, 1);
            else
                M.setAt(i, j, 0);
        }
    }
    return M;
}

// creates a random vector, a n × 1 matrix
matrix vect(size_t n) {
    matrix M(n, 1, 0);
    for (std::size_t i = 0; i < M.getRows(); i++) {
        M.setAt(i, 0, rand() % 100);
    }
    return M;
}

// creates a random matrix
matrix random(size_t n, size_t m) {
    matrix M(n, m, 0);
    for (std::size_t i = 0; i < M.getRows(); i++) {
        for (std::size_t j = 0; j < M.getCols(); j++) {
            M.setAt(i, j, rand() % 100);
        }

    }
    return M;
}

// ---- HARDCODED EXAMPLE ----
// creates 2, nxn matricies to test addition, subtraction, & multiplication
void hardcode() { 
    // create a 2x2 test matrix:
    // (1, 2)
    // (3, 4)
    size_t n = 2;
    matrix M1(n, n, 0); // makes an nxm matrix full of 0s
    // hardcode values:
    M1.setAt(0,0,1);
    M1.setAt(0,1,2);
    M1.setAt(1,0,3);
    M1.setAt(1,1,4);
    cout << "Matrix 1:" << endl;
    M1.print();
    
    // create another 2x2 test matrix:
    // (4, 3)
    // (2, 1)
    n = 2;
    matrix M2(n, n, 0); // makes an nxm matrix full of 0s
    // hardcode values:
    M2.setAt(0,0,4);
    M2.setAt(0,1,3);
    M2.setAt(1,0,2);
    M2.setAt(1,1,1);
    cout << "Matrix 2:" << endl;
    M2.print();

    /* ---- TIMING ----:
    cout << "Time starts now: " << endl;

	// The "auto" type determines the correct type at compile-time
	auto start = std::chrono::system_clock::now();
    */
    
    // test addition - should be:
    // (5, 5)
    // (5, 5)
    matrix resultAdd(n, n, 0);
    resultAdd = M1.add(M2);
    cout << "Add:" << endl;
    resultAdd.print();
    
    // test subtraction - should be:
    // (-3, -1)
    // ( 1,  3)
    matrix resultSub(n, n, 0);
    resultSub = M1.subtract(M2);
    cout << "Subtract:" << endl;
    resultSub.print();

    // test multiplication - should be:
    // ( 8,  5)
    // (20, 13)
    matrix resultMul(n, n, 0);
    resultMul = M1.multiply(M2);
    cout << "Multiply:" << endl;
    resultMul.print();

     // test scalar - M1 * 10 should be:
     // (10, 20)
     // (30, 40)
     matrix resultS(n, n, 0);
     int scalar = 10;
     resultS = M1 * scalar;
     cout << "Scalar:" << endl;
     resultS.print();
     

    /*auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = chrono::system_clock::to_time_t(end);
	cout << "\nfinished at " << ctime(&end_time) << "elapsed time: "
			<< elapsed_seconds.count() << "s\n";
            */
}


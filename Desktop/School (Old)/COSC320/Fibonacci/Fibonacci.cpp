// Kalyn Howes
// 3.4.21
// Lab 5 - Bonus
// Implements the fast Fibonacci algorithm to compute the nth Fibonacci number
//      reports the time & number of arithmetic operations needed

#include <iostream>
// includes for timing
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "matrix.h" // include matrix class
using namespace std;

matrix fastPow(matrix, size_t, int&);
size_t fastFib(size_t, int&);
matrix identity(size_t, size_t);
void testPow(size_t);

int main() {

    // size_t dim = 2;
    // testPow(dim); // testing for fastpow with matrix - works

    size_t n = 1, result = 0;
    int ops = 0; // holds number of arithmetic operations

    // ---- TIMING ----
    cout << "Time starts now: " << endl;

	// The "auto" type determines the correct type at compile-time
	auto start = std::chrono::system_clock::now();
 
	result = fastFib(n, ops); // finds nth Fibonacci number
    cout << "\nThe " << n << "th Fibonacci number is " << result << "." << endl;
    cout << ops << " arithmetic operations were needed." << endl;

	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = chrono::system_clock::to_time_t(end);
	cout << "\nfinished at " << ctime(&end_time) << "elapsed time: "
			<< elapsed_seconds.count() << "s\n"; 

    return 0;
}

// fast pow - computes x^n, for x being an entire matrix
// 'ops' - holds number of arithmetic operations
// T(n) = theta(logn)
matrix fastPow(matrix M, size_t exp, int &ops) {
    matrix R(M.getRows(), M.getCols(), 0); // empty matrix for return
    matrix temp(M.getRows(), M.getCols(), 0); // empty temp matrix

    // if exponent is 0 or 1, return the identity matrix
    if (exp < 1) {
        return (identity(M.getRows(), M.getCols()));
    } else {
        temp = fastPow(M, exp / 2, ops);
        ops++; // bc of the division

         // is exponent even?
        if (exp % 2 == 0) {
            ops++; // bc of the %
            return (temp.multiply(temp));
            ops += (2 * (temp.getRows() * temp.getCols() * temp.getCols())); // multiply has: 2 times rowsA(colsB)(colsA) operations
        } else {
            ops++; // bc of the %
            R = temp.multiply(temp); // tmp * tmp
            ops += (2 * (temp.getRows() * temp.getCols() * temp.getCols())); // multiply has: 2 times rowsA(colsB)(colsA) operations
            ops += (2 * R.getRows() * M.getCols() * R.getCols()); // for multiply call below:
            return (R.multiply(M)); // * x
        }
    }
}

// fast Fibonacci - computes the nth Fibonacci number
// 'ops' - holds number of arithmetic operations
size_t fastFib(size_t n, int &ops) {
    matrix R(n,n,0); // holds returning matrix

    // let F = (0, 1) 
    //         (1, 1)
    matrix F(n,n,0);
    F.setAt(0,0,0);
    F.setAt(0,1,1);
    F.setAt(1,0,1);
    F.setAt(1,1,1);

    if (n == 0 || n == 1 ) {
        return n;
    } else {
        ops++; // bc of the n - 1 below
        R = fastPow(F, n - 1, ops); // theta(logn) bc 2x2 * 2x2 -> constant
    }

    return R[1][1];
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

void testPow(size_t dim) {
    matrix M(dim,dim,0);
    matrix R(dim,dim,0);
    int ops = 0;

    M.setAt(0,0,1);
    M.setAt(0,1,2);
    M.setAt(1,0,3);
    M.setAt(1,1,4);
    cout << "\nmatrix M:" << endl;
    M.print();

    R = fastPow(M, 3, ops);
    cout << "pow result: " << endl;
    R.print();
}

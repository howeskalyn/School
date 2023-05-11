/*
* Kalyn Howes
* 3.14.21
* Project 1
* BONUS - Testing Strassen's
*/

#include "matrix.h"
#include <iostream>
#include <ctime> // for random numbers
#include <chrono> // to time functions
#include <cstdlib>
using namespace std;

int main () {
    srand(time(NULL)); // reset

    // create test matrices & print it
    int dim = 2;

    matrix A(dim, dim, 0);
    A = A.random();
    cout << "\nMatrix A:" << endl;
    A.print();

    matrix B(dim, dim, 0);
    B = B.random();
    cout << "\nMatrix B:" << endl;
    B.print();

    // timing:
	// The "auto" type determines the correct type at compile-time
	auto start = std::chrono::system_clock::now();

    matrix M(dim, dim, 0);
    M = A.multiply(B);
    cout << "\nMultiplied:" << endl;
    M.print();

	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = chrono::system_clock::to_time_t(end);
	cout << "\nMatrix Multiplication finished at " << ctime(&end_time) << "elapsed time: "
			<< elapsed_seconds.count() << "\n";  
   
    cout << endl;
    matrix S(dim, dim, 0);
    S = A.StrassenHelp(A, B, false); // debug is off at the moment
    cout << "\nStrassen Multiplied:" << endl;
    S.print();

    return 0;
}

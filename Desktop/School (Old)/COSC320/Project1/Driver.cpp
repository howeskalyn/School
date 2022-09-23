/*
* Kalyn Howes
* 3.14.21
* Project 1
* I/O model using matrices - matrix testing driver program
* include timing and arithmetic operation counting
*/

#include "matrix.h"
#include <iostream>

// for timing
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

int main () {

    // create test matrix & print it
    int dim = 2;
    matrix A(dim, dim, 0);
    A = A.random();
    
    cout << "\nMatrix A:" << endl;
    A.print();

    // ------- TIMING --------
	cout << "Time starts now: " << endl;

	// The "auto" type determines the correct type at compile-time
	auto start = std::chrono::system_clock::now();

   // calculate inverse
    matrix AI(dim, dim, 0);
    int ops = 0;
    AI = A.inverse(A, ops);
    cout << "\nMatrix A Inverse:" << endl;
    AI.print();
    cout << "Number of operations: " << ops << endl;

    // check is matrix inverse is correct
    matrix ID(dim, dim, 0);
    ID = ID.identity();
    if ( ID.same(ID, A.multiply(AI)) ) {
        cout << "\nInverse is correct. A * A^−1 = In." << endl;
    } else 
        cout << "\nThere is most likely a rounding error." << endl;

	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = chrono::system_clock::to_time_t(end);
	cout << "\nfinished at " << ctime(&end_time) << "elapsed time: "
			<< elapsed_seconds.count() << "s\n";


    // ---- BONUS ----
    // showing determinant works:
    float det = 0;
    det = A.determinant(A);
    cout << "\nDeterminant: " << det << endl;

    return 0;
}
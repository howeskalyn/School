// Testing.cpp

#include "matrix.h"
#include <iostream>
using namespace std;

int main () {

    /* SYMMETRIC TESTING
    matrix A(4, 4, 0);
    A.setAt(0,0,1);
    A.setAt(0,1,0);
    A.setAt(0,2,1);
    A.setAt(0,3,2);

    A.setAt(1,0,0);
    A.setAt(1,1,2);
    A.setAt(1,2,2);
    A.setAt(1,3,4);

    A.setAt(2,0,1);
    A.setAt(2,1,2);
    A.setAt(2,2,3);
    A.setAt(2,3,4);
    
    A.setAt(3,0,2);
    A.setAt(3,1,4);
    A.setAt(3,2,4);
    A.setAt(3,3,4);
    cout << "\nMATRIX A:" << endl;
    A.print();

    matrix AI(A.getRows(), A.getCols(), 0);
    AI = A.inverse(A);
    cout << "\nA INVERSE:" << endl;
    AI.print();
    cout << "Determinant: " << A.determinant(A) << endl;
  
    // NON SYMMETRIC MATRIX TESTING:
    matrix B(2, 2, 0);
    B.setAt(0,0,4);
    B.setAt(0,1,7);
    B.setAt(1,0,2);
    B.setAt(1,1,6);
    cout << "\nMATRIX B:" << endl;
    B.print();
    
    matrix BI(B.getRows(), B.getCols(), 0);
    BI = B.inverse(B);
    cout << "\nB INVERSE:" << endl;
    BI.print();
    std::cout << "Determinant: " << B.determinant(B) << std::endl;

    // PADDING MATRIX TESTING:
    matrix P(3, 3, 0);
    P.setAt(0,0,2);
    P.setAt(0,1,3);
    P.setAt(0,2,1);
    P.setAt(1,0,-1);
    P.setAt(1,1,5);
    P.setAt(1,2,9);
    P.setAt(2,0,2);
    P.setAt(2,1,2);
    P.setAt(2,2,2);
    
    cout << "\nMATRIX P:" << endl;
    P.print();
    
    matrix PI(P.getRows(), P.getCols(), 0);
    PI = P.inverse(P);
    cout << "\nP INVERSE:" << endl;
    PI.print();
    std::cout << "Determinant: " << P.determinant(P) << std::endl;

    // NON SQUARE TESTING
    matrix S(2,3,0);
    S.inverse(S);
    */

    // ANOTHER MATRIX TO TEST STRASSENS
    /*matrix C(2, 2, 0);
    C.setAt(0,0,4);
    C.setAt(0,1,3);
    C.setAt(1,0,2);
    C.setAt(1,1,1);
    cout << "\nMATRIX B:" << endl;
    C.print();

    matrix res(2,2,0);
    res = B.Strassen(B, C);
    cout << "A * B (strassen): " << endl;
    res.print();*/

    // FILE STUFF
    matrix R(3,3,0);
    R.matrixFromFile("example_input.txt");
    //R.print();

}
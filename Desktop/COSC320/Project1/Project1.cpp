/*
* Kalyn Howes
* 3.14.21
* Project 1
* I/O model using matrices - determines how much total of a 
* single product will be needed to satisfy all demands of the economy
*/

#include "matrix.h"
#include <iostream>
#include <string>
#include <iomanip> // for printing nicely
#include <fstream> // files
using namespace std;

// char array holds './iomodel' in arr[0] & the file 'data' in arr[1]
int main (int argc, char *argv[]) {

    // ---- OPEN FILE ----
    // ex.) must pass in './iomodel' & 'data'
    if (argc != 2) {
        cout << "Must pass in 2 args." << endl;
        return 1;
    }

    ifstream inputFile;
    inputFile.open(argv[1]); // opens file name given in command line

    // check for file open errors
    if (! inputFile) {
      cerr << "There was an error opening the file." << endl;
      return -1;
   }

    // ---- DATA STORAGE FROM FILE ----
    int size = 0;
    // determine needed size of array - count each element
    while (inputFile) {
        string str;
        inputFile >> str;
        size++;
    }
    // reset to beginning of file:
    inputFile.clear();
    inputFile.seekg(0);

    string data[size]; // holds data being brought in - a line in each index
    int i = 0; // holds index of array
    // fill array to hold each element of file
    while (inputFile) {
        string str = "";
        inputFile >> str;
        data[i] = str;
        i++;
    }

    // dimension will be number of indices before "---"
    int dim = 0;
    for (int i = 0; i < size; i++) {
        if (data[i] == "---") 
            break;
        dim++;
    }

    // move data to 2 matrices:
    //     matrix A: nxn after "---" (dimensions: dim x dim)
    //     matrix V: vector for last section (dimensions: dim x 1)
    // (first "---" will be in arr[dim] & second will be in arr[dim * dim + dim + 1]

    // put data from file in an array to be put into matrix A
    // start loop at dim + 1
    int sizearrA = dim * dim;
    string arrA[sizearrA]; // array for matrix A (will be length of dimensions)
    int j = 0;
    for (int i = dim + 1; i < sizearrA + dim + 1; i++) {
        arrA[j] = data[i];
        j++;
    }

    // put vector data from file into array to be put in a vector
    // start loop at dim * dim + dim + 1
    int sizearrV = dim;
    string arrV[sizearrV]; // array for matrix V (will be length of dimensions)
    j = 0;
    int s = (dim * dim) + dim + 2; // starting index
    for (int i = s; i < dim + s; i++) {
        arrV[j] = data[i];
        j++;
    }

    matrix A(dim, dim, 0); // create matrix A with dimensions dim x dim
    matrix V(dim, 1, 0); // create matrix B with dimensions dim x 1 (vector)

    // fill matrix A - need stof
    int a = 0; // index to move through arrA
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            A.setAt(i, j, stof(arrA[a]) );
            a++;
        }
    }

    // fill matrix V - need stof
    int v = 0; // index to move through arrA
    for (int i = 0; i < dim; i++) {
        V.setAt(i, 0, stof(arrV[v]) );
        v++;
    }

    // ---- USING FORMULA TO FIND X ----
    // how much total of a single product will be needed to satisfy all demands of the economy
    //      we need only compute x = (In − A)^−1 * d
    matrix X(dim, 1, 0); // total of product needed to satisfy all demands
    matrix ID(dim, dim, 0); // stores identity matrix
    ID = ID.identity(); // make it the identity matrix
    matrix temp(dim, dim, 0);
    temp = ID.subtract(A);
    int ops = 0; // needed from other file
    temp = temp.inverse(temp, ops);

    // print results to user
    X = temp.multiply(V);
    cout << "\nAmount of each product needed: " << endl;
    for (int i = 0; i < dim; i++) {
        cout << left << setw(12) << data[i] << right << setw(12) << setprecision(5) << X[i][0] << endl;
    }

    // determinant:
    // cout << A.determinant(A) << endl;

    // clean up
    cout << endl;
    inputFile.close();
    
    return 0;
}
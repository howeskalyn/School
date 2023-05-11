// Kalyn Howes
// 3.4.21
// Lab 5
// Matrix class, matrix.cpp

#include "matrix.h"
#include <iostream>
#include <stdlib.h> // for random numbers
#include <ctime> // for random numbers
#include <iomanip> // for setw
#include <fstream> // for files
#include <chrono> // to time functions
#include <math.h> // for pow

// --------- SET UP & DESTROY --------
// constructor - takes in matrix dimensions & a default value
matrix::matrix(std::size_t n, std::size_t m, float defaultval) {
    N = n; 
    M = m;
    arr = new float*[N];

    for (std::size_t i = 0; i < N; i++) {
        arr[i] = new float[M];
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
    arr = new float*[N];
    for (std::size_t i = 0; i < N; i++) {
        arr[i] = new float[M];
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

// -------- OVERLOADS --------
// overloaded assignment operator
matrix& matrix::operator=(const matrix &M1) { 
    N = M1.N;
    M = M1.M;

    // copy entire array
    arr = new float*[N];
    for (std::size_t i = 0; i < N; i++) {
        arr[i] = new float[M];
        for (std::size_t j = 0; j < M; j++) {
            arr[i][j] = M1.arr[i][j];
        }
    }
    return *this;
}

// overloaded multiplication operator to multiply a matrix by a scalar
//    each entry of the matrix is multiplied by the scalar
matrix matrix::operator*(float scalar) {
    matrix R = *this;
    for (std::size_t i = 0; i < getRows(); i++) {
        for (std::size_t j = 0; j < getCols(); j++) {
            R.arr[i][j] *= scalar;
        }
    }
    return R;
}

// -------- HELPER FUNCTIONS --------
// takes in indices in the matrix and sets the
//  given number to that location
void matrix::setAt(std::size_t i, std::size_t j, float num) {
    if ( (i >= 0 && i < N) && (j >= 0 && j < M) )
        arr[i][j] = num;
}

// gets the number in the matrix at the specified indices
float matrix::getAt(std::size_t i, std::size_t j) {
    if ((i >= 0 && i < N) && (j >= 0 && j < M)) 
        return arr[i][j];
    return 0;
}

// appends 2 matrices together horizontally
// the first matrix taken in will be the right & the second the left
matrix matrix::appendH(matrix right, matrix left) {
    matrix result(right.getRows(), left.getCols() + right.getCols(), 0);

    if (right.getRows() == left.getRows()) {
        for (std::size_t i = 0; i < right.getRows(); i++) {
            for (std::size_t j = 0; j < left.getCols() + right.getCols(); j++) {
                if (j < left.getCols())
                    result.setAt(i, j, left.getAt(i, j));
                else
                    result.setAt(i, j, right.getAt(i, j - left.getCols()));
            }
        }
        return result;
    }
    return result; // empty
}

// appends 2 matrices together vertically
// the first matrix taken in will be the top & the second the bottom
matrix matrix::appendV(matrix top, matrix bottom) {
    matrix result(top.getRows() + bottom.getRows(), top.getCols(), 0);

    if (top.getCols() == bottom.getCols()) {
        for (std::size_t i = 0; i < (top.getRows() + bottom.getRows()); i++) {
            for (std::size_t j = 0; j < top.getCols(); j++) {
                if (i < top.getRows())
                    result.setAt(i, j, top.getAt(i, j));
                else
                    result.setAt(i, j, bottom.getAt(i - top.getRows(), j));
            }
        }
        return result;
    }
    return result; // empty
}

// prints the matrix
void matrix::print()const {
    for (std::size_t i = 0; i < N; i++) {
        for (std::size_t j = 0; j < M; j++)
            std::cout << std::left << std::setw(3) << arr[i][j] << " "; // works beacuse of overload in .h
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


// -------- CHECKS --------
// checks if 2 matrices are the same
//  (each entry must be equal)
bool matrix::same(matrix P, matrix K) {

    // check dimensions first
    if ( (P.getRows() != K.getRows()) || (P.getCols() != K.getCols()) ) {
        return false;
    } else {
        for (std::size_t i = 0; i < P.getRows(); i++) {
            for (std::size_t j = 0; j < P.getCols(); j++) {
                if (P.getAt(i, j) != K.getAt(i, j)) { // if they are not equal
                    return false;
                }
            }
        }   
    }
    return true;
}

// checks if a number of a power of 2
bool matrix::isPower2(int n) {
    bool ret = false;
    if (n > 0) {
        while (n % 2 == 0)
            n /= 2;

        if (n == 1) {
            //std::cout << "Number is a power of 2. " << std::endl;
            ret =true;
        }
    }

    if (n == 0 || n != 1) {
        //std::cout << "Number is NOT a power of 2." << std::endl;
        ret = false;
    }
    return ret;
}

// checks if a matrix is invertible by 
//      checking if it is square & symmetric
bool matrix::isInvertible(matrix A) {
    bool ret = true;

    // check 1
    if (!isSquare(A) || !isSymmetric(A)) {
        std::cout << "The matrix is NOT invertible. It is not square and/or symmetric." << std::endl;
        ret = false;
    }

    // bonus check! (with determinant):
    if (determinant(A) == 0) {
        std::cout << "The matrix is NOT invertible. It's determinant is 0." << std::endl;
        ret = false;
    }
    return ret;
}

// checks if a matrix is square by looking at the dimensions
bool matrix::isSquare(matrix A) {
    if (A.getRows() != A.getCols()) {
        //std::cout << "The matrix is NOT square." << std::endl;
        return false;
    } else
        return true;
}

// checks if a matrix is symmetric
//      it is if A^T = A
bool matrix::isSymmetric(matrix A) {
    if (! same(A.transpose(A), A) ) {
        //std::cout << "The matrix is NOT symmetric." << std::endl;
        return false;
    } else
        return true;
}


// -------- OPERATIONS --------
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
        for (std::size_t i = 0; i < rowsA; i++) {
            for (std::size_t j = 0; j < colsA; j++) {
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
        for (std::size_t i = 0; i < rowsA; i++) {
            for (std::size_t j = 0; j < colsA; j++) {
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
                float sum = 0;
                for (int k = 0; k < colsA; k++) {
                    sum += arr[i][k] * B.arr[k][j];
                }
                C.arr[i][j] = sum;
            }
        }
    }
    return C;
}

// returns the transpose of the given matrix
// if input matrix is n x m, the returning matrix will be m x n
matrix matrix::transpose(matrix P) {
    matrix R(P.getCols(), P.getRows(), 0); // empty matrix of correct size for transpose

    for (std::size_t i = 0; i < P.getCols(); i++) {
        for(std::size_t j = 0; j < P.getRows(); j++) {
            R.setAt(i, j, P.getAt(j, i));
            //R[i][j] = arr[j][i];
        }
    }
    return R;
}

// returns the inverse of the given matrix, A, using a specific algorithm
// (matrix must be padded if the dimensions arent a power of 2)
matrix matrix::inverse(matrix A, int &ops) {

    matrix AI(A.getRows(), A.getCols(), 0); // holds whole inverse/return matrix

    // if not square return 0 
    if (! isSquare(A)) {
        ops++;
        std::cout << "\nReturning 0 matrix." << std::endl;
        return AI; // return empty matrix
    }
        
    // 0. Pad matrix as: A -> (A  0) (0, Ik) & n + k must be a power of 2 (n = 2^k)
    // ex) 3x3 goes to 4x4: k = 1 & n = 3
    //      top left is n x n, 0 matrix top-right is n x k
    //      bottom-left 0 matrix is k x n, Ik is k x k
    bool padded = false;
    if (! isPower2(A.getRows())) {
        ops++;
        padded = true;
        // must pad to make power of 2
        int next2 = nextPower2(A.getRows()); // find next power of 2
        int k = next2 - A.getRows(); // k will be the next power of 2 minus n
        ops++;

        matrix P(A.getRows() + k, A.getCols() + k, 0); // padded matrix will be size n + k

        // three needed parts to pad
        matrix zTop(A.getRows(), k, 0); // zero matrix on top-right is size n x k
        matrix zBot(k, A.getCols(), 0); // zero matrix on bottom-left is k x n
        matrix ID(k, k, 0); // identity matrix is k x k
        ID = ID.identity();

        // find top & bottom of padded matrix & append vertically
        matrix top(A.getRows(), A.getCols() + k, 0); // holds top of padded matrix: n x (n+k)
        matrix bottom(k, A.getCols() + k, 0); // holds bottom of padded matrix k x (n+k)
        top = appendH(zTop, A);

        bottom = appendH(ID, zBot);

        P = appendV(top, bottom);
        
        matrix PI(P.getRows(), P.getCols(), 0);
        PI = inverse(P, ops); // return inverse on padded matrix
    
        // return top left only....
        matrix topLeft(A.getRows(), A.getCols(), 0); // holds return matrix of padded
        // put only top left in return matrix
        for (std::size_t i = 0; i < A.getRows(); i++) {
            for (std::size_t j = 0; j < A.getCols(); j++) {
                // top half:
                if (i < A.getRows()) {
                    ops++;
                // top left side
                    if (j < A.getRows()) {
                    ops++;
                    topLeft.setAt(i, j, PI.getAt(i, j)); 
                    }
                }
            }
        }
        // return top-left only
        return topLeft;
    }

    // if only a 1x1 matrix, return reciprocal of self
    if (A.getRows() == 1 && A.getCols() == 1) {
        ops++;
        // check for divison by 0
        matrix recip(1, 1, 0);
        if (A.getAt(0,0) == 0) { // if the only element is 0
            return recip;
        } else { // otherwise find reciprocal
            ops++;
            float r = (float)1 / (float)A.getAt(0,0);
            recip.setAt(0, 0, r); // adds the reciprocal of the single element to return matrix
            return recip;
        }

        // if a 2x2 has a 0 in the 0,0 spot, use determinant (special case...)
        // using formula: 1/det * (d -b)
        //                        (-c a)
    } else if ( (A.getRows() == 2 && A.getCols() == 2) && A.getAt(0,0) == 0) {
        float det = determinant(A); // holds determinant
        det = (float)1 / (float)det;
        ops++;

        matrix r(A.getRows(), A.getCols(), 0); // holds return/inverse matrix
        r.setAt(0,0, A.getAt(1,1)); // sets 0,0 to d of matrix A
        r.setAt(0,1, A.getAt(0,1) * (-1)); // sets 0,1 to -b of matrix A
        r.setAt(1,0, A.getAt(1,0) * (-1)); // sets 1,0 to -c of matrix A
        r.setAt(1,1, A.getAt(0,0)); // sets 1,1 to a of matrix A

        return(r * det); // return new matrix times 1/det
        
        // if not symmetric, force it & return
    } else if (! isSymmetric(A)) { 
        ops++;
        // A−^1 = ( (A^T)(A) )−^1 (A^T)
        matrix AT(A.getRows(), A.getCols(), 0); // holds A^T
        AT = A.transpose(A); 
        matrix ATA(A.getRows(), A.getCols(), 0); // holds (A^T)(A)
        ATA = AT.multiply(A); // (A^T)(A)

        return ( (ATA.inverse(ATA, ops) ).multiply(AT) ); // return (A.transpose()A).inverse() * A.transpose()

        // otherwise, start algorithm:
    } else {
        // 1. Divide A into submatrices: A = (B C^T) (C D)
        // B & D are symmetric - all are (n/2) × (n/2)
        int dim = A.getRows() / 2; // find (n/2)
        matrix B(dim, dim, 0); 
        matrix D(dim, dim, 0);
        matrix C(dim, dim, 0);
        matrix CT(dim, dim, 0); 

        // split into 4:
        for (std::size_t i = 0; i < A.getRows(); i++) {
            for (std::size_t j = 0; j < A.getCols(); j++) {
                //top half:
                if (i < dim) {
                    ops++;
                // B - top left side
                    if (j < dim) {
                        ops++;
                        B.setAt(i, j, A.getAt(i, j));
                    }
                    // CT - top right side
                    else {
                        ops++;
                        CT.setAt(i, j - dim, A.getAt(i, j));
                    }
                }
                // bottom half
                else {
                    // C - bottom left side
                    if (j < dim) {
                        ops++;
                        ops++;
                        C.setAt(i - dim, j, A.getAt(i, j));
                    }
                    // D - bottom right side
                    else {
                        ops++;
                        D.setAt(i - dim, j - dim, A.getAt(i, j));
                    }
                }
            }
        } 
        
        // --------------------------------------------------
        // 2. Recursively compute B^−1 
        matrix BI(dim, dim, 0); // inverse of B will be same size as B
        BI = inverse(B, ops);

        // 3. Compute W = C B^−1 and W^T = B^-1 C^T 
        matrix W(dim, dim, 0); 
        matrix WT(dim, dim, 0); 
        W = C.multiply(BI);
        WT = BI.multiply(CT);
        ops++;
        ops++;

        // 4. Compute X = W C^T
        matrix X(dim, dim, 0); 
        X = W.multiply(CT);
        ops++;

        // 5. Compute S = D − X
        matrix S(dim, dim, 0); 
        S = D.subtract(X);
        ops++;

        // 6. Recursively compute V = S^−1
        matrix V(dim, dim, 0);
        V = inverse(S, ops);

        // 7. Compute Y = V W and Y^T
        matrix Y(dim, dim, 0);
        Y = V.multiply(W);
        ops++;
        matrix YT(dim, dim, 0);
        YT = transpose(Y);

        // 8.Set T = −Y^T and U = −Y
        matrix T(dim, dim, 0);
        T = YT * (-1); // scalar multiplication by -1
        ops++;
        matrix U(dim, dim, 0); 
        U = Y * (-1); // scalar multiplication by -1
        ops++;

        // 9. Compute Z = W^T Y and set R = B^−1 + Z
        matrix Z(dim, dim, 0);
        Z = WT.multiply(Y);
        ops++;
        matrix R(dim, dim, 0); 
        R = BI.add(Z);
        ops++;

        // 10. Assemble the inverse of A as: A^-1 = (R T) (U V)
        matrix AI1(dim / 2, dim, 0); // holds (R T)
        matrix AI2(dim / 2, dim, 0); // holds (U V)
        AI1 = R.appendH(T, R); // T on right & R on left
        AI2 = U.appendH(V, U); // V on right & U on left
        AI = AI1.appendV(AI1, AI2); // AI1 on top & AI2 on bottom
    }

    /* check if inverse was done properly: yes if AA^-1 = ID
    // create identity matrix
    matrix ID(AI.getRows(), AI.getCols(), 0);
    ID = ID.identity();

    if (same(A.multiply(AI), ID)) // multiply A and its inverse - if same as identity we're good!
        std::cout << "Inverse checks out." << std::endl;
    else
        std::cout << "Something is wrong with the inverse." << std::endl;
    */

    return AI;
}

// gets the next power of 2 from n
int matrix::nextPower2(int n) {
	long int r = 1; // holds result

	// until number is greater than n
	while(r <= n) {
		// number will be left shifted by 1 place in each iteration (binary)
		r = r << 1;
	}
	return r;
}


// ------ BONUS ------ 
// calculates the cofactor matrix
// ith row & jth column is not included in new matrix
matrix matrix::cofactor(std::size_t i, std::size_t j, matrix M) {
    matrix temp(M.getRows() - 1, M.getCols() - 1, 0); // return matrix that is one dimension smaller
    
    for (std::size_t k = 0, r = 0; k < M.getRows(); k++, r++) {
        if (k == i) // row being removed
            r--;
        else {
            for (std::size_t l = 0, c = 0; l < M.getCols(); l++, c++) {
                if (l == j) // column being removed
                    c--;
                else
                    temp.setAt(r, c, M.getAt(k, l));
            }
        }
    }
    return temp;
}

// ------ BONUS ------ 
// recursive function for finding the determinant of matrix
// the determinant is returned
float matrix::determinant(matrix M) {

    float det = 0;
	if (isSquare(M)) {
		if (M.getRows() == 2)
			det = ((M.getAt(0,0) * M.getAt(1, 1)) - (M.getAt(0, 1) * M.getAt(1, 0)));
		else //calculate deteminant recursively
			for (int i = 0; i < M.getCols(); i++)
				det += pow(-1, i) * (M.getAt(0, i) * determinant((cofactor(0, i, M))));
	}
	else
		std::cout << "Not a square matrix, the determinant is undefined." << std::endl;

	return det;
}

// -------- BUILDING SPECIFIC MATRIX TYPES --------
// creates a diagonal matrix :
//   all values on main diagonal are randomized
//   all values off the main diagonal are 0
matrix matrix::diagonal() {
    matrix R(N, M, 0);
    for (std::size_t i = 0; i < R.getRows(); i++) {
        for (std::size_t j = 0; j < R.getCols(); j++) {
            if (i == j)
                R.setAt(i, j, rand() % 100);
            else
                R.setAt(i, j, 0);
        }
    }
    return R;
}

// creates an upper triangular matrix :
//   all values below main diagonal are 0
//   all values on & above main diagonal are random
matrix matrix::upperTri() {
    matrix R(N, M, 0);
    for (std::size_t i = 0; i < R.getRows(); i++) {
        for (std::size_t j = 0; j < R.getCols(); j++) {
            if (i == j || i < j)
                R.setAt(i, j, rand() % 100);
            else
                R.setAt(i, j, 0);
        }
    }
    return R;
}

// creates a lower triangular matrix :
//   all values above main diagonal are 0
//   all values on & below main diagonal are random
matrix matrix::lowerTri() {
    matrix R(N, M, 0);
    for (std::size_t i = 0; i < R.getRows(); i++) {
        for (std::size_t j = 0; j < R.getCols(); j++) {
            if (i == j || i > j)
                R.setAt(i, j, rand() % 100);
            else
                R.setAt(i, j, 0);
        }
    }
    return R;
}

// creates an identity matrix :
//   all values on main diagonal are 1
//   all other values are 0
matrix matrix::identity() {
    matrix R(N, M, 0);
    for (std::size_t i = 0; i < R.getRows(); i++) {
        for (std::size_t j = 0; j < R.getCols(); j++) {
            if (i == j)
                R.setAt(i, j, 1);
            else
                R.setAt(i, j, 0);
        }
    }
    return R;
}

// creates a random vector, a n × 1 matrix
matrix matrix::vect() {
    matrix R(N, 1, 0);
    for (std::size_t i = 0; i < R.getRows(); i++) {
        R.setAt(i, 0, rand() % 100);
    }
    return R;
}

// creates a random matrix
matrix matrix::random() {
    matrix R(N, M, 0);
    for (std::size_t i = 0; i < R.getRows(); i++) {
        for (std::size_t j = 0; j < R.getCols(); j++) {
            R.setAt(i, j, rand() % 10);
        }
    }
    return R;
}

// resizing method - used in strassens
void matrix::resize(std::size_t newr, std::size_t newc, float defaultval) {
    float** temp;
    temp = new float* [newr];

    for (std::size_t i = 0; i < newr; i++) {
        temp[i] = new float[newc];
        for (std::size_t j = 0; j < newc; j++) {
            if (i < N && j < M)
                temp[i][j] = arr[i][j];
            else
                temp[i][j] = defaultval;
        }
    }
    // delete matrix:
    if (arr) {
        for (std::size_t i = 0; i < N; ++i)
            delete[] arr[i];
        delete[] arr;
    }
    arr = NULL;

    // reset
    M = newc;
    N = newr;
    arr = temp;
}

// for padding purposes with Strassens
// takes in 2 matrices to be multiplied and a boolean for debugging
matrix matrix::StrassenHelp(matrix A, matrix B, bool debug) {
    //std::cout << "A.Cols == B.Rows" << std::endl;

    if (A.getCols() != B.getRows()) {
        std::cout << "The size of the matricies are not compatible. The matrix multiplication process has stopped." << std::endl;
        std::cout << "Returning a default matrix." << std::endl;
        matrix C(1, 1, 0); // nxm * mxk = > nxk
        return C;
    } else {
        //resultant rows and columns. Resize the Result matrix to these dimensions at the end.
        std::size_t rows = A.getRows();
        std::size_t cols = B.getCols();

        //start timer
        auto start = std::chrono::system_clock::now();

        matrix C = Strassen(A, B, debug); 

        //end time
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        //std::cout << "Matrix A dims: " << A.getRows() << " x " << A.getCols() << "\n";
        //std::cout << "Matrix B dims: " << B.getRows() << " x " << B.getCols() << "\n";
        std::cout << "Strassen Time (to pad and multiply): " << elapsed_seconds.count() << "\n";

        C.resize(rows, cols, 0);

        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "Total Time (with removing padding): " << elapsed_seconds.count() << "\n";
        
        return C;
    }
}

// Strassens algorithm implementation
// takes in 2 matrices to be multiplied and a boolean for debugging
matrix matrix::Strassen(matrix A, matrix B, bool debug) {
    if(debug)
        std::cout << "Youre in Strassens function!" << std::endl; // makes it here
    
    // dimensions of A & B need to be the same - if both square and rows match, they also need to be of power of 2
    if (!((A.getRows() == B.getRows()) && (isPower2(A.getRows())) && (A.isSquare(A) && B.isSquare(B)))) {
        if (debug)
            std::cout << "Youre in the pad statment!" << std::endl; // crashed before here

        // use large of 2 dimensions:
        int newdims = 0;
        if (nextPower2(A.getRows()) >= nextPower2(B.getRows()))
            newdims = nextPower2(A.getRows());
        else
            newdims = nextPower2(B.getRows());

        if (debug)
            std::cout << "New dimension: " << newdims << std::endl;

        // make matrices have same dimensions & be power of 2
        // resize with defualt value as 0
        A.resize(newdims, newdims, 0);
        B.resize(newdims, newdims, 0);
        if (debug) 
            std::cout << "Either the dims didn't match or they were not powers of 2. This is fixed now!" << std::endl;

        if (debug) {
            std::cout << "New A:" << std::endl;
            A.print();
            std::cout << "New B:" << std::endl;
            B.print();
        }
    }
    // Algorithm:
    /* 7 new matrices by splitting the current matrix into 4 new matrices (11, 12, 21, 22):
    * M1 = (A11 + A22)(B11 + B12)
    * M2 = (A21 + A22)(B11)
    * M3 = A11(B12 - B22)
    * M4 = A22(B21 - B11)
    * M5 = (A11 + A12)(B22)
    * M6 = (A21 - A11)(B11 + B12)
    * M7 = (A12 - A22)(B21 + B22)
    *
    * end recurion when a 1x1 (when all 4 new 2x2 are 1x1)
    */
        
    // split matrix A & B into 4 new each:
    matrix A11(A.getRows() / 2, A.getCols() / 2, 0);
    matrix A12(A.getRows() / 2, A.getCols() / 2, 0);
    matrix A21(A.getRows() / 2, A.getCols() / 2, 0);
    matrix A22(A.getRows() / 2, A.getCols() / 2, 0);

    matrix B11(B.getRows() / 2, B.getCols() / 2, 0);
    matrix B12(B.getRows() / 2, B.getCols() / 2, 0);
    matrix B21(B.getRows() / 2, B.getCols() / 2, 0);
    matrix B22(B.getRows() / 2, B.getCols() / 2, 0);

    for (int i = 0; i < A.getRows(); i++) {
        for (int j = 0; j < A.getCols(); j++) {
            // top half (A11, A12)
            if (i < A.getRows() / 2) {
                // A11 - left side
                if (j < A.getCols() / 2) {
                    A11.setAt(i, j, A.getAt(i, j));
                    B11.setAt(i, j, B.getAt(i, j));
                }
                // A12 - right side
                else {
                    A12.setAt(i, j - (A.getCols() / 2), A.getAt(i, j));
                    B12.setAt(i, j - (A.getCols() / 2), B.getAt(i, j));
                }
            }
            // bottom half
            else {
                // A21 - left side
                if (j < A.getCols() / 2) {
                    A21.setAt(i - (A.getRows() / 2), j, A.getAt(i, j));
                    B21.setAt(i - (A.getRows() / 2), j, B.getAt(i, j));
                }
                // A22 - right side
                else {
                    A22.setAt(i - (A.getRows() / 2), j - (A.getCols() / 2), A.getAt(i, j));
                    B22.setAt(i - (A.getRows() / 2), j - (A.getCols() / 2), B.getAt(i, j));
                }   
            }
        }
    }

    if (debug) {
        std::cout << "A11:  " << std::endl;
        A11.print();
        std::cout << "A12:  " << std::endl;
        A12.print();
        std::cout << "A21:  " << std::endl;
        A21.print();
        std::cout << "A22:  " << std::endl;
        A22.print();

        std::cout << "B11:  " << std::endl;
        B11.print();
        std::cout << "B12:  " << std::endl;
        B12.print();
        std::cout << "B21:  " << std::endl;
        B21.print();
        std::cout << "B22:  " << std::endl;
        B22.print();
    }

    // if not at base case, 'Strassen' it again
    // this is the source of the seg fault...
    if ( (A.getRows() / 2) >= 2) {
        matrix M1 = Strassen( A11.add(A22), B11.add(B22), false);
        matrix M2 = Strassen( A21.add(A22), B11, false);
        matrix M3 = Strassen( A11, B12.subtract(B22), false);
        matrix M4 = Strassen( A22, B21.subtract(B11), false);
        matrix M5 = Strassen( A11.add(A12), B22, false);   
        matrix M6 = Strassen( A21.subtract(A11), B11.add(B12), false);
        matrix M7 = Strassen( A12.subtract(A22), B21.add(B22), false);

        if (debug) {
            std::cout << "7 M's: " << std::endl;
            M1.print();
            M2.print();
            M3.print();
            M4.print();
            M5.print();
            M6.print();
            M7.print(); 
        }

        matrix C11 = M1.add(M4).subtract(M5).add(M7); // M1 + M4 - M5 + M7;
        matrix C12 = M3.add(M5); // M3 + M5;
        matrix C21 = M2.add(M4); // M2 + M4;
        matrix C22 = M1.subtract(M2).add(M3).add(M6); // M1 - M2 + M3 + M6;

        // function takes in (right, left)... should be fixed to take in (left, right) but thats okay
        matrix top = appendH(C12, C11);
        matrix bot = appendH(C22, C21);
        matrix R = appendV(top, bot);

        if (debug) {
            std::cout << "Return Matrix, R:" << std::endl;
            R.print();
        }
        return R;

        
    // if base case - matrices are 1x1
    } else { 
        // note: current A/B 11, 12, 21, 22 are 1x1 so they are just values, not matrices
        float M1 = (A11.getAt(0, 0) + A22.getAt(0, 0)) * (B11.getAt(0, 0) + B22.getAt(0, 0));
        float M2 = (A21.getAt(0, 0) + A22.getAt(0, 0)) * (B11.getAt(0, 0));
        float M3 = (A11.getAt(0, 0)) * (B12.getAt(0, 0) - B22.getAt(0, 0));
        float M4 = (A22.getAt(0, 0)) * (B21.getAt(0, 0) - B11.getAt(0, 0));
        float M5 = (A11.getAt(0, 0) + A12.getAt(0, 0)) * (B22.getAt(0, 0));
        float M6 = (A21.getAt(0, 0) - A11.getAt(0, 0)) * (B11.getAt(0, 0) + B12.getAt(0, 0));
        float M7 = (A12.getAt(0, 0) - A22.getAt(0, 0)) * (B21.getAt(0, 0) + B22.getAt(0, 0));

        float C11 = M1 + M4 - M5 + M7;
        float C12 = M3 + M5;
        float C21 = M2 + M4;
        float C22 = M1 - M2 + M3 + M6;

        // create and set return matrix
        matrix R(2, 2, 0);
        R.setAt(0, 0, C11);
        R.setAt(0, 1, C12);
        R.setAt(1, 0, C21);
        R.setAt(1, 1, C22);

        if (debug) {
            std::cout << "BASE CASE: Return Matrix, R:" << std::endl;
            R.print();
        }

        return R;
    }
}

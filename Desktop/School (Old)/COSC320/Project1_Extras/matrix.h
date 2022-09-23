// Kalyn Howes
// 3.4.21
// Lab 5
// Matrix class, matrix.h (header file)

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class matrix {
    private:
        std::size_t N; // rows
        std::size_t M; // columns
        float **arr; // storage of the array elements should use dynamic memory


    public:
        matrix(std::size_t, std::size_t, float); // constructor
        matrix(const matrix&); // copy constructor
        ~matrix(); // destructor

        //overloads
        matrix& operator=(const matrix&); // assignment overload
        float* operator[](const int i)  { return arr[i]; } // index overload
        matrix operator*(float); // scalar multiplication overload
        friend std::ostream& operator<<(std::ostream&, const matrix&); // print overload

        // helpers (sets & gets & stuff)
        void setAt(std::size_t, std::size_t, float);
        float getAt(std::size_t, std::size_t);
        std::size_t getRows() { return N; }
        std::size_t getCols() { return M; }
        matrix appendH(matrix, matrix); // right & left are switched oops
        matrix appendV(matrix, matrix);
        void print() const; // prints matrix

        // checks
        bool same(matrix, matrix); // checks if 2 matrices are the same
        bool isPower2(int);
        bool isInvertible(matrix);
        bool isSquare(matrix);
        bool isSymmetric(matrix);

        // matrix operations
        matrix add(matrix);
        matrix subtract(matrix);
        matrix multiply(matrix);
        matrix transpose(matrix);
        matrix inverse(matrix, int&);
        int nextPower2(int);

        // --- BONUS ---
        matrix cofactor(std::size_t, std::size_t, matrix);
        int determinant(matrix);

        // building certain matrix types
        matrix diagonal();
        matrix upperTri();
        matrix lowerTri();
        matrix identity();
        matrix vect();
        matrix random();

        /* --- BONUS --- Strassens
        matrix Strassen(matrix, matrix);
        void resize(int, int, float);
        */

};

std::ostream& operator<< (std::ostream& os, const matrix &m) {
    m.print();
    return os;
}

#endif
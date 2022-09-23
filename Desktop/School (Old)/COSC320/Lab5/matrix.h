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
        int **arr; // storage of the array elements should use dynamic memory


    public:
        matrix(std::size_t, std::size_t, int); // constructor
        matrix(const matrix&); // copy constructor
        ~matrix(); // destructor

        //overloads
        matrix& operator=(const matrix&); // assignment overload
        int* operator[](const int i)  { return arr[i]; } // index overload
        matrix& operator*(const int); // scalar multiplication overload

        // sets & gets
        void setAt(std::size_t, std::size_t, int);
        int getAt(std::size_t, std::size_t);
        std::size_t getRows() { return N; }
        std::size_t getCols() { return M; }

        void print() const; // prints matrix
        // print overload
        friend std::ostream& operator<<(std::ostream&, const matrix&);

        // addition, subtraction, and multiplication of matrices
        matrix add(matrix);
        matrix subtract(matrix);
        matrix multiply(matrix);

};

std::ostream& operator<< (std::ostream& os, const matrix &m) {
    m.print();
    return os;
}

#endif
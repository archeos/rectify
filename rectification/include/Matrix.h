/***********************************************
Class Matrix.h with their declarations and implementations
***********************************************/

#ifndef _MATRIX_H
#define _MATRIX_H 1

#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>

class Matrix
{
public:
    Matrix(int lines, int columns);
    virtual ~Matrix();

    int lines() const;
    int columns() const;
    const std::string& name() const;

    long double value(int line, int column) const; // returns a value of position x line array column
    void setValue(int line, int column, long double value); // Assigns a value to a position val line x matrix column

    void show(); // Displays the array
    void report(); // Displays the array in report
    void fillrand(int lim); // (for testing) Fills the array with random values within a range of 0 atlim
    void identity(); // transforms the matrix identity
    Matrix sum(Matrix m1); // Sum of two matrices of the same size
    Matrix subtract(Matrix m1); // Subtraction between two matrices of the same size
    float determinant(); // Determinant of a matrix
    Matrix product(Matrix m1); // Returns the product of the owner of the matrix method and the matrix m1
    Matrix scalar_product(double pesc);
    Matrix transpose(); // Returns the transpose of the matrix
    Matrix invert(int size); // Returns the inverse of the matrix
    Matrix copy(); // Returns a copy of the matrix
    void fillin(); // (for testing) Fills values one by one in the matrix
    //void showGui(QTable* tabela); // Displays the array in a QT QTable object

private:
    std::vector<std::vector<long double> > m;  // Matrix data.
    int lines_, columns_; // Matrix dimensions.
    std::string name_; // Name of the matrix.
};

#endif // _MATRIX_H

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
    Matrix(int linha, int coluna);
    virtual ~Matrix();

    int maxlin() const;
    int maxcol() const;
    const std::string& name() const;

    void show(); // Displays the array
    void report(); // Displays the array in report
    void atribui(int linha, int coluna, long double val); //Atribui um valor val a uma posicao linha x coluna da matriz
    long double value(int linha, int coluna); // returns a value of position x line array column
    void fillrand(int lim); // (for testing) Fills the array with random values within a range of 0 atlim
    void identity(); // transforms the matrix identity
    Matrix sum(Matrix m1); // Sum of two matrices of the same size
    Matrix subtract(Matrix m1); // Subtraction between two matrices of the same size
    float determinant(); // Determinant of a matrix
    Matrix product(Matrix m1); // Returns the product of the owner of the matrix method and the matrix m1
    Matrix scalar_product(double pesc);
    Matrix transpose(); // Returns the transpose of the matrix
    Matrix invert(int size); // Returns the inverse of the matrix
    Matrix copy(); //Retorna uma copia da matriz
    void fillin(); // (for testing) Fills values one by one in the matrix
    //void showGui(QTable* tabela); //Exibe a matriz num objeto QTable do QT

private:
    std::vector<std::vector<long double> > m;  // Matrix data.
    int lin, col; //dimensoes da matriz
    std::string name_; // Name of the matrix.
};

#endif // _MATRIX_H

/*
 *  rectify - Orthophoto rectification for archaeological use.
 *  Copyright (C) 2015  Bernhard Arnold
 *                2004  Marcelo Teixeira Silveira, Rafael Paz,
 *                      Orlando Bernardo Filho, Sidney Andrade de Lima,
 *                      Luiz Coelho
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see {http://www.gnu.org/licenses/}.
 *
 */

#include "Matrix.h"

#include <QtCore/QString>

#include <iostream>
#include <cstdlib>
#include <cmath>

// TODO: Replace with Eigen::MatrixXd class?

//IMPLEMENTACOES

Matrix::Matrix(int lines, int columns)
 : lines_(lines), columns_(columns)
{
    m = std::vector<std::vector<long double> >(
        this->lines(), std::vector<long double>(this->columns(), 0.)
    );
}

Matrix::~Matrix()
{
}

long double Matrix::value(int line, int column) const
{
    return m[line][column];
}

void Matrix::setValue(int line, int column, long double value)
{
    m[line][column] = value;
}

int Matrix::lines() const
{
    return lines_;
}

int Matrix::columns() const
{
    return columns_;
}

const std::string& Matrix::name() const
{
    return name_;
}


void Matrix::show()
{
    int i, j;
    for (i = 0; i < lines(); i++)
    {
        for (j = 0; j < columns(); j++)
        {
            std::cout << m[i][j] << " ";
            if (j == (columns() - 1)) std::cout << std::endl;
        }
    }
}

void Matrix::fillrand(int lim)
{
    int i, j;
    srand(time(NULL));
    for (i = 0; i < lines(); i++)
    {
        for (j = 0; j < columns(); j++)
        {
            m[i][j] = floor(rand() % lim);
        }
    }
}

void Matrix::identity(void)
{
    int i, j;
    if (lines() == columns())
    {
        for (i = 0; i < lines(); i++)
        {
            for (j = 0; j < columns(); j++)
            {
                if (i == j)
                {
                    m[i][j] = 1;
                }
                else
                {
                    m[i][j] = 0;
                }
            }
        }
        return;
    }
    std::cout << "Impossible to create identity";
    throw std::string("Impossible to create identity");
}

Matrix Matrix::sum(Matrix m1)
{
    int  i, j;
    Matrix matrix(lines(), columns());
    if ((m1.columns() == columns()) && (m1.lines() == lines()))
    {
        for (i = 0; i < lines(); i++)
        {
            for (j = 0; j < columns(); j++)
                matrix.m[i][j] = m1.m[i][j] + m[i][j];
        }
        return matrix;
    }
    std::cout << "Arrays must be the same size!" << std::endl;
    throw std::string("Arrays must be the same size!");
}

Matrix Matrix::subtract(Matrix m1)
{
    // A.subtract(B)
    // Faz   A - B
    int  i, j;
    Matrix matrix(lines(), columns());
    if ((m1.columns() == columns()) && (m1.lines() == lines()))
    {
        for (i = 0; i < lines(); i++)
        {
            for (j = 0; j < columns(); j++)
                matrix.m[i][j] = m[i][j] - m1.m[i][j];
        }
    }
    else
        std::cout << "Matrizes devem ser do mesmo tamanho! \n";
    return matrix;
}

float Matrix::determinant()
{
    int i, j, mm, nn;
    float det = 0, prdp, prdn;
    if (lines() != columns())
    {
        std::cout << "Determinante somente de matriz quadrada!\n";
        return 0;
    }
    if (lines() == 1)
        return m[0][0];
    j = lines();
    if (lines() == 2)
        j = 1;
    for (i = 0; i < j; i++)
    {
        nn = i;
        mm = 0;
        prdp = 1;
        prdn = -1;
        while (mm < lines())
        {
            prdp = prdp * m[mm][nn];
            prdn = prdn * m[mm][(columns() - 1) - nn];
            nn++;
            mm++;
            if (nn >= columns())
                nn = 0;
        }
        det = det + prdp + prdn;
    }
    return det;
}

Matrix Matrix::product(Matrix m1)
{
    int i, j, k;
    Matrix prod(lines(), m1.columns());

    if (columns() == m1.lines())
    {
        for (i = 0; i < lines(); i++) //Percorre linhas da 1 matriz
        {
            for (k = 0; k < m1.columns(); k++) //Percorre colunas da 2 matriz
            {
                prod.m[i][k] = 0;
                for (j = 0; j < columns(); j++)
                {
                    prod.m[i][k] = prod.m[i][k] + m[i][j] * m1.m[j][k];
                }
            }
        }
    }
    else
    {
        std::cout << "Impossivel multiplicar";
    }
    return prod;
}

Matrix Matrix::scalar_product(double pesc)
{
    int i, j;
    Matrix prod(lines(), columns());

    for (i = 0; i < lines(); i++)
    {
        for (j = 0; j < columns(); j++)
            prod.m[i][j] = m[i][j] * pesc;
    }
    return prod;
}

Matrix Matrix::transpose(void)
{
    int i, j;
    Matrix transposed(columns(), lines());
    for (i = 0; i < lines(); i++)
    {
        for (j = 0; j < columns(); j++)
        {
            transposed.m[j][i] = m[i][j];
        }
    }
    return transposed;

}

Matrix Matrix::copy(void)
{
    int i, j;
    Matrix clone(lines(), columns());
    for (i = 0; i < lines(); i++)
    {
        for (j = 0; j < columns(); j++)
        {
            clone.m[i][j] = m[i][j];
        }
    }
    return clone;
}

Matrix Matrix::invert(int size)
{
    int i, j, k, l; //this function inv.merts a square matrix (of course)
    long double det = 1; //M, having a (size X size) size.
    long double p, c, x;
    Matrix inv(size, size);  // Matriz nova int
    Matrix mat(lines(), columns()); // Matriz nova mat
    mat = copy();  // Cópia da matriz em uso em mat
    /*
       Establishing the identity matrix (I) inv
       |1 0 0|
       |0 1 0|
       |0 0 1|
    */
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (i == j) inv.m[i][j] = 1;
            else inv.m[i][j] = 0;
        }
    }
    i = 0;
    while (i < size) //((i<size)&&(det!=0))
    {
        c = mat.m[i][i]; // Diagonal value i, c i
        l = i; // Guarda esta posição em l
        // Percorre a coluna do i, de i+1 ao final
        for (k = i + 1; k < size; k++)
        {
            // If the absolute value of the diagonal is less than the current value
            if (abs(c) < abs(m[k][i]))
            {
                c = mat.m[k][i]; // Saves this value in C
                l = k; // e guarda esta posição em l
            }
        }
        // If the stored value is different from the original (l <> i)
        if (l != i)
        {
            det = det * (-1); // det = -det
            // Percorre toda a linha do i
            for (j = 0; j < size; j++)
            {
                x = mat.m[i][j]; // $
                mat.m[i][j] = mat.m[l][j]; // $ Troca mat(i,j) <-> mat(l,j)
                mat.m[l][j] = x; // $
                x = inv.m[i][j]; // &
                inv.m[i][j] = inv.m[l][j]; // & Troca inv(i,j) <-> inv(l,j)
                inv.m[l][j] = x; // &
            }
        }
        p = mat.m[i][i]; // Store the value of the diagonal i, i w
        det = det * p; // det = det*p
        // Se p for diferente de 0
        if (p != 0)
        {
            // Percorre a linha de i
            for(j = 0; j < size; j++)
            {
                mat.m[i][j] = mat.m[i][j] / p; // Gets the value of the current position and divided by p
                inv.m[i][j] = inv.m[i][j] / p; // Gets the value of the current position and divided by p
            }
            // Percorre a coluna de i
            for(k = 0; k < size; k++)
            {
                // Somente se k não pertencer a i
                if (k != i)
                {
                    p = mat.m[k][i]; // Store the value of the current position in p
                    // Percorre a linha
                    for(j = 0; j < size; j++)
                    {
                        mat.m[k][j] = mat.m[k][j] - p * mat.m[i][j]; // mat(k,j) = mat(k,j)-p*mat(i,j)
                        inv.m[k][j] = inv.m[k][j] - p * inv.m[i][j]; // inv(k,j) = inv(k,j)-p*inv(i,j)
                    }
                }
            }
            // Próximo ponto
            i++;
        }
    }
//if (det==0) std::cout << "Matriz nao e inversivel!\n";
    return(inv);

}

void Matrix::fillin()
{
    int i, j;
    std::cout << "Filling the matrix" << name();
    for (i = 0; i < lines(); i++)
    {
        for (j = 0; j < columns(); j++)
        {
            std::cout << "\nEnter the value of the position" << i << " x " << j << "\n";
            std::cin >> m[i][j];
        }
    }
}

/*
void Matrix::showGui(QTable *tab)
{
 int i,j;
 tab->setNumRows(lines());
 tab->setNumCols(columns());
 QString *str = new QString();

 for (i=0;i<lines();i++)
 {
  for (j=0;j<columns();j++)
  {
   tab->setText(i,j,str->number(double(m[i][j])));
  }
 }
}
*/

//Para exibir graficamente
//#include <qtable.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <qstring.h>
#include "Matrix.h"
#include "form2.h"

extern Form2 *form2;

//IMPLEMENTACOES

Matrix::Matrix(int lin, int col)
 : lin(lin), col(col)
{
    int i;
    for (size_t i = 0; i < lin; ++i)
        m.push_back(std::vector<long double>(col, 0.));
}

Matrix::~Matrix()
{
}

void Matrix::atribui(int linha, int coluna, long double val)
{
    m[linha][coluna] = val;
}

void Matrix::show()
{
    int i, j;
    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
        {
            std::cout << m[i][j] << " ";
            if (j == (col - 1)) std::cout << std::endl;
        }
    }
}

void Matrix::report()
{
    int i, j;
    QString msg, s;

    for (i = 0; i < lin; i++)
    {
        msg = "| ";
        for (j = 0; j < col; j++)
        {
            s = QString::number(m[i][j], 'f', 10);
            s.truncate(10);
            msg = msg + " " + s;
        }
        msg = msg + " |\n";
        form2->mensagem(msg);
    }
}

void Matrix::fillrand(int lim)
{
    int i, j;
    srand(time(NULL));
    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
        {
            m[i][j] = floor(rand() % lim);
        }
    }
}

void Matrix::identity(void)
{
    int i, j;
    if (lin == col)
    {
        for (i = 0; i < lin; i++)
        {
            for (j = 0; j < col; j++)
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
    Matrix matrix(lin, col);
    if ((m1.col == col) && (m1.lin == lin))
    {
        for (i = 0; i < lin; i++)
        {
            for (j = 0; j < col; j++)
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
    Matrix matrix(lin, col);
    if ((m1.col == col) && (m1.lin == lin))
    {
        for (i = 0; i < lin; i++)
        {
            for (j = 0; j < col; j++)
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
    if (lin != col)
    {
        std::cout << "Determinante somente de matriz quadrada!\n";
        return 0;
    }
    if (lin == 1)
        return m[0][0];
    j = lin;
    if (lin == 2)
        j = 1;
    for (i = 0; i < j; i++)
    {
        nn = i;
        mm = 0;
        prdp = 1;
        prdn = -1;
        while (mm < lin)
        {
            prdp = prdp * m[mm][nn];
            prdn = prdn * m[mm][(col - 1) - nn];
            nn++;
            mm++;
            if (nn >= col)
                nn = 0;
        }
        det = det + prdp + prdn;
    }
    return det;
}

Matrix Matrix::product(Matrix m1)
{
    int i, j, k;
    Matrix prod(lin, m1.col);

    if (col == m1.lin)
    {
        for (i = 0; i < lin; i++) //Percorre linhas da 1 matriz
        {
            for (k = 0; k < m1.col; k++) //Percorre colunas da 2 matriz
            {
                prod.m[i][k] = 0;
                for (j = 0; j < col; j++)
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
    Matrix prod(lin, col);

    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
            prod.m[i][j] = m[i][j] * pesc;
    }
    return prod;
}

Matrix Matrix::transpose(void)
{
    int i, j;
    Matrix transposed(col, lin);
    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
        {
            transposed.m[j][i] = m[i][j];
        }
    }
    return transposed;

}

Matrix Matrix::copy(void)
{
    int i, j;
    Matrix clone(lin, col);
    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
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
    Matrix mat(lin, col); // Matriz nova mat
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
    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
        {
            std::cout << "\nEnter the value of the position" << i << " x " << j << "\n";
            std::cin >> m[i][j];
        }
    }
}

long double Matrix::value(int linha, int coluna)
{
    return m[linha][coluna];
}

int Matrix::maxlin() const
{
    return lin;
}

int Matrix::maxcol() const
{
    return col;
}

const std::string& Matrix::name() const
{
    return name_;
}

/*
void Matrix::showGui(QTable *tab)
{
 int i,j;
 tab->setNumRows(lin);
 tab->setNumCols(col);
 QString *str = new QString();

 for (i=0;i<lin;i++)
 {
  for (j=0;j<col;j++)
  {
   tab->setText(i,j,str->number(double(m[i][j])));
  }
 }
}
*/

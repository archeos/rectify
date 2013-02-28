//Para exibir graficamente
//#include <qtable.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <qstring.h>
#include "matriz.h"
#include "form2.h"

extern Form2 *form2; 

//IMPLEMENTACOES

matriz::matriz(int linha, int coluna)
{
 int i;
 lin = linha;
 col = coluna;
 m = new long double*[lin];
 for (i=0;i<lin;i++)
  m[i] = new long double[col];
}

//matriz::~matriz()  { delete m;  }

void matriz::atribui(int linha,int coluna,long double val)
{
 m[linha][coluna] = val;
}

void matriz::show()
{
 int i,j;
 for (i=0;i<lin;i++)
 {
  for (j=0;j<col;j++)
  {
   std::cout << m[i][j] << " ";
   if (j == (col-1)) std::cout << std::endl;
  }
 }
}

void matriz::report()
{
 int i,j;
 QString msg,s;
 
 for (i=0;i<lin;i++)
 {
   msg="| ";
   for (j=0;j<col;j++)
   {
       s = QString::number(m[i][j],'f',10);
       s.truncate(10);
       msg=msg+" "+s;
   }
   msg=msg+" |\n";
   form2->mensagem(msg);
 }
}

void matriz::fillrand(int lim)
{
 int i,j;
 srand(time(NULL));
 for (i=0;i<lin;i++)
 {
  for (j=0;j<col;j++)
  {
   m[i][j] = floor(rand() % lim);
  }
 }
}

void matriz::identidade(void)
{
 int i,j;
 if (lin == col)
 {
   for (i=0;i<lin;i++)
   {
      for (j=0;j<col;j++)
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
 }       
 else
 {
      std::cout << "Impossivel criar identidade";
 }     
}

matriz matriz::soma(matriz m1)
{
              int  i,j;
              matriz soma(lin,col);
              if ((m1.col==col)&&(m1.lin==lin))
              {
                    for (i=0; i<lin; i++)
                    {
                            for (j=0; j<col; j++)
                                soma.m[i][j]=m1.m[i][j]+m[i][j];
                    }
              }
              else
                   std::cout << "Matrizes devem ser do mesmo tamanho! \n";              
              return soma;      
}

matriz matriz::subtrai(matriz m1)
{
              // A.subtrai(B)
             // Faz   A - B
              int  i,j;
              matriz subtrai(lin,col);
              if ((m1.col==col)&&(m1.lin==lin))
              {
                    for (i=0; i<lin; i++)
                    {
                            for (j=0; j<col; j++)
                                subtrai.m[i][j]=m[i][j]-m1.m[i][j];
                    }
              }
              else
                   std::cout << "Matrizes devem ser do mesmo tamanho! \n";             
              return subtrai;       
}

float matriz::det()
{
  int i,j,mm,nn;
  float det=0,prdp,prdn;
  if (lin!=col)
  {
     std::cout << "Determinante somente de matriz quadrada!\n";
     return 0;
  }
  if (lin==1)
    return m[0][0];
  j=lin;
  if (lin==2)
    j=1;  
  for (i=0; i<j; i++)
  {       
     nn=i;
     mm=0;
     prdp=1;
     prdn=-1;     
     while (mm<lin)
     {
 prdp=prdp*m[mm][nn];
 prdn=prdn*m[mm][(col-1)-nn];
 nn++;
 mm++;
 if (nn>=col)
    nn=0;
     }     
     det=det+prdp+prdn;
  }
  return det;
}

matriz matriz::produto(matriz m1)
{ 
 int i,j,k;
 matriz prod(lin,m1.col);

 if (col == m1.lin)
 {  
  for (i=0;i<lin;i++)   //Percorre linhas da 1 matriz
  {          
   for (k=0;k<m1.col;k++)  //Percorre colunas da 2 matriz
   {
    prod.m[i][k]=0;
    for (j=0;j<col;j++)
    {
     prod.m[i][k]=prod.m[i][k]+m[i][j]*m1.m[j][k];
    }
   }
  }
  return(prod);
 }
 else
 {
  std::cout << "Impossivel multiplicar";  
 }
}

matriz matriz::produto_escalar(double pesc)
{ 
  int i,j;
  matriz prod(lin,col);

  for (i=0;i<lin;i++)
  {          
   for (j=0;j<col;j++)
     prod.m[i][j]=m[i][j]*pesc; 
  }
  return(prod);
}

matriz matriz::transp(void)
{
 int i,j;
 matriz transposta(col,lin);
 for (i=0;i<lin;i++)
 {
  for (j=0;j<col;j++)
  {
   transposta.m[j][i] = m[i][j];
  }
 }
 return transposta;

}

matriz matriz::copia(void)
{
 int i,j;
 matriz clone(lin,col);
 for (i=0;i<lin;i++)
 {
  for (j=0;j<col;j++)
  {
   clone.m[i][j] = m[i][j];
  }
 }
 return clone;
}

matriz matriz::inversa(int size)
{
 int i,j,k,l; //this function inv.merts a square matrix (of course)
 long double det=1;   //M, having a (size X size) size.
 long double p,c,x;
 matriz inv(size,size);   // Matriz nova int
 matriz mat(lin,col); // Matriz nova mat
 mat = copia();  // Cópia da matriz em uso em mat
 /* 
    Cria matriz identidade (I) em inv   
    |1 0 0|
    |0 1 0|
    |0 0 1|
 */
 for (i=0;i<size;i++)
 {
  for (j=0;j<size;j++)
  {
   if (i==j) inv.m[i][j]=1;
   else inv.m[i][j]=0;
  }
 }
 i=0;
 while (i<size)//((i<size)&&(det!=0))
 {  
  c=mat.m[i][i]; // Valor da diagonal i,i em c
  l=i;  // Guarda esta posição em l
  // Percorre a coluna do i, de i+1 ao final
  for (k=i+1;k<size;k++)
  {
   // Se o valor absoluto da diagonal for menor que o valor atual
   if (abs(c)<abs(m[k][i]))
   {
    c=mat.m[k][i]; // Guarda este valor em c
    l=k;  // e guarda esta posição em l
   }
  }
  // Caso o valor guardado seja diferente do original (l <> i)
  if (l!=i)
  {
   det = det*(-1);  // det = -det
   // Percorre toda a linha do i
   for (j=0;j<size;j++)
   {
    x=mat.m[i][j];   // $
    mat.m[i][j]=mat.m[l][j]; // $ Troca mat(i,j) <-> mat(l,j)
    mat.m[l][j]=x;   // $
    x=inv.m[i][j];   // & 
    inv.m[i][j]=inv.m[l][j]; // & Troca inv(i,j) <-> inv(l,j)
    inv.m[l][j]=x;   // & 
   }
  }
  p=mat.m[i][i]; // Guarda o valor da diagonal i,i em p
  det=det*p; // det = det*p
  // Se p for diferente de 0
  if (p!=0)
  {
   // Percorre a linha de i
   for(j=0;j<size;j++)
   {
    mat.m[i][j]=mat.m[i][j]/p; // Pega o valor da posição atual e divide por p
    inv.m[i][j]=inv.m[i][j]/p; // Pega o valor da posição atual e divide por p
   }
   // Percorre a coluna de i
   for(k=0;k<size;k++)
   {
    // Somente se k não pertencer a i
    if (k!=i)
    {
     p=mat.m[k][i]; // Guarda o valor da posição atual em p
     // Percorre a linha
     for(j=0;j<size;j++)
     {
      mat.m[k][j]=mat.m[k][j]-p*mat.m[i][j]; // mat(k,j) = mat(k,j)-p*mat(i,j)
      inv.m[k][j]=inv.m[k][j]-p*inv.m[i][j]; // inv(k,j) = inv(k,j)-p*inv(i,j)
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

void matriz::namao()
{
 int i,j;
 std::cout << "Preenchendo a matriz" << nome;
 for (i=0;i<lin;i++)
 {
  for (j=0;j<col;j++)
  {
   std::cout << "\nInforme o valor da posicao" << i << " x " << j << "\n";
   std::cin >> m[i][j];
  }
 }
}

long double matriz::valor(int linha,int coluna)
{
 return m[linha][coluna];
}

int matriz::maxlin()
{
 return lin;
}
int matriz::maxcol()
{
 return col;
}

/*
void matriz::showGui(QTable *tab)
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

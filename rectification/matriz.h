/***********************************************
Classe matriz.h com suas declaracoes e implementacoes
***********************************************/

#ifndef _MATRIZ_H
#define _MATRIZ_H 1

// #include <iostream.h>
#include <stdlib.h>
#include <math.h>
//#include <qtable.h>

class matriz
{
 private:
  long double** m;  //matriz
  int lin,col;  //dimensoes da matriz
 public:
  int maxlin(void);
  int maxcol(void);
  char* nome; //nome da matriz
  matriz(int linha,int coluna); //construtor
  void show(void); //Exibe a matriz
  void report(void); //Exibe a matriz no report
  void atribui(int linha,int coluna,long double val); //Atribui um valor val a uma posicao linha x coluna da matriz
  long double valor(int linha,int coluna); //retorna um valor da posicao linha x coluna da matriz
  void fillrand(int lim); //(para testes) Preenche a matriz com valores randomicos dentro de um intervalo de 0 at�lim
  void identidade(void); //transforma a matriz em identidade
  matriz soma(matriz m1); // Soma entre 2 matrizes de mesmo tamanho
  matriz subtrai(matriz m1); // Subtração entre 2 matrizes de mesmo tamanho
  float det(); // Determinante de uma matriz
  matriz produto(matriz m1); //Retorna o produto da matriz dona do metodo e a matriz m1
  matriz produto_escalar(double pesc);
  matriz transp(void); //Retorna a transposta da matriz
  matriz inversa(int size); //Retorna a inversa da matriz
  matriz copia(void); //Retorna uma copia da matriz
  void namao(void); //(para testes) Preenche valores um a um na matriz
  //void showGui(QTable* tabela); //Exibe a matriz num objeto QTable do QT
  //~matriz(void);
};

#endif // _MATRIZ_H

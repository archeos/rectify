#include <stdio.h>
#include "matriz.cpp"

int main(void)
{
   matriz A(3,3);
   matriz B(2,2);
   A.atribui(0,0,3);
   A.atribui(1,0,3);
   A.atribui(2,0,4);
   //A.atribui(3,0,2);
   
   A.atribui(0,1,-5);
   A.atribui(1,1,1);
   A.atribui(2,1,1);
   //A.atribui(3,1,-2);
   
   A.atribui(0,2,-6);
   A.atribui(1,2,-4);
   A.atribui(2,2,5);
   //A.atribui(3,2,-2);
   
   //A.atribui(0,3,0);
   //A.atribui(1,3,1);
   //A.atribui(2,3,7);
   //A.atribui(3,3,-2);
//   B.atribui(0,0,1);
//   B.atribui(0,1,1);
//   B.atribui(1,0,1);
//   B.atribui(1,1,1);
/*   
   matriz L(8,1);
   matriz A(8,6);      
   matriz K(6,6);
   matriz N(6,1);
   matriz X(6,1);
   
   L.atribui(0,0,52);
   L.atribui(1,0,77);
   L.atribui(2,0,256);
   L.atribui(3,0,24);
   L.atribui(4,0,253);
   L.atribui(5,0,274);
   L.atribui(6,0,2);
   L.atribui(7,0,364);
    
   A.atribui(0,0,1); A.atribui(0,1,0); A.atribui(0,2,0); A.atribui(0,3,0); A.atribui(0,4,0); A.atribui(0,5,0); 
   A.atribui(1,0,0); A.atribui(1,1,0); A.atribui(1,2,0); A.atribui(1,3,1); A.atribui(1,4,0); A.atribui(1,5,0);
   A.atribui(2,0,1); A.atribui(2,1,256); A.atribui(2,2,0); A.atribui(2,3,0); A.atribui(2,4,0); A.atribui(2,5,0); 
   A.atribui(3,0,0); A.atribui(3,1,0); A.atribui(3,2,0); A.atribui(3,3,1); A.atribui(3,4,256); A.atribui(3,5,0);
   A.atribui(4,0,1); A.atribui(4,1,256); A.atribui(4,2,372); A.atribui(4,3,0); A.atribui(4,4,0); A.atribui(4,5,0); 
   A.atribui(5,0,0); A.atribui(5,1,0); A.atribui(5,2,0); A.atribui(5,3,1); A.atribui(5,4,256); A.atribui(5,5,372);
   A.atribui(6,0,1); A.atribui(6,1,0); A.atribui(6,2,372); A.atribui(6,3,0); A.atribui(6,4,0); A.atribui(6,5,0); 
   A.atribui(7,0,0); A.atribui(7,1,0); A.atribui(7,2,0); A.atribui(7,3,1); A.atribui(7,4,0); A.atribui(7,5,372);
   
   cout << "Teste dos minimos quadrados\n\n";
   A.show(); cout << "\n\n";
   L.show(); cout  << "\n\n";
   
   cout << "Passo 1: A'*A:\n\n";   
   K = A.transp().produto(A);
   K.show(); cout  << "\n\n";
   cout << "Passo 2: inv(A'*A):\n\n";   
   K = (A.transp().produto(A)).inversa(6);
   K.show(); cout  << "\n\n";
   cout << "Passo 3: A'*L:\n\n";   
   N = (A.transp()).produto(L);
   N.show(); cout  << "\n\n";
   cout << "Passo final: inv(A'*A)*(A'*L):\n\n";  
   X = ((((A.transp()).produto(A)).inversa(6)).produto(A.transp())).produto(L);
   X.show(); cout  << "\n\n";
*/  
   //A.show(); cout  << "\n\n";
   //B.show(); cout  << "\n\n";
   //A=A.subtrai(B);
   A.show(); cout  << "\n\n";
   printf("Determinante de A: %f\n",A.det());
   return 0;
}

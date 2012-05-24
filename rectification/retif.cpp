#include <qstring.h>
#include <qimage.h>
#include <qcolor.h>
#include <qmessagebox.h>
#include "retif.h"
#include "matriz.h"
#include "imagem.h"
#include "math.h"
#include "form2.h"

extern Form2 *form2; 

Retif::Retif(Imagem *o, Imagem *r, int intp)
{ 
    // Construtor da classe imagem
    original = o;
    retificada = r;
    if (original->figura->depth()<=8)
    {
         if (intp>0)
         {
             QMessageBox::warning( this, "Warning:",
             "This image has depth lower than 32 bits. It's only possible\n "
             "to use nearest neighbor interpolation !\n\n",
             "Ok",
             0);  
             form2->mensagem("Message from system: image lower than 32 bits\n"); 
             form2->mensagem("Message from system: interpolation set to Near Neighbor\n");
         }      
         interpolacao=0;
    }
    else
        interpolacao=intp;   
}

void Retif::afimGeral(int modo)
{
    // Determina os parâmetros a0, a1, a2, b0, b1, b2
    int total_pontos=0, i, j;
    while((original->pontos[total_pontos][2])&&(total_pontos<20))
       total_pontos++;
    form2->mensagem("Number of control points: "+QString::number(total_pontos)+"\n");
    
    matriz A(total_pontos*2,6);
    matriz Lb(total_pontos*2,1);    
    matriz X(6,1);

    for (i=0;i<total_pontos*2;i=i+2)
    {
        Lb.atribui(i,0,original->pontos[i/2][0]);
        Lb.atribui(i+1,0,original->pontos[i/2][1]);
    }    
    form2->mensagem("\nMatrix L:\n");
    Lb.report();

    for (i=0; i<total_pontos*2; i=i+2)
    {
        A.atribui(i,0,1);
        A.atribui(i,1,retificada->pontos[i/2][0]);
        A.atribui(i,2,retificada->pontos[i/2][1]);
        A.atribui(i,3,0);
        A.atribui(i,4,0);
        A.atribui(i,5,0);
        A.atribui(i+1,0,0);
        A.atribui(i+1,1,0);
        A.atribui(i+1,2,0);     
        A.atribui(i+1,3,1);
        A.atribui(i+1,4,retificada->pontos[i/2][0]);
        A.atribui(i+1,5,retificada->pontos[i/2][1]);
    }
    form2->mensagem("\nMatrix A:\n");
    A.report();
    
    X = ((((A.transp()).produto(A)).inversa(6)).produto(A.transp())).produto(Lb);    
    form2->mensagem("\nMatrix X:\n");
    X.report();

    float a0=X.valor(0,0),a1=X.valor(1,0),a2=X.valor(2,0),b0=X.valor(3,0),b1=X.valor(4,0),b2=X.valor(5,0);
    form2->mensagem("\n* General Affine parameters: *\nA0= "+QString::number(a0)+"\nA1= "+QString::number(a1)+"\nA2= "+QString::number(a2)+"\nB0= "+QString::number(b0)+"\nB1= "+QString::number(b1)+"\nB2= "+QString::number(b2)+"\n");
    //
    //  Calculo da MVC
    //
    form2->mensagem("\nQuality adjustment statistics:\n");
    matriz V(total_pontos*2,1);
    V = (A.produto(X)).subtrai(Lb);
    form2->mensagem("\nMatrix V:\n");
    V.report();    
    matriz sigma02(1,1);
    sigma02 = (V.transp().produto(V)).produto_escalar(1.0/(total_pontos*2-6.0));
    matriz SumX(6,6);    
    SumX = ((A.transp().produto(A)).inversa(6)).produto_escalar(sigma02.valor(0,0));
    form2->mensagem("\nVariance-covariance Matrix of the Adjusted Parameters:\n");
    SumX.report();
    form2->mensagem("\nVariance-covariance Matrix of the Observed Parameters:\n");
    matriz SumLa(8,8);
    SumLa = (A.produto(SumX)).produto(A.transp());
    SumLa.report();
    
    double x,y;
    if (modo==0)
    {
        // Começa a retificação para Geral Linear        
        for (j=0; j<retificada->height(); j++)
        {
            for (i=0; i<retificada->width(); i++)
            {
                x=a0+a1*i+a2*j;
                y=b0+b1*i+b2*j;
                retificada->figura->setPixel(i,j,achaCor(x,y));
            }
        }    
       return;
    }           
   
    // Modo não linear

    // "Chute" inicial para o modo não linear
    int iteracoes=0;
    bool converge=false, teste;
    float dx,dy,Cx,Cy,alfa;
    dx=a0;
    dy=b0;
    alfa=atan(-b1/a1);
    Cx=a1/cos(alfa);
    Cy=b2/cos(alfa);
    form2->mensagem("\n* Non-Linear parameters - initial values: *\ndx= "+QString::number(dx)+"\ndy= "+QString::number(dy)+"\nalpha= "+QString::number(alfa)+"\nCx= "+QString::number(Cx)+"\nCy= "+QString::number(Cy)+"\n");

    matriz Lo(total_pontos*2,1);    
    matriz Xa1(5,1); // Ortogonal
    matriz Xa2(3,1); // Corpo Rigido
    matriz Xo1(5,1); // Ortogonal
    matriz Xo2(3,1); // Corpo Rigido
    matriz J1(total_pontos*2,5); // Ortogonal
    matriz J2(total_pontos*2,3); // Corpo Rigido
        
    Xo1.atribui(0,0,dx); Xo1.atribui(1,0,dy); Xo1.atribui(2,0,Cx); Xo1.atribui(3,0,Cy);Xo1.atribui(4,0,alfa); // Ortogonal    
    Xo2.atribui(0,0,dx); Xo2.atribui(1,0,dy);Xo2.atribui(2,0,alfa); // Corpo Rígido
    
    // Calcula parametros necessarios
    while ((iteracoes<20)&&(!converge))
    {
         form2->mensagem("\nIteration #"+QString::number(iteracoes+1)+": \n");
         // Determina Lo
         if (modo==2)
         {
              // Ortogonal     
              for (i=0; i<total_pontos*2; i=i+2)
              {
                  Lo.atribui(i,0,dx+Cx*retificada->pontos[i/2][0]*cos(alfa)+Cy*retificada->pontos[i/2][1]*sin(alfa));
                  Lo.atribui(i+1,0,dy-Cx*retificada->pontos[i/2][0]*sin(alfa)+Cy*retificada->pontos[i/2][1]*cos(alfa));            
              }
              form2->mensagem("\nMatrix Lo:\n");
              Lo.report();      
        }
        else
        {
               // Corpo rigido   
              for (i=0; i<total_pontos*2; i=i+2)
              {
                  Lo.atribui(i,0,dx+retificada->pontos[i/2][0]*cos(alfa)+retificada->pontos[i/2][1]*sin(alfa));
                  Lo.atribui(i+1,0,dy-retificada->pontos[i/2][0]*sin(alfa)+retificada->pontos[i/2][1]*cos(alfa));                
              }
              form2->mensagem("\nMatrix Lo:\n");
              Lo.report();      
         } 
         // Determina J 
         if (modo==2)
         {
              // Ortogonal     
              for (i=0; i<total_pontos*2; i=i+2)
              {
                  J1.atribui(i,0,1);
                  J1.atribui(i,1,0);
                  J1.atribui(i,2,cos(alfa)*retificada->pontos[i/2][0]);
                  J1.atribui(i,3,sin(alfa)*retificada->pontos[i/2][1]);
                  J1.atribui(i,4,-Cx*sin(alfa)*retificada->pontos[i/2][0]+Cy*cos(alfa)*retificada->pontos[i/2][1]);
                  J1.atribui(i+1,0,0);
                  J1.atribui(i+1,1,1);
                  J1.atribui(i+1,2,-sin(alfa)*retificada->pontos[i/2][0]);
                  J1.atribui(i+1,3,cos(alfa)*retificada->pontos[i/2][1]);
                  J1.atribui(i+1,4,-Cx*cos(alfa)*retificada->pontos[i/2][0]-Cy*sin(alfa)*retificada->pontos[i/2][1]);
              }
              form2->mensagem("\nMatrix J:\n");
              J1.report();      
        }
        else
        {
              // Corpo rigido   
              for (i=0; i<total_pontos*2; i=i+2)
              {
                  J2.atribui(i,0,1);
                  J2.atribui(i,1,0);
                  J2.atribui(i,2,-retificada->pontos[i/2][0]*sin(alfa)+retificada->pontos[i/2][1]*cos(alfa));
                  J2.atribui(i+1,0,0);
                  J2.atribui(i+1,1,1);
                  J2.atribui(i+1,2,-retificada->pontos[i/2][0]*cos(alfa)-retificada->pontos[i/2][1]*sin(alfa));
              }
              form2->mensagem("\nMatrix J:\n");
              J2.report();      
        } 
        // Contas finais 
        if (modo==2)
        {
            // Calcula Xa     
            Xa1 = Xo1.subtrai((((J1.transp()).produto(J1)).inversa(5).produto(J1.transp())).produto(Lo.subtrai(Lb)));
            form2->mensagem("\nMatrix Xa:\n");
            Xa1.report();      

            // Verifica residuos
            teste=true;
            for (i=0; i<5; i++)
            {
                 if (fabs(Xa1.valor(i,0)-Xo1.valor(i,0))>0.01)
                     teste=false;
           }
           if (teste)
                converge=true;    
            // Copia
            Xo1=Xa1;
            // Atualiza parâmetros
            dx=Xa1.valor(0,0); dy=Xa1.valor(1,0); Cx=Xa1.valor(2,0); Cy=Xa1.valor(3,0); alfa=Xa1.valor(4,0);
        }
        else
        {
            // Calcula Xa
            Xa2 = Xo2.subtrai((((J2.transp()).produto(J2)).inversa(3).produto(J2.transp())).produto(Lo.subtrai(Lb)));
            form2->mensagem("\nMatrix Xa:\n");
            Xa2.report();      
            // Verifica residuos
            teste=true;
            for (i=0; i<3; i++)
            {
                 if (fabs(Xa2.valor(i,0)-Xo2.valor(i,0))>0.01)
                     teste=false;
            }
           if (teste)
                converge=true;    
            // Copia
            Xo2=Xa2;
            // Atualiza parâmetros
            dx=Xa2.valor(0,0); dy=Xa2.valor(1,0); alfa=Xa2.valor(2,0);
        }      
    iteracoes++;
    }
    form2->mensagem("\nNumber of iterations to converge: "+QString::number(iteracoes)+"\n");
    form2->mensagem("\n* Non-Linear parameters - adjusted values: *\ndx= "+QString::number(dx)+"\ndy= "+QString::number(dy)+"\nalpha= "+QString::number(alfa)+"\nCx= "+QString::number(Cx)+"\nCy= "+QString::number(Cy)+"\n");    
    // Elimina parâmetros Cx e Cy, caso ortogonal
    if (modo==1)
    {
           Cx=1;
           Cy=1;
    }
    //
    //  Calculo da MVC
    //
    form2->mensagem("\nQuality adjustment statistics - non linear:\n");
    if (modo==2)
       V = (J1.produto(Xa1)).subtrai(Lb);
    else
       V = (J2.produto(Xa2)).subtrai(Lb);
    form2->mensagem("\nMatrix V:\n");
    V.report();    
    if (modo==2)
    {
        matriz SumXa1(5,5);    
        sigma02 = (V.transp().produto(V)).produto_escalar(1.0/(total_pontos*2-5.0));
        SumXa1 = ((J1.transp().produto(J1)).inversa(5)).produto_escalar(sigma02.valor(0,0));
        form2->mensagem("\nVariance-covariance Matrix of the Adjusted Parameters:\n");
        SumXa1.report();
        form2->mensagem("\nVariance-covariance Matrix of the Observed Parameters:\n");
        SumLa = (J1.produto(SumXa1)).produto(J1.transp());
        SumLa.report();
    }
    else
    {
        matriz SumXa2(3,3);    
        sigma02 = (V.transp().produto(V)).produto_escalar(1.0/(total_pontos*2-3.0));
        SumXa2 = ((J2.transp().produto(J2)).inversa(3)).produto_escalar(sigma02.valor(0,0));
        form2->mensagem("\nVariance-covariance Matrix of the Adjusted Parameters:\n");
        SumXa2.report();
        form2->mensagem("\nVariance-covariance Matrix of the Observed Parameters:\n");
        SumLa = (J2.produto(SumXa2)).produto(J2.transp()); 
        SumLa.report();
    }
    // Desenha a nova imagem
    for (j=0; j<retificada->height(); j++)
    {
        for (i=0; i<retificada->width(); i++)
        {
            x=dx+i*Cx*cos(alfa)+j*Cy*sin(alfa);
            y=dy-i*Cx*sin(alfa)+j*Cy*cos(alfa);
            retificada->figura->setPixel(i,j,achaCor(x,y));
        }    
    }  
}

void Retif::afimIsogonal()
{
    // Determina os parâmetros a0, a1, a2, b0, b1, b2
    int total_pontos=0, i, j;
    while((original->pontos[total_pontos][2])&&(total_pontos<20))
       total_pontos++;
    form2->mensagem("Number of control points: "+QString::number(total_pontos)+"\n");
    
    matriz A(total_pontos*2,4);
    matriz L(total_pontos*2,1);
    matriz X(4,1);

    for (i=0;i<total_pontos*2;i=i+2)
    {
        L.atribui(i,0,original->pontos[i/2][0]);
        L.atribui(i+1,0,original->pontos[i/2][1]);
    } 
    
    form2->mensagem("\nMatrix L:\n");
    L.report();

    for (i=0; i<total_pontos*2; i=i+2)
    {
        A.atribui(i,0,1);
        A.atribui(i,1,retificada->pontos[i/2][0]);
        A.atribui(i,2,retificada->pontos[i/2][1]);
        A.atribui(i,3,0);
        A.atribui(i+1,0,0);
        A.atribui(i+1,1,retificada->pontos[i/2][1]);
        A.atribui(i+1,2,-retificada->pontos[i/2][0]);     
        A.atribui(i+1,3,1);
    }

    form2->mensagem("\nMatrix A:\n");
    A.report();

    X = ((((A.transp()).produto(A)).inversa(4)).produto(A.transp())).produto(L);    
    
    form2->mensagem("\nMatrix X:\n");
    X.report();

    // Começa a retificação
    float a0=X.valor(0,0),a1=X.valor(1,0),a2=X.valor(2,0),b0=X.valor(3,0);
    form2->mensagem("\n* Parameters: *\nA0= "+QString::number(a0)+"\nA1= "+QString::number(a1)+"\nA2= "+QString::number(a2)+"\nB0= "+QString::number(b0)+"\n");
    float x,y;
    //
    //  Calculo da MVC
    //
    form2->mensagem("\nQuality adjustment statistics:\n");
    matriz V(total_pontos*2,1);
    V = (A.produto(X)).subtrai(L);
    form2->mensagem("\nMatrix V:\n");
    V.report();    
    matriz sigma02(1,1);
    sigma02 = (V.transp().produto(V)).produto_escalar(1.0/(total_pontos*2-4.0));
    matriz SumX(4,4);    
    SumX = ((A.transp().produto(A)).inversa(4)).produto_escalar(sigma02.valor(0,0));
    form2->mensagem("\nVariance-covariance Matrix of the Adjusted Parameters:\n");
    SumX.report();
    form2->mensagem("\nVariance-covariance Matrix of the Observed Parameters:\n");
    matriz SumLa(8,8);
    SumLa = (A.produto(SumX)).produto(A.transp());
    SumLa.report();
    // Desenha nova imagem
    for (j=0; j<retificada->height(); j++)
    {
        for (i=0; i<retificada->width(); i++)
        {
            x=a0+a1*i+a2*j;
            y=b0-a2*i+a1*j;
            retificada->figura->setPixel(i,j,achaCor(x,y));
        }
    }        
}

void Retif::linearDireta()
{
    // Determina os parâmetros a0, a1, a2, b0, b1, b2
    int total_pontos=0, i, j;
    float k=1.0;
    while((original->pontos[total_pontos][2])&&(total_pontos<20))
       total_pontos++;
    form2->mensagem("Number of control points: "+QString::number(total_pontos)+"\n");
    
    matriz A(total_pontos*2,11);
    matriz L(total_pontos*2,1);
    matriz X(11,1);

    for (i=0;i<total_pontos*2;i=i+2)
    {
        L.atribui(i,0,original->pontos[i/2][0]);
        L.atribui(i+1,0,original->pontos[i/2][1]);
    }    

    form2->mensagem("\nMatrix L:\n");
    L.report();
    
    for (i=0; i<total_pontos*2; i=i+2)
    {
        A.atribui(i,0,retificada->pontos[i/2][0]);
        A.atribui(i,1,retificada->pontos[i/2][1]);
        A.atribui(i,2,k); 
        A.atribui(i,3,1);
        A.atribui(i,4,0);
        A.atribui(i,5,0);
        A.atribui(i,6,0);
        A.atribui(i,7,0);
        A.atribui(i,8,-original->pontos[i/2][0]*retificada->pontos[i/2][0]);
        A.atribui(i,9,-original->pontos[i/2][0]*retificada->pontos[i/2][1]);
        A.atribui(i,10,-original->pontos[i/2][0]*k); 
        A.atribui(i+1,0,0);
        A.atribui(i+1,1,0);
        A.atribui(i+1,2,0);     
        A.atribui(i+1,3,0);
        A.atribui(i+1,4,retificada->pontos[i/2][0]);
        A.atribui(i+1,5,retificada->pontos[i/2][1]);
        A.atribui(i+1,6,k);
        A.atribui(i+1,7,1);
        A.atribui(i+1,8,-original->pontos[i/2][1]*retificada->pontos[i/2][0]);
        A.atribui(i+1,9,-original->pontos[i/2][1]*retificada->pontos[i/2][1]);
        A.atribui(i+1,10,-original->pontos[i/2][1]*k);
        k=k+0.1;
    }

    form2->mensagem("\nMatrix A:\n");
    A.report();
    
    X = ((((A.transp()).produto(A)).inversa(11)).produto(A.transp())).produto(L);    

    form2->mensagem("\nMatrix X:\n");
    X.report();

    // Começa a retificação
    float l1=X.valor(0,0),l2=X.valor(1,0),l3=X.valor(2,0),l4=X.valor(3,0),l5=X.valor(4,0),l6=X.valor(5,0),l7=X.valor(6,0),l8=X.valor(7,0),l9=X.valor(8,0),l10=X.valor(9,0),l11=X.valor(10,0);
    form2->mensagem("\n* Parameters: *\nL1= "+QString::number(l1)+"\nL2= "+QString::number(l2)+"\nL3= "+QString::number(l3)+"\nL4= "+QString::number(l4)+"\nL5= "+QString::number(l5)+"\nL6= "+QString::number(l6)+"\nL7= "+QString::number(l7)+"\nL8= "+QString::number(l8)+"\nL9= "+QString::number(l9)+"\nL10= "+QString::number(l10)+"\nL11= "+QString::number(l11)+"\n");
    float x,y;
    //
    //  Calculo da MVC
    //
    form2->mensagem("\nQuality adjustment statistics:\n");
    matriz V(total_pontos*2,1);
    V = (A.produto(X)).subtrai(L);
    form2->mensagem("\nMatrix V:\n");
    V.report();    
    matriz sigma02(1,1);
    sigma02 = (V.transp().produto(V)).produto_escalar(1.0/(total_pontos*2-11.0));
    matriz SumX(11,11);    
    SumX = ((A.transp().produto(A)).inversa(11)).produto_escalar(sigma02.valor(0,0));
    form2->mensagem("\nVariance-covariance Matrix of the Adjusted Parameters:\n");
    SumX.report();
    form2->mensagem("\nVariance-covariance Matrix of the Observed Parameters:\n");
    matriz SumLa(8,8);
    SumLa = (A.produto(SumX)).produto(A.transp());
    SumLa.report();
    // Desenha a nova imagem
    for (j=0; j<retificada->height(); j++)
    {
        for (i=0; i<retificada->width(); i++)
        {
            x=(l1*i+l2*j+l3*k+l4) / (l9*i+l10*j+l11*k+1);
            y=(l5*i+l6*j+l7*k+l8) / (l9*i+l10*j+l11*k+1);
            retificada->figura->setPixel(i,j,achaCor(x,y));
        }
    }    
}

void Retif::projetiva()
{
    // Determina os parâmetros c11,c12,c13,c21,c22,c23,c31,c2
    int total_pontos=0, i, j;
    while((original->pontos[total_pontos][2])&&(total_pontos<20))
       total_pontos++;    
    form2->mensagem("Number of control points: "+QString::number(total_pontos)+"\n");
    
    matriz A(total_pontos*2,8);
    matriz L(total_pontos*2,1);
    matriz X(8,1);

    for (i=0;i<total_pontos*2;i=i+2)
    {
        L.atribui(i,0,original->pontos[i/2][0]);
        L.atribui(i+1,0,original->pontos[i/2][1]);
    }    

    form2->mensagem("\nMatrix L:\n");
    L.report();
    
    for (i=0; i<total_pontos*2; i=i+2)
    {
        A.atribui(i,0,retificada->pontos[i/2][0]);
        A.atribui(i,1,retificada->pontos[i/2][1]);
        A.atribui(i,2,1);
        A.atribui(i,3,0);
        A.atribui(i,4,0);
        A.atribui(i,5,0);
        A.atribui(i,6,-original->pontos[i/2][0]*retificada->pontos[i/2][0]);
        A.atribui(i,7,-original->pontos[i/2][0]*retificada->pontos[i/2][1]);
        A.atribui(i+1,0,0);
        A.atribui(i+1,1,0);
        A.atribui(i+1,2,0);     
        A.atribui(i+1,3,retificada->pontos[i/2][0]);
        A.atribui(i+1,4,retificada->pontos[i/2][1]);
        A.atribui(i+1,5,1);
        A.atribui(i+1,6,-original->pontos[i/2][1]*retificada->pontos[i/2][0]);
        A.atribui(i+1,7,-original->pontos[i/2][1]*retificada->pontos[i/2][1]);
    }
    
    form2->mensagem("\nMatrix A:\n");
    A.report();

    X = ((((A.transp()).produto(A)).inversa(8)).produto(A.transp())).produto(L);    

    form2->mensagem("\nMatrix X:\n");
    X.report();
    
    // Começa a retificação
    float c11=X.valor(0,0),c12=X.valor(1,0),c13=X.valor(2,0),c21=X.valor(3,0),c22=X.valor(4,0),c23=X.valor(5,0),c31=X.valor(6,0),c32=X.valor(7,0);
    form2->mensagem("\n* Parameters: *\nC11= "+QString::number(c11)+"\nC12= "+QString::number(c12)+"\nC13= "+QString::number(c13)+"\nC21= "+QString::number(c21)+"\nC22= "+QString::number(c22)+"\nC23= "+QString::number(c23)+"\nC31= "+QString::number(c31)+"\nC32= "+QString::number(c32)+"\n");
    //
    //  Calculo da MVC
    //
    form2->mensagem("\nQuality adjustment statistics:\n");
    matriz V(total_pontos*2,1);
    V = (A.produto(X)).subtrai(L);
    form2->mensagem("\nMatrix V:\n");
    V.report();    
    matriz sigma02(1,1);
    sigma02 = (V.transp().produto(V)).produto_escalar(1.0/(total_pontos*2-8.0));
    matriz SumX(8,8);    
    SumX = ((A.transp().produto(A)).inversa(8)).produto_escalar(sigma02.valor(0,0));
    form2->mensagem("\nVariance-covariance Matrix of the Adjusted Parameters:\n");
    SumX.report();    
    form2->mensagem("\nVariance-covariance Matrix of the Observed Parameters:\n");
    matriz SumLa(8,8);
    SumLa = (A.produto(SumX)).produto(A.transp());
    SumLa.report();
    // Desenha a nova imagem
    float x,y;
    for (j=0; j<retificada->height(); j++)
    {
        for (i=0; i<retificada->width(); i++)
        {
            x=(c11*i+c12*j+c13) / (c31*i+c32*j+1);
            y=(c21*i+c22*j+c23) / (c31*i+c32*j+1);
            retificada->figura->setPixel(i,j,achaCor(x,y));
        }
    }
}

QRgb Retif::achaCor(float x, float y)
{    
    // Rotina para determinação da cor do pixel da nova imagem, 
    // de acordo com o método de interpolação.
    int l,k;
    float a,b;
    float a_1,a_2,a_3,a_4;
    QRgb ponto=(0xFF000000&original->figura->pixel(0,0)); // Obtem o alfa
    int red,green,blue;
        
    switch (interpolacao)
    {
        // Vizinho mais próximo
        case 0:
        l=(int) ceil(x);
        k=(int) ceil(y);
        if ((l<0)||(k<0)||(l>=original->figura->width())||(k>=original->figura->height()))
           return 0;
        else
        {
             if (original->figura->depth()<=8)
                return original->figura->pixelIndex(l,k);
             else
                return original->figura->pixel(l,k);
        }
 
        // Bilinear
        case 1: 
        l=(int) floor(x);
        k=(int) floor(y);
        a=x-l;
        b=y-k;
        if ((l<1)||(k<1)||(l>=original->figura->width()-1)||(k>=original->figura->height()-1))
           return 0;
        else
        {
             // Filtro vermelho para variável QRgb = 0x00FF0000 shift 16 bits >>
             red=(1-a)*(1-b)*((original->figura->pixel(l,k)&0x00FF0000)>>16)+a*(1-b)*((original->figura->pixel(l+1,k)&0x00FF0000)>>16)+(1-a)*b*((original->figura->pixel(l,k+1)&0x00FF0000)>>16)+a*b*((original->figura->pixel(l+1,k+1)&0x00FF0000)>>16);
             // Filtro verde para variável QRgb = 0x0000FF00  shift 8 bits >>
             green=(1-a)*(1-b)*((original->figura->pixel(l,k)&0x0000FF00)>>8)+a*(1-b)*((original->figura->pixel(l+1,k)&0x0000FF00)>>8)+(1-a)*b*((original->figura->pixel(l,k+1)&0x0000FF00)>>8)+a*b*((original->figura->pixel(l+1,k+1)&0x0000FF00)>>8);
             // Filtro azul para variável QRgb = 0x000000FF
             blue=(1-a)*(1-b)*(original->figura->pixel(l,k)&0x000000FF)+a*(1-b)*(original->figura->pixel(l+1,k)&0x000000FF)+(1-a)*b*(original->figura->pixel(l,k+1)&0x000000FF)+a*b*(original->figura->pixel(l+1,k+1)&0x000000FF);
             ponto = ponto+(acertaPixel(red)<<16)+(acertaPixel(green)<<8)+acertaPixel(blue);
             return ponto;
        }
    
        // Bicubica
        case 2:
        l=(int) floor(x);
        k=(int) floor(y);
        a=x-l;
        b=y-k;
        if ((l<1)||(k<1)||(l>=original->figura->width()-3)||(k>=original->figura->height()-3))
           return 0;
        else
        {
             // Filtro vermelho para variável QRgb = 0x00FF0000 shift 16 bits >>
             a_1=df(a+1)*((original->figura->pixel(l-1,k+1-2)&0x00FF0000)>>16)+((original->figura->pixel(l,k+1-2)&0x00FF0000)>>16)*df(a)+((original->figura->pixel(l+1,k+1-2)&0x00FF0000)>>16)*df(a-1)+((original->figura->pixel(l+2,k+1-2)&0x00FF0000)>>16)*df(a-2);
             a_2=df(a+1)*((original->figura->pixel(l-1,k+2-2)&0x00FF0000)>>16)+((original->figura->pixel(l,k+2-2)&0x00FF0000)>>16)*df(a)+((original->figura->pixel(l+1,k+2-2)&0x00FF0000)>>16)*df(a-1)+((original->figura->pixel(l+2,k+2-2)&0x00FF0000)>>16)*df(a-2);
             a_3=df(a+1)*((original->figura->pixel(l-1,k+3-2)&0x00FF0000)>>16)+((original->figura->pixel(l,k+3-2)&0x00FF0000)>>16)*df(a)+((original->figura->pixel(l+1,k+3-2)&0x00FF0000)>>16)*df(a-1)+((original->figura->pixel(l+2,k+3-2)&0x00FF0000)>>16)*df(a-2);
             a_4=df(a+1)*((original->figura->pixel(l-1,k+4-2)&0x00FF0000)>>16)+((original->figura->pixel(l,k+4-2)&0x00FF0000)>>16)*df(a)+((original->figura->pixel(l+1,k+4-2)&0x00FF0000)>>16)*df(a-1)+((original->figura->pixel(l+2,k+4-2)&0x00FF0000)>>16)*df(a-2);             
             red=a_1*df(b+1)+a_2*df(b)+a_3*df(b-1)+a_4*df(b-2);
             // Filtro verde para variável QRgb = 0x0000FF00  shift 8 bits >>
             a_1=df(a+1)*((original->figura->pixel(l-1,k+1-2)&0x0000FF00)>>8)+((original->figura->pixel(l,k+1-2)&0x0000FF00)>>8)*df(a)+((original->figura->pixel(l+1,k+1-2)&0x0000FF00)>>8)*df(a-1)+((original->figura->pixel(l+2,k+1-2)&0x0000FF00)>>8)*df(a-2);
             a_2=df(a+1)*((original->figura->pixel(l-1,k+2-2)&0x0000FF00)>>8)+((original->figura->pixel(l,k+2-2)&0x0000FF00)>>8)*df(a)+((original->figura->pixel(l+1,k+2-2)&0x0000FF00)>>8)*df(a-1)+((original->figura->pixel(l+2,k+2-2)&0x0000FF00)>>8)*df(a-2);
             a_3=df(a+1)*((original->figura->pixel(l-1,k+3-2)&0x0000FF00)>>8)+((original->figura->pixel(l,k+3-2)&0x0000FF00)>>8)*df(a)+((original->figura->pixel(l+1,k+3-2)&0x0000FF00)>>8)*df(a-1)+((original->figura->pixel(l+2,k+3-2)&0x0000FF00)>>8)*df(a-2);
             a_4=df(a+1)*((original->figura->pixel(l-1,k+4-2)&0x0000FF00)>>8)+((original->figura->pixel(l,k+4-2)&0x0000FF00)>>8)*df(a)+((original->figura->pixel(l+1,k+4-2)&0x0000FF00)>>8)*df(a-1)+((original->figura->pixel(l+2,k+4-2)&0x0000FF00)>>8)*df(a-2);             
             green=a_1*df(b+1)+a_2*df(b)+a_3*df(b-1)+a_4*df(b-2);
             // Filtro azul para variável QRgb = 0x000000FF
             a_1=df(a+1)*(original->figura->pixel(l-1,k+1-2)&0x000000FF)+(original->figura->pixel(l,k+1-2)&0x000000FF)*df(a)+(original->figura->pixel(l+1,k+1-2)&0x000000FF)*df(a-1)+(original->figura->pixel(l+2,k+1-2)&0x000000FF)*df(a-2);
             a_2=df(a+1)*(original->figura->pixel(l-1,k+2-2)&0x000000FF)+(original->figura->pixel(l,k+2-2)&0x000000FF)*df(a)+(original->figura->pixel(l+1,k+2-2)&0x000000FF)*df(a-1)+(original->figura->pixel(l+2,k+2-2)&0x000000FF)*df(a-2);
             a_3=df(a+1)*(original->figura->pixel(l-1,k+3-2)&0x000000FF)+(original->figura->pixel(l,k+3-2)&0x000000FF)*df(a)+(original->figura->pixel(l+1,k+3-2)&0x000000FF)*df(a-1)+(original->figura->pixel(l+2,k+3-2)&0x000000FF)*df(a-2);
             a_4=df(a+1)*(original->figura->pixel(l-1,k+4-2)&0x000000FF)+(original->figura->pixel(l,k+4-2)&0x000000FF)*df(a)+(original->figura->pixel(l+1,k+4-2)&0x000000FF)*df(a-1)+(original->figura->pixel(l+2,k+4-2)&0x000000FF)*df(a-2);             
             blue=a_1*df(b+1)+a_2*df(b)+a_3*df(b-1)+a_4*df(b-2);
             ponto = ponto+(acertaPixel(red)<<16)+(acertaPixel(green)<<8)+acertaPixel(blue);
             return ponto;
        }
    
        // Lagrange
        case 3:
        l=(int) floor(x);
        k=(int) floor(y);
        a=x-l;
        b=y-k;
        if ((l<1)||(k<1)||(l>=original->figura->width()-3)||(k>=original->figura->height()-3))
           return 0;
        else
        {
             // Filtro vermelho para variável QRgb = 0x00FF0000 shift 16 bits >>
             a_1=((original->figura->pixel(l-1,k+1-2)&0x00FF0000)>>16)*(a-1)*(a-2)*a/-6 + ((original->figura->pixel(l,k+1-2)&0x00FF0000)>>16)*(a+1)*(a-1)*(a-2)/2 + ((original->figura->pixel(l+1,k+1-2)&0x00FF0000)>>16)*(a+1)*(a-2)*a/-2 + ((original->figura->pixel(l+2,k+1-2)&0x00FF0000)>>16)*(a+1)*(a-1)*a/6;
             a_2=((original->figura->pixel(l-1,k+2-2)&0x00FF0000)>>16)*(a-1)*(a-2)*a/-6 + ((original->figura->pixel(l,k+2-2)&0x00FF0000)>>16)*(a+1)*(a-1)*(a-2)/2 + ((original->figura->pixel(l+1,k+2-2)&0x00FF0000)>>16)*(a+1)*(a-2)*a/-2 + ((original->figura->pixel(l+2,k+2-2)&0x00FF0000)>>16)*(a+1)*(a-1)*a/6;
             a_3=((original->figura->pixel(l-1,k+3-2)&0x00FF0000)>>16)*(a-1)*(a-2)*a/-6 + ((original->figura->pixel(l,k+3-2)&0x00FF0000)>>16)*(a+1)*(a-1)*(a-2)/2 + ((original->figura->pixel(l+1,k+3-2)&0x00FF0000)>>16)*(a+1)*(a-2)*a/-2 + ((original->figura->pixel(l+2,k+3-2)&0x00FF0000)>>16)*(a+1)*(a-1)*a/6;
             a_4=((original->figura->pixel(l-1,k+4-2)&0x00FF0000)>>16)*(a-1)*(a-2)*a/-6 + ((original->figura->pixel(l,k+4-2)&0x00FF0000)>>16)*(a+1)*(a-1)*(a-2)/2 + ((original->figura->pixel(l+1,k+4-2)&0x00FF0000)>>16)*(a+1)*(a-2)*a/-2 + ((original->figura->pixel(l+2,k+4-2)&0x00FF0000)>>16)*(a+1)*(a-1)*a/6;
             red=a_1*(b-1)*(b-2)*b/-6 + a_2*(b+1)*(b-1)*(b-2)/2 + a_3*(b+1)*(b-2)*b/-2 + a_4*(b+1)*(b-1)*b/6;
             // Filtro verde para variável QRgb = 0x0000FF00  shift 8 bits >>
             a_1=((original->figura->pixel(l-1,k+1-2)&0x0000FF00)>>8)*(a-1)*(a-2)*a/-6 + ((original->figura->pixel(l,k+1-2)&0x0000FF00)>>8)*(a+1)*(a-1)*(a-2)/2 + ((original->figura->pixel(l+1,k+1-2)&0x0000FF00)>>8)*(a+1)*(a-2)*a/-2 + ((original->figura->pixel(l+2,k+1-2)&0x0000FF00)>>8)*(a+1)*(a-1)*a/6;
             a_2=((original->figura->pixel(l-1,k+2-2)&0x0000FF00)>>8)*(a-1)*(a-2)*a/-6 + ((original->figura->pixel(l,k+2-2)&0x0000FF00)>>8)*(a+1)*(a-1)*(a-2)/2 + ((original->figura->pixel(l+1,k+2-2)&0x0000FF00)>>8)*(a+1)*(a-2)*a/-2 + ((original->figura->pixel(l+2,k+2-2)&0x0000FF00)>>8)*(a+1)*(a-1)*a/6;
             a_3=((original->figura->pixel(l-1,k+3-2)&0x0000FF00)>>8)*(a-1)*(a-2)*a/-6 + ((original->figura->pixel(l,k+3-2)&0x0000FF00)>>8)*(a+1)*(a-1)*(a-2)/2 + ((original->figura->pixel(l+1,k+3-2)&0x0000FF00)>>8)*(a+1)*(a-2)*a/-2 + ((original->figura->pixel(l+2,k+3-2)&0x0000FF00)>>8)*(a+1)*(a-1)*a/6;
             a_4=((original->figura->pixel(l-1,k+4-2)&0x0000FF00)>>8)*(a-1)*(a-2)*a/-6 + ((original->figura->pixel(l,k+4-2)&0x0000FF00)>>8)*(a+1)*(a-1)*(a-2)/2 + ((original->figura->pixel(l+1,k+4-2)&0x0000FF00)>>8)*(a+1)*(a-2)*a/-2 + ((original->figura->pixel(l+2,k+4-2)&0x0000FF00)>>8)*(a+1)*(a-1)*a/6;
             green=a_1*(b-1)*(b-2)*b/-6 + a_2*(b+1)*(b-1)*(b-2)/2 + a_3*(b+1)*(b-2)*b/-2 + a_4*(b+1)*(b-1)*b/6;
             // Filtro azul para variável QRgb = 0x000000FF
             a_1=(original->figura->pixel(l-1,k+1-2)&0x000000FF)*(a-1)*(a-2)*a/-6 + (original->figura->pixel(l,k+1-2)&0x000000FF)*(a+1)*(a-1)*(a-2)/2 + (original->figura->pixel(l+1,k+1-2)&0x000000FF)*(a+1)*(a-2)*a/-2 + (original->figura->pixel(l+2,k+1-2)&0x000000FF)*(a+1)*(a-1)*a/6;
             a_2=(original->figura->pixel(l-1,k+2-2)&0x000000FF)*(a-1)*(a-2)*a/-6 + (original->figura->pixel(l,k+2-2)&0x000000FF)*(a+1)*(a-1)*(a-2)/2 + (original->figura->pixel(l+1,k+2-2)&0x000000FF)*(a+1)*(a-2)*a/-2 + (original->figura->pixel(l+2,k+2-2)&0x000000FF)*(a+1)*(a-1)*a/6;
             a_3=(original->figura->pixel(l-1,k+3-2)&0x000000FF)*(a-1)*(a-2)*a/-6 + (original->figura->pixel(l,k+3-2)&0x000000FF)*(a+1)*(a-1)*(a-2)/2 + (original->figura->pixel(l+1,k+3-2)&0x000000FF)*(a+1)*(a-2)*a/-2 + (original->figura->pixel(l+2,k+3-2)&0x000000FF)*(a+1)*(a-1)*a/6;
             a_4=(original->figura->pixel(l-1,k+4-2)&0x000000FF)*(a-1)*(a-2)*a/-6 + (original->figura->pixel(l,k+4-2)&0x000000FF)*(a+1)*(a-1)*(a-2)/2 + (original->figura->pixel(l+1,k+4-2)&0x000000FF)*(a+1)*(a-2)*a/-2 + (original->figura->pixel(l+2,k+4-2)&0x000000FF)*(a+1)*(a-1)*a/6;
             blue=a_1*(b-1)*(b-2)*b/-6 + a_2*(b+1)*(b-1)*(b-2)/2 + a_3*(b+1)*(b-2)*b/-2 + a_4*(b+1)*(b-1)*b/6;
             ponto = ponto+(acertaPixel(red)<<16)+(acertaPixel(green)<<8)+acertaPixel(blue);
             return ponto;
        }
    }
}

float Retif::df(float x)
{   
   //  Função auxiliar à interpolação
   float mx=fabs(x);
   
   if (mx<1)
       return mx*mx*mx-2*mx*mx+1;
   if ((mx>=1)&&(mx<2))
       return -mx*mx*mx+5*mx*mx-8*mx+4;
   else
       return 0;
}

int Retif::acertaPixel(int cor)
{
   if (cor<0)
       return 0;
   if (cor>255)
       return 255;
   return cor;
}

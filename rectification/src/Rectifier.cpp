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

#include <QtGui/QImage>
#include <QtGui/QMessageBox>
#include "Rectifier.h"
#include "Matrix.h"
#include <cmath>
#include "ReportDialog.h"
#include "Image.h"

extern ReportDialog* reportDialog;

Rectifier::Rectifier(Image* o, Image* r, int intp)
{
    // Construtor da classe imagem
    original = o;
    retificada = r;
    if (original->figura->depth() <= 8)
    {
        if (intp > 0)
        {
            QMessageBox::warning( 0, "Warning:",
                                  "This image has depth lower than 32 bits. It's only possible\n "
                                  "to use nearest neighbor interpolation !\n\n",
                                  "Ok",
                                  0);
            reportDialog->append("Message from system: image lower than 32 bits");
            reportDialog->append("Message from system: interpolation set to Near Neighbor");
        }
        interpolacao = 0;
    }
    else
        interpolacao = intp;
}

void Rectifier::afimGeral(int modo)
{
    // Determina os parâmetros a0, a1, a2, b0, b1, b2
    int total_pontos = 0, i, j;
    while((original->pontos[total_pontos][2]) && (total_pontos < 20))
        total_pontos++;
    reportDialog->append("Number of control points: " + QString::number(total_pontos));

    Matrix A(total_pontos * 2, 6);
    Matrix Lb(total_pontos * 2, 1);
    Matrix X(6, 1);

    for (i = 0; i < total_pontos * 2; i = i + 2)
    {
        Lb.setValue(i, 0, original->pontos[i / 2][0]);
        Lb.setValue(i + 1, 0, original->pontos[i / 2][1]);
    }
    reportDialog->append("\nMatrix L:");
    Lb.report();

    for (i = 0; i < total_pontos * 2; i = i + 2)
    {
        A.setValue(i, 0, 1);
        A.setValue(i, 1, retificada->pontos[i / 2][0]);
        A.setValue(i, 2, retificada->pontos[i / 2][1]);
        A.setValue(i, 3, 0);
        A.setValue(i, 4, 0);
        A.setValue(i, 5, 0);
        A.setValue(i + 1, 0, 0);
        A.setValue(i + 1, 1, 0);
        A.setValue(i + 1, 2, 0);
        A.setValue(i + 1, 3, 1);
        A.setValue(i + 1, 4, retificada->pontos[i / 2][0]);
        A.setValue(i + 1, 5, retificada->pontos[i / 2][1]);
    }
    reportDialog->append("\nMatrix A:");
    A.report();

    X = ((((A.transpose()).product(A)).invert(6)).product(A.transpose())).product(Lb);
    reportDialog->append("\nMatrix X:");
    X.report();

    float a0 = X.value(0, 0), a1 = X.value(1, 0), a2 = X.value(2, 0), b0 = X.value(3, 0), b1 = X.value(4, 0), b2 = X.value(5, 0);
    reportDialog->append("\n* General Affine parameters: *\nA0= " + QString::number(a0) + "\nA1= " + QString::number(a1) + "\nA2= " + QString::number(a2) + "\nB0= " + QString::number(b0) + "\nB1= " + QString::number(b1) + "\nB2= " + QString::number(b2));
    //
    //  Calculo da MVC
    //
    reportDialog->append("\nQuality adjustment statistics:");
    Matrix V(total_pontos * 2, 1);
    V = (A.product(X)).subtract(Lb);
    reportDialog->append("\nMatrix V:");
    V.report();
    Matrix sigma02(1, 1);
    sigma02 = (V.transpose().product(V)).scalar_product(1.0 / (total_pontos * 2 - 6.0));
    Matrix SumX(6, 6);
    SumX = ((A.transpose().product(A)).invert(6)).scalar_product(sigma02.value(0, 0));
    reportDialog->append("\nVariance-covariance Matrix of the Adjusted Parameters:");
    SumX.report();
    reportDialog->append("\nVariance-covariance Matrix of the Observed Parameters:");
    Matrix SumLa(8, 8);
    SumLa = (A.product(SumX)).product(A.transpose());
    SumLa.report();

    double x, y;
    if (modo == 0)
    {
        // Começa a retificação para Geral Linear
        for (j = 0; j < retificada->height(); j++)
        {
            for (i = 0; i < retificada->width(); i++)
            {
                x = a0 + a1 * i + a2 * j;
                y = b0 + b1 * i + b2 * j;
                retificada->figura->setPixel(i, j, achaCor(x, y));
            }
        }
        return;
    }

    // Modo não linear

    // "Chute" inicial para o modo não linear
    int iteracoes = 0;
    bool converge = false, teste;
    float dx, dy, Cx, Cy, alfa;
    dx = a0;
    dy = b0;
    alfa = atan(-b1 / a1);
    Cx = a1 / cos(alfa);
    Cy = b2 / cos(alfa);
    reportDialog->append("\n* Non-Linear parameters - initial values: *\ndx= " + QString::number(dx) + "\ndy= " + QString::number(dy) + "\nalpha= " + QString::number(alfa) + "\nCx= " + QString::number(Cx) + "\nCy= " + QString::number(Cy));

    Matrix Lo(total_pontos * 2, 1);
    Matrix Xa1(5, 1); // Ortogonal
    Matrix Xa2(3, 1); // Corpo Rigido
    Matrix Xo1(5, 1); // Ortogonal
    Matrix Xo2(3, 1); // Corpo Rigido
    Matrix J1(total_pontos * 2, 5); // Ortogonal
    Matrix J2(total_pontos * 2, 3); // Corpo Rigido

    Xo1.setValue(0, 0, dx);
    Xo1.setValue(1, 0, dy);
    Xo1.setValue(2, 0, Cx);
    Xo1.setValue(3, 0, Cy);
    Xo1.setValue(4, 0, alfa); // Ortogonal
    Xo2.setValue(0, 0, dx);
    Xo2.setValue(1, 0, dy);
    Xo2.setValue(2, 0, alfa); // Corpo Rígido

    // Calcula parametros necessarios
    while ((iteracoes < 20) && (!converge))
    {
        reportDialog->append("\nIteration #" + QString::number(iteracoes + 1) + ":");
        // Determina Lo
        if (modo == 2)
        {
            // Ortogonal
            for (i = 0; i < total_pontos * 2; i = i + 2)
            {
                Lo.setValue(i, 0, dx + Cx * retificada->pontos[i / 2][0]*cos(alfa) + Cy * retificada->pontos[i / 2][1]*sin(alfa));
                Lo.setValue(i + 1, 0, dy - Cx * retificada->pontos[i / 2][0]*sin(alfa) + Cy * retificada->pontos[i / 2][1]*cos(alfa));
            }
            reportDialog->append("\nMatrix Lo:");
            Lo.report();
        }
        else
        {
            // Corpo rigido
            for (i = 0; i < total_pontos * 2; i = i + 2)
            {
                Lo.setValue(i, 0, dx + retificada->pontos[i / 2][0]*cos(alfa) + retificada->pontos[i / 2][1]*sin(alfa));
                Lo.setValue(i + 1, 0, dy - retificada->pontos[i / 2][0]*sin(alfa) + retificada->pontos[i / 2][1]*cos(alfa));
            }
            reportDialog->append("\nMatrix Lo:");
            Lo.report();
        }
        // Determina J
        if (modo == 2)
        {
            // Ortogonal
            for (i = 0; i < total_pontos * 2; i = i + 2)
            {
                J1.setValue(i, 0, 1);
                J1.setValue(i, 1, 0);
                J1.setValue(i, 2, cos(alfa)*retificada->pontos[i / 2][0]);
                J1.setValue(i, 3, sin(alfa)*retificada->pontos[i / 2][1]);
                J1.setValue(i, 4, -Cx * sin(alfa)*retificada->pontos[i / 2][0] + Cy * cos(alfa)*retificada->pontos[i / 2][1]);
                J1.setValue(i + 1, 0, 0);
                J1.setValue(i + 1, 1, 1);
                J1.setValue(i + 1, 2, -sin(alfa)*retificada->pontos[i / 2][0]);
                J1.setValue(i + 1, 3, cos(alfa)*retificada->pontos[i / 2][1]);
                J1.setValue(i + 1, 4, -Cx * cos(alfa)*retificada->pontos[i / 2][0] - Cy * sin(alfa)*retificada->pontos[i / 2][1]);
            }
            reportDialog->append("\nMatrix J:");
            J1.report();
        }
        else
        {
            // Corpo rigido
            for (i = 0; i < total_pontos * 2; i = i + 2)
            {
                J2.setValue(i, 0, 1);
                J2.setValue(i, 1, 0);
                J2.setValue(i, 2, -retificada->pontos[i / 2][0]*sin(alfa) + retificada->pontos[i / 2][1]*cos(alfa));
                J2.setValue(i + 1, 0, 0);
                J2.setValue(i + 1, 1, 1);
                J2.setValue(i + 1, 2, -retificada->pontos[i / 2][0]*cos(alfa) - retificada->pontos[i / 2][1]*sin(alfa));
            }
            reportDialog->append("\nMatrix J:");
            J2.report();
        }
        // Contas finais
        if (modo == 2)
        {
            // Calcula Xa
            Xa1 = Xo1.subtract((((J1.transpose()).product(J1)).invert(5).product(J1.transpose())).product(Lo.subtract(Lb)));
            reportDialog->append("\nMatrix Xa:");
            Xa1.report();

            // Verifica residuos
            teste = true;
            for (i = 0; i < 5; i++)
            {
                if (fabs(Xa1.value(i, 0) - Xo1.value(i, 0)) > 0.01)
                    teste = false;
            }
            if (teste)
                converge = true;
            // Copia
            Xo1 = Xa1;
            // Atualiza parâmetros
            dx = Xa1.value(0, 0);
            dy = Xa1.value(1, 0);
            Cx = Xa1.value(2, 0);
            Cy = Xa1.value(3, 0);
            alfa = Xa1.value(4, 0);
        }
        else
        {
            // Calcula Xa
            Xa2 = Xo2.subtract((((J2.transpose()).product(J2)).invert(3).product(J2.transpose())).product(Lo.subtract(Lb)));
            reportDialog->append("\nMatrix Xa:");
            Xa2.report();
            // Verifica residuos
            teste = true;
            for (i = 0; i < 3; i++)
            {
                if (fabs(Xa2.value(i, 0) - Xo2.value(i, 0)) > 0.01)
                    teste = false;
            }
            if (teste)
                converge = true;
            // Copia
            Xo2 = Xa2;
            // Atualiza parâmetros
            dx = Xa2.value(0, 0);
            dy = Xa2.value(1, 0);
            alfa = Xa2.value(2, 0);
        }
        iteracoes++;
    }
    reportDialog->append("\nNumber of iterations to converge: " + QString::number(iteracoes));
    reportDialog->append("\n* Non-Linear parameters - adjusted values: *\ndx= " + QString::number(dx) + "\ndy= " + QString::number(dy) + "\nalpha= " + QString::number(alfa) + "\nCx= " + QString::number(Cx) + "\nCy= " + QString::number(Cy));
    // Elimina parâmetros Cx e Cy, caso ortogonal
    if (modo == 1)
    {
        Cx = 1;
        Cy = 1;
    }
    //
    //  Calculo da MVC
    //
    reportDialog->append("\nQuality adjustment statistics - non linear:");
    if (modo == 2)
        V = (J1.product(Xa1)).subtract(Lb);
    else
        V = (J2.product(Xa2)).subtract(Lb);
    reportDialog->append("\nMatrix V:");
    V.report();
    if (modo == 2)
    {
        Matrix SumXa1(5, 5);
        sigma02 = (V.transpose().product(V)).scalar_product(1.0 / (total_pontos * 2 - 5.0));
        SumXa1 = ((J1.transpose().product(J1)).invert(5)).scalar_product(sigma02.value(0, 0));
        reportDialog->append("\nVariance-covariance Matrix of the Adjusted Parameters:");
        SumXa1.report();
        reportDialog->append("\nVariance-covariance Matrix of the Observed Parameters:");
        SumLa = (J1.product(SumXa1)).product(J1.transpose());
        SumLa.report();
    }
    else
    {
        Matrix SumXa2(3, 3);
        sigma02 = (V.transpose().product(V)).scalar_product(1.0 / (total_pontos * 2 - 3.0));
        SumXa2 = ((J2.transpose().product(J2)).invert(3)).scalar_product(sigma02.value(0, 0));
        reportDialog->append("\nVariance-covariance Matrix of the Adjusted Parameters:");
        SumXa2.report();
        reportDialog->append("\nVariance-covariance Matrix of the Observed Parameters:");
        SumLa = (J2.product(SumXa2)).product(J2.transpose());
        SumLa.report();
    }
    // Desenha a nova imagem
    for (j = 0; j < retificada->height(); j++)
    {
        for (i = 0; i < retificada->width(); i++)
        {
            x = dx + i * Cx * cos(alfa) + j * Cy * sin(alfa);
            y = dy - i * Cx * sin(alfa) + j * Cy * cos(alfa);
            retificada->figura->setPixel(i, j, achaCor(x, y));
        }
    }
}

void Rectifier::afimIsogonal()
{
    // Determina os parâmetros a0, a1, a2, b0, b1, b2
    int total_pontos = 0, i, j;
    while((original->pontos[total_pontos][2]) && (total_pontos < 20))
        total_pontos++;
    reportDialog->append("Number of control points: " + QString::number(total_pontos));

    Matrix A(total_pontos * 2, 4);
    Matrix L(total_pontos * 2, 1);
    Matrix X(4, 1);

    for (i = 0; i < total_pontos * 2; i = i + 2)
    {
        L.setValue(i, 0, original->pontos[i / 2][0]);
        L.setValue(i + 1, 0, original->pontos[i / 2][1]);
    }

    reportDialog->append("\nMatrix L:");
    L.report();

    for (i = 0; i < total_pontos * 2; i = i + 2)
    {
        A.setValue(i, 0, 1);
        A.setValue(i, 1, retificada->pontos[i / 2][0]);
        A.setValue(i, 2, retificada->pontos[i / 2][1]);
        A.setValue(i, 3, 0);
        A.setValue(i + 1, 0, 0);
        A.setValue(i + 1, 1, retificada->pontos[i / 2][1]);
        A.setValue(i + 1, 2, -retificada->pontos[i / 2][0]);
        A.setValue(i + 1, 3, 1);
    }

    reportDialog->append("\nMatrix A:");
    A.report();

    X = ((((A.transpose()).product(A)).invert(4)).product(A.transpose())).product(L);

    reportDialog->append("\nMatrix X:");
    X.report();

    // Começa a retificação
    float a0 = X.value(0, 0), a1 = X.value(1, 0), a2 = X.value(2, 0), b0 = X.value(3, 0);
    reportDialog->append("\n* Parameters: *\nA0= " + QString::number(a0) + "\nA1= " + QString::number(a1) + "\nA2= " + QString::number(a2) + "\nB0= " + QString::number(b0));
    float x, y;
    //
    //  Calculo da MVC
    //
    reportDialog->append("\nQuality adjustment statistics:");
    Matrix V(total_pontos * 2, 1);
    V = (A.product(X)).subtract(L);
    reportDialog->append("\nMatrix V:");
    V.report();
    Matrix sigma02(1, 1);
    sigma02 = (V.transpose().product(V)).scalar_product(1.0 / (total_pontos * 2 - 4.0));
    Matrix SumX(4, 4);
    SumX = ((A.transpose().product(A)).invert(4)).scalar_product(sigma02.value(0, 0));
    reportDialog->append("\nVariance-covariance Matrix of the Adjusted Parameters:");
    SumX.report();
    reportDialog->append("\nVariance-covariance Matrix of the Observed Parameters:");
    Matrix SumLa(8, 8);
    SumLa = (A.product(SumX)).product(A.transpose());
    SumLa.report();
    // Desenha nova imagem
    for (j = 0; j < retificada->height(); j++)
    {
        for (i = 0; i < retificada->width(); i++)
        {
            x = a0 + a1 * i + a2 * j;
            y = b0 - a2 * i + a1 * j;
            retificada->figura->setPixel(i, j, achaCor(x, y));
        }
    }
}

void Rectifier::linearDireta()
{
    // Determina os parâmetros a0, a1, a2, b0, b1, b2
    int total_pontos = 0, i, j;
    float k = 1.0;
    while((original->pontos[total_pontos][2]) && (total_pontos < 20))
        total_pontos++;
    reportDialog->append("Number of control points: " + QString::number(total_pontos));

    Matrix A(total_pontos * 2, 11);
    Matrix L(total_pontos * 2, 1);
    Matrix X(11, 1);

    for (i = 0; i < total_pontos * 2; i = i + 2)
    {
        L.setValue(i, 0, original->pontos[i / 2][0]);
        L.setValue(i + 1, 0, original->pontos[i / 2][1]);
    }

    reportDialog->append("\nMatrix L:");
    L.report();

    for (i = 0; i < total_pontos * 2; i = i + 2)
    {
        A.setValue(i, 0, retificada->pontos[i / 2][0]);
        A.setValue(i, 1, retificada->pontos[i / 2][1]);
        A.setValue(i, 2, k);
        A.setValue(i, 3, 1);
        A.setValue(i, 4, 0);
        A.setValue(i, 5, 0);
        A.setValue(i, 6, 0);
        A.setValue(i, 7, 0);
        A.setValue(i, 8, -original->pontos[i / 2][0]*retificada->pontos[i / 2][0]);
        A.setValue(i, 9, -original->pontos[i / 2][0]*retificada->pontos[i / 2][1]);
        A.setValue(i, 10, -original->pontos[i / 2][0]*k);
        A.setValue(i + 1, 0, 0);
        A.setValue(i + 1, 1, 0);
        A.setValue(i + 1, 2, 0);
        A.setValue(i + 1, 3, 0);
        A.setValue(i + 1, 4, retificada->pontos[i / 2][0]);
        A.setValue(i + 1, 5, retificada->pontos[i / 2][1]);
        A.setValue(i + 1, 6, k);
        A.setValue(i + 1, 7, 1);
        A.setValue(i + 1, 8, -original->pontos[i / 2][1]*retificada->pontos[i / 2][0]);
        A.setValue(i + 1, 9, -original->pontos[i / 2][1]*retificada->pontos[i / 2][1]);
        A.setValue(i + 1, 10, -original->pontos[i / 2][1]*k);
        k = k + 0.1;
    }

    reportDialog->append("\nMatrix A:");
    A.report();

    X = ((((A.transpose()).product(A)).invert(11)).product(A.transpose())).product(L);

    reportDialog->append("\nMatrix X:");
    X.report();

    // Começa a retificação
    float l1 = X.value(0, 0), l2 = X.value(1, 0), l3 = X.value(2, 0), l4 = X.value(3, 0), l5 = X.value(4, 0), l6 = X.value(5, 0), l7 = X.value(6, 0), l8 = X.value(7, 0), l9 = X.value(8, 0), l10 = X.value(9, 0), l11 = X.value(10, 0);
    reportDialog->append("\n* Parameters: *\nL1= " + QString::number(l1) + "\nL2= " + QString::number(l2) + "\nL3= " + QString::number(l3) + "\nL4= " + QString::number(l4) + "\nL5= " + QString::number(l5) + "\nL6= " + QString::number(l6) + "\nL7= " + QString::number(l7) + "\nL8= " + QString::number(l8) + "\nL9= " + QString::number(l9) + "\nL10= " + QString::number(l10) + "\nL11= " + QString::number(l11));
    float x, y;
    //
    //  Calculo da MVC
    //
    reportDialog->append("\nQuality adjustment statistics:");
    Matrix V(total_pontos * 2, 1);
    V = (A.product(X)).subtract(L);
    reportDialog->append("\nMatrix V:");
    V.report();
    Matrix sigma02(1, 1);
    sigma02 = (V.transpose().product(V)).scalar_product(1.0 / (total_pontos * 2 - 11.0));
    Matrix SumX(11, 11);
    SumX = ((A.transpose().product(A)).invert(11)).scalar_product(sigma02.value(0, 0));
    reportDialog->append("\nVariance-covariance Matrix of the Adjusted Parameters:");
    SumX.report();
    reportDialog->append("\nVariance-covariance Matrix of the Observed Parameters:");
    Matrix SumLa(8, 8);
    SumLa = (A.product(SumX)).product(A.transpose());
    SumLa.report();
    // Desenha a nova imagem
    for (j = 0; j < retificada->height(); j++)
    {
        for (i = 0; i < retificada->width(); i++)
        {
            x = (l1 * i + l2 * j + l3 * k + l4) / (l9 * i + l10 * j + l11 * k + 1);
            y = (l5 * i + l6 * j + l7 * k + l8) / (l9 * i + l10 * j + l11 * k + 1);
            retificada->figura->setPixel(i, j, achaCor(x, y));
        }
    }
}

void Rectifier::projetiva()
{
    // Determina os parâmetros c11,c12,c13,c21,c22,c23,c31,c2
    int total_pontos = 0, i, j;
    while((original->pontos[total_pontos][2]) && (total_pontos < 20))
        total_pontos++;
    reportDialog->append("Number of control points: " + QString::number(total_pontos));

    Matrix A(total_pontos * 2, 8);
    Matrix L(total_pontos * 2, 1);
    Matrix X(8, 1);

    for (i = 0; i < total_pontos * 2; i = i + 2)
    {
        L.setValue(i, 0, original->pontos[i / 2][0]);
        L.setValue(i + 1, 0, original->pontos[i / 2][1]);
    }

    reportDialog->append("\nMatrix L:");
    L.report();

    for (i = 0; i < total_pontos * 2; i = i + 2)
    {
        A.setValue(i, 0, retificada->pontos[i / 2][0]);
        A.setValue(i, 1, retificada->pontos[i / 2][1]);
        A.setValue(i, 2, 1);
        A.setValue(i, 3, 0);
        A.setValue(i, 4, 0);
        A.setValue(i, 5, 0);
        A.setValue(i, 6, -original->pontos[i / 2][0]*retificada->pontos[i / 2][0]);
        A.setValue(i, 7, -original->pontos[i / 2][0]*retificada->pontos[i / 2][1]);
        A.setValue(i + 1, 0, 0);
        A.setValue(i + 1, 1, 0);
        A.setValue(i + 1, 2, 0);
        A.setValue(i + 1, 3, retificada->pontos[i / 2][0]);
        A.setValue(i + 1, 4, retificada->pontos[i / 2][1]);
        A.setValue(i + 1, 5, 1);
        A.setValue(i + 1, 6, -original->pontos[i / 2][1]*retificada->pontos[i / 2][0]);
        A.setValue(i + 1, 7, -original->pontos[i / 2][1]*retificada->pontos[i / 2][1]);
    }

    reportDialog->append("\nMatrix A:");
    A.report();

    X = ((((A.transpose()).product(A)).invert(8)).product(A.transpose())).product(L);

    reportDialog->append("\nMatrix X:");
    X.report();

    // Começa a retificação
    float c11 = X.value(0, 0), c12 = X.value(1, 0), c13 = X.value(2, 0), c21 = X.value(3, 0), c22 = X.value(4, 0), c23 = X.value(5, 0), c31 = X.value(6, 0), c32 = X.value(7, 0);
    reportDialog->append("\n* Parameters: *\nC11= " + QString::number(c11) + "\nC12= " + QString::number(c12) + "\nC13= " + QString::number(c13) + "\nC21= " + QString::number(c21) + "\nC22= " + QString::number(c22) + "\nC23= " + QString::number(c23) + "\nC31= " + QString::number(c31) + "\nC32= " + QString::number(c32));
    //
    //  Calculo da MVC
    //
    reportDialog->append("\nQuality adjustment statistics:");
    Matrix V(total_pontos * 2, 1);
    V = (A.product(X)).subtract(L);
    reportDialog->append("\nMatrix V:");
    V.report();
    Matrix sigma02(1, 1);
    sigma02 = (V.transpose().product(V)).scalar_product(1.0 / (total_pontos * 2 - 8.0));
    Matrix SumX(8, 8);
    SumX = ((A.transpose().product(A)).invert(8)).scalar_product(sigma02.value(0, 0));
    reportDialog->append("\nVariance-covariance Matrix of the Adjusted Parameters:");
    SumX.report();
    reportDialog->append("\nVariance-covariance Matrix of the Observed Parameters:");
    Matrix SumLa(8, 8);
    SumLa = (A.product(SumX)).product(A.transpose());
    SumLa.report();
    // Desenha a nova imagem
    float x, y;
    for (j = 0; j < retificada->height(); j++)
    {
        for (i = 0; i < retificada->width(); i++)
        {
            x = (c11 * i + c12 * j + c13) / (c31 * i + c32 * j + 1);
            y = (c21 * i + c22 * j + c23) / (c31 * i + c32 * j + 1);
            retificada->figura->setPixel(i, j, achaCor(x, y));
        }
    }
}

QRgb Rectifier::achaCor(float x, float y)
{
    // Rotina para determinação da cor do pixel da nova imagem,
    // de acordo com o método de interpolação.
    int l, k;
    float a, b;
    float a_1, a_2, a_3, a_4;
    QRgb ponto = (0xFF000000 & original->figura->pixel(0, 0)); // Obtem o alfa
    int red, green, blue;

    switch (interpolacao)
    {
        // Vizinho mais próximo
    case 0:
        l = (int) ceil(x);
        k = (int) ceil(y);
        if ((l < 0) || (k < 0) || (l >= original->figura->width()) || (k >= original->figura->height()))
            return 0;
        else
        {
            if (original->figura->depth() <= 8)
                return original->figura->pixelIndex(l, k);
            else
                return original->figura->pixel(l, k);
        }

        // Bilinear
    case 1:
        l = (int) floor(x);
        k = (int) floor(y);
        a = x - l;
        b = y - k;
        if ((l < 1) || (k < 1) || (l >= original->figura->width() - 1) || (k >= original->figura->height() - 1))
            return 0;
        else
        {
            // Filtro vermelho para variável QRgb = 0x00FF0000 shift 16 bits >>
            red = (1 - a) * (1 - b) * ((original->figura->pixel(l, k) & 0x00FF0000) >> 16) + a * (1 - b) * ((original->figura->pixel(l + 1, k) & 0x00FF0000) >> 16) + (1 - a) * b * ((original->figura->pixel(l, k + 1) & 0x00FF0000) >> 16) + a * b * ((original->figura->pixel(l + 1, k + 1) & 0x00FF0000) >> 16);
            // Filtro verde para variável QRgb = 0x0000FF00  shift 8 bits >>
            green = (1 - a) * (1 - b) * ((original->figura->pixel(l, k) & 0x0000FF00) >> 8) + a * (1 - b) * ((original->figura->pixel(l + 1, k) & 0x0000FF00) >> 8) + (1 - a) * b * ((original->figura->pixel(l, k + 1) & 0x0000FF00) >> 8) + a * b * ((original->figura->pixel(l + 1, k + 1) & 0x0000FF00) >> 8);
            // Filtro azul para variável QRgb = 0x000000FF
            blue = (1 - a) * (1 - b) * (original->figura->pixel(l, k) & 0x000000FF) + a * (1 - b) * (original->figura->pixel(l + 1, k) & 0x000000FF) + (1 - a) * b * (original->figura->pixel(l, k + 1) & 0x000000FF) + a * b * (original->figura->pixel(l + 1, k + 1) & 0x000000FF);
            ponto = ponto + (acertaPixel(red) << 16) + (acertaPixel(green) << 8) + acertaPixel(blue);
            return ponto;
        }

        // Bicubica
    case 2:
        l = (int) floor(x);
        k = (int) floor(y);
        a = x - l;
        b = y - k;
        if ((l < 1) || (k < 1) || (l >= original->figura->width() - 3) || (k >= original->figura->height() - 3))
            return 0;
        else
        {
            // Filtro vermelho para variável QRgb = 0x00FF0000 shift 16 bits >>
            a_1 = df(a + 1) * ((original->figura->pixel(l - 1, k + 1 - 2) & 0x00FF0000) >> 16) + ((original->figura->pixel(l, k + 1 - 2) & 0x00FF0000) >> 16) * df(a) + ((original->figura->pixel(l + 1, k + 1 - 2) & 0x00FF0000) >> 16) * df(a - 1) + ((original->figura->pixel(l + 2, k + 1 - 2) & 0x00FF0000) >> 16) * df(a - 2);
            a_2 = df(a + 1) * ((original->figura->pixel(l - 1, k + 2 - 2) & 0x00FF0000) >> 16) + ((original->figura->pixel(l, k + 2 - 2) & 0x00FF0000) >> 16) * df(a) + ((original->figura->pixel(l + 1, k + 2 - 2) & 0x00FF0000) >> 16) * df(a - 1) + ((original->figura->pixel(l + 2, k + 2 - 2) & 0x00FF0000) >> 16) * df(a - 2);
            a_3 = df(a + 1) * ((original->figura->pixel(l - 1, k + 3 - 2) & 0x00FF0000) >> 16) + ((original->figura->pixel(l, k + 3 - 2) & 0x00FF0000) >> 16) * df(a) + ((original->figura->pixel(l + 1, k + 3 - 2) & 0x00FF0000) >> 16) * df(a - 1) + ((original->figura->pixel(l + 2, k + 3 - 2) & 0x00FF0000) >> 16) * df(a - 2);
            a_4 = df(a + 1) * ((original->figura->pixel(l - 1, k + 4 - 2) & 0x00FF0000) >> 16) + ((original->figura->pixel(l, k + 4 - 2) & 0x00FF0000) >> 16) * df(a) + ((original->figura->pixel(l + 1, k + 4 - 2) & 0x00FF0000) >> 16) * df(a - 1) + ((original->figura->pixel(l + 2, k + 4 - 2) & 0x00FF0000) >> 16) * df(a - 2);
            red = a_1 * df(b + 1) + a_2 * df(b) + a_3 * df(b - 1) + a_4 * df(b - 2);
            // Filtro verde para variável QRgb = 0x0000FF00  shift 8 bits >>
            a_1 = df(a + 1) * ((original->figura->pixel(l - 1, k + 1 - 2) & 0x0000FF00) >> 8) + ((original->figura->pixel(l, k + 1 - 2) & 0x0000FF00) >> 8) * df(a) + ((original->figura->pixel(l + 1, k + 1 - 2) & 0x0000FF00) >> 8) * df(a - 1) + ((original->figura->pixel(l + 2, k + 1 - 2) & 0x0000FF00) >> 8) * df(a - 2);
            a_2 = df(a + 1) * ((original->figura->pixel(l - 1, k + 2 - 2) & 0x0000FF00) >> 8) + ((original->figura->pixel(l, k + 2 - 2) & 0x0000FF00) >> 8) * df(a) + ((original->figura->pixel(l + 1, k + 2 - 2) & 0x0000FF00) >> 8) * df(a - 1) + ((original->figura->pixel(l + 2, k + 2 - 2) & 0x0000FF00) >> 8) * df(a - 2);
            a_3 = df(a + 1) * ((original->figura->pixel(l - 1, k + 3 - 2) & 0x0000FF00) >> 8) + ((original->figura->pixel(l, k + 3 - 2) & 0x0000FF00) >> 8) * df(a) + ((original->figura->pixel(l + 1, k + 3 - 2) & 0x0000FF00) >> 8) * df(a - 1) + ((original->figura->pixel(l + 2, k + 3 - 2) & 0x0000FF00) >> 8) * df(a - 2);
            a_4 = df(a + 1) * ((original->figura->pixel(l - 1, k + 4 - 2) & 0x0000FF00) >> 8) + ((original->figura->pixel(l, k + 4 - 2) & 0x0000FF00) >> 8) * df(a) + ((original->figura->pixel(l + 1, k + 4 - 2) & 0x0000FF00) >> 8) * df(a - 1) + ((original->figura->pixel(l + 2, k + 4 - 2) & 0x0000FF00) >> 8) * df(a - 2);
            green = a_1 * df(b + 1) + a_2 * df(b) + a_3 * df(b - 1) + a_4 * df(b - 2);
            // Filtro azul para variável QRgb = 0x000000FF
            a_1 = df(a + 1) * (original->figura->pixel(l - 1, k + 1 - 2) & 0x000000FF) + (original->figura->pixel(l, k + 1 - 2) & 0x000000FF) * df(a) + (original->figura->pixel(l + 1, k + 1 - 2) & 0x000000FF) * df(a - 1) + (original->figura->pixel(l + 2, k + 1 - 2) & 0x000000FF) * df(a - 2);
            a_2 = df(a + 1) * (original->figura->pixel(l - 1, k + 2 - 2) & 0x000000FF) + (original->figura->pixel(l, k + 2 - 2) & 0x000000FF) * df(a) + (original->figura->pixel(l + 1, k + 2 - 2) & 0x000000FF) * df(a - 1) + (original->figura->pixel(l + 2, k + 2 - 2) & 0x000000FF) * df(a - 2);
            a_3 = df(a + 1) * (original->figura->pixel(l - 1, k + 3 - 2) & 0x000000FF) + (original->figura->pixel(l, k + 3 - 2) & 0x000000FF) * df(a) + (original->figura->pixel(l + 1, k + 3 - 2) & 0x000000FF) * df(a - 1) + (original->figura->pixel(l + 2, k + 3 - 2) & 0x000000FF) * df(a - 2);
            a_4 = df(a + 1) * (original->figura->pixel(l - 1, k + 4 - 2) & 0x000000FF) + (original->figura->pixel(l, k + 4 - 2) & 0x000000FF) * df(a) + (original->figura->pixel(l + 1, k + 4 - 2) & 0x000000FF) * df(a - 1) + (original->figura->pixel(l + 2, k + 4 - 2) & 0x000000FF) * df(a - 2);
            blue = a_1 * df(b + 1) + a_2 * df(b) + a_3 * df(b - 1) + a_4 * df(b - 2);
            ponto = ponto + (acertaPixel(red) << 16) + (acertaPixel(green) << 8) + acertaPixel(blue);
            return ponto;
        }

        // Lagrange
    case 3:
        l = (int) floor(x);
        k = (int) floor(y);
        a = x - l;
        b = y - k;
        if ((l < 1) || (k < 1) || (l >= original->figura->width() - 3) || (k >= original->figura->height() - 3))
            return 0;
        else
        {
            // Filtro vermelho para variável QRgb = 0x00FF0000 shift 16 bits >>
            a_1 = ((original->figura->pixel(l - 1, k + 1 - 2) & 0x00FF0000) >> 16) * (a - 1) * (a - 2) * a / -6 + ((original->figura->pixel(l, k + 1 - 2) & 0x00FF0000) >> 16) * (a + 1) * (a - 1) * (a - 2) / 2 + ((original->figura->pixel(l + 1, k + 1 - 2) & 0x00FF0000) >> 16) * (a + 1) * (a - 2) * a / -2 + ((original->figura->pixel(l + 2, k + 1 - 2) & 0x00FF0000) >> 16) * (a + 1) * (a - 1) * a / 6;
            a_2 = ((original->figura->pixel(l - 1, k + 2 - 2) & 0x00FF0000) >> 16) * (a - 1) * (a - 2) * a / -6 + ((original->figura->pixel(l, k + 2 - 2) & 0x00FF0000) >> 16) * (a + 1) * (a - 1) * (a - 2) / 2 + ((original->figura->pixel(l + 1, k + 2 - 2) & 0x00FF0000) >> 16) * (a + 1) * (a - 2) * a / -2 + ((original->figura->pixel(l + 2, k + 2 - 2) & 0x00FF0000) >> 16) * (a + 1) * (a - 1) * a / 6;
            a_3 = ((original->figura->pixel(l - 1, k + 3 - 2) & 0x00FF0000) >> 16) * (a - 1) * (a - 2) * a / -6 + ((original->figura->pixel(l, k + 3 - 2) & 0x00FF0000) >> 16) * (a + 1) * (a - 1) * (a - 2) / 2 + ((original->figura->pixel(l + 1, k + 3 - 2) & 0x00FF0000) >> 16) * (a + 1) * (a - 2) * a / -2 + ((original->figura->pixel(l + 2, k + 3 - 2) & 0x00FF0000) >> 16) * (a + 1) * (a - 1) * a / 6;
            a_4 = ((original->figura->pixel(l - 1, k + 4 - 2) & 0x00FF0000) >> 16) * (a - 1) * (a - 2) * a / -6 + ((original->figura->pixel(l, k + 4 - 2) & 0x00FF0000) >> 16) * (a + 1) * (a - 1) * (a - 2) / 2 + ((original->figura->pixel(l + 1, k + 4 - 2) & 0x00FF0000) >> 16) * (a + 1) * (a - 2) * a / -2 + ((original->figura->pixel(l + 2, k + 4 - 2) & 0x00FF0000) >> 16) * (a + 1) * (a - 1) * a / 6;
            red = a_1 * (b - 1) * (b - 2) * b / -6 + a_2 * (b + 1) * (b - 1) * (b - 2) / 2 + a_3 * (b + 1) * (b - 2) * b / -2 + a_4 * (b + 1) * (b - 1) * b / 6;
            // Filtro verde para variável QRgb = 0x0000FF00  shift 8 bits >>
            a_1 = ((original->figura->pixel(l - 1, k + 1 - 2) & 0x0000FF00) >> 8) * (a - 1) * (a - 2) * a / -6 + ((original->figura->pixel(l, k + 1 - 2) & 0x0000FF00) >> 8) * (a + 1) * (a - 1) * (a - 2) / 2 + ((original->figura->pixel(l + 1, k + 1 - 2) & 0x0000FF00) >> 8) * (a + 1) * (a - 2) * a / -2 + ((original->figura->pixel(l + 2, k + 1 - 2) & 0x0000FF00) >> 8) * (a + 1) * (a - 1) * a / 6;
            a_2 = ((original->figura->pixel(l - 1, k + 2 - 2) & 0x0000FF00) >> 8) * (a - 1) * (a - 2) * a / -6 + ((original->figura->pixel(l, k + 2 - 2) & 0x0000FF00) >> 8) * (a + 1) * (a - 1) * (a - 2) / 2 + ((original->figura->pixel(l + 1, k + 2 - 2) & 0x0000FF00) >> 8) * (a + 1) * (a - 2) * a / -2 + ((original->figura->pixel(l + 2, k + 2 - 2) & 0x0000FF00) >> 8) * (a + 1) * (a - 1) * a / 6;
            a_3 = ((original->figura->pixel(l - 1, k + 3 - 2) & 0x0000FF00) >> 8) * (a - 1) * (a - 2) * a / -6 + ((original->figura->pixel(l, k + 3 - 2) & 0x0000FF00) >> 8) * (a + 1) * (a - 1) * (a - 2) / 2 + ((original->figura->pixel(l + 1, k + 3 - 2) & 0x0000FF00) >> 8) * (a + 1) * (a - 2) * a / -2 + ((original->figura->pixel(l + 2, k + 3 - 2) & 0x0000FF00) >> 8) * (a + 1) * (a - 1) * a / 6;
            a_4 = ((original->figura->pixel(l - 1, k + 4 - 2) & 0x0000FF00) >> 8) * (a - 1) * (a - 2) * a / -6 + ((original->figura->pixel(l, k + 4 - 2) & 0x0000FF00) >> 8) * (a + 1) * (a - 1) * (a - 2) / 2 + ((original->figura->pixel(l + 1, k + 4 - 2) & 0x0000FF00) >> 8) * (a + 1) * (a - 2) * a / -2 + ((original->figura->pixel(l + 2, k + 4 - 2) & 0x0000FF00) >> 8) * (a + 1) * (a - 1) * a / 6;
            green = a_1 * (b - 1) * (b - 2) * b / -6 + a_2 * (b + 1) * (b - 1) * (b - 2) / 2 + a_3 * (b + 1) * (b - 2) * b / -2 + a_4 * (b + 1) * (b - 1) * b / 6;
            // Filtro azul para variável QRgb = 0x000000FF
            a_1 = (original->figura->pixel(l - 1, k + 1 - 2) & 0x000000FF) * (a - 1) * (a - 2) * a / -6 + (original->figura->pixel(l, k + 1 - 2) & 0x000000FF) * (a + 1) * (a - 1) * (a - 2) / 2 + (original->figura->pixel(l + 1, k + 1 - 2) & 0x000000FF) * (a + 1) * (a - 2) * a / -2 + (original->figura->pixel(l + 2, k + 1 - 2) & 0x000000FF) * (a + 1) * (a - 1) * a / 6;
            a_2 = (original->figura->pixel(l - 1, k + 2 - 2) & 0x000000FF) * (a - 1) * (a - 2) * a / -6 + (original->figura->pixel(l, k + 2 - 2) & 0x000000FF) * (a + 1) * (a - 1) * (a - 2) / 2 + (original->figura->pixel(l + 1, k + 2 - 2) & 0x000000FF) * (a + 1) * (a - 2) * a / -2 + (original->figura->pixel(l + 2, k + 2 - 2) & 0x000000FF) * (a + 1) * (a - 1) * a / 6;
            a_3 = (original->figura->pixel(l - 1, k + 3 - 2) & 0x000000FF) * (a - 1) * (a - 2) * a / -6 + (original->figura->pixel(l, k + 3 - 2) & 0x000000FF) * (a + 1) * (a - 1) * (a - 2) / 2 + (original->figura->pixel(l + 1, k + 3 - 2) & 0x000000FF) * (a + 1) * (a - 2) * a / -2 + (original->figura->pixel(l + 2, k + 3 - 2) & 0x000000FF) * (a + 1) * (a - 1) * a / 6;
            a_4 = (original->figura->pixel(l - 1, k + 4 - 2) & 0x000000FF) * (a - 1) * (a - 2) * a / -6 + (original->figura->pixel(l, k + 4 - 2) & 0x000000FF) * (a + 1) * (a - 1) * (a - 2) / 2 + (original->figura->pixel(l + 1, k + 4 - 2) & 0x000000FF) * (a + 1) * (a - 2) * a / -2 + (original->figura->pixel(l + 2, k + 4 - 2) & 0x000000FF) * (a + 1) * (a - 1) * a / 6;
            blue = a_1 * (b - 1) * (b - 2) * b / -6 + a_2 * (b + 1) * (b - 1) * (b - 2) / 2 + a_3 * (b + 1) * (b - 2) * b / -2 + a_4 * (b + 1) * (b - 1) * b / 6;
            ponto = ponto + (acertaPixel(red) << 16) + (acertaPixel(green) << 8) + acertaPixel(blue);
            return ponto;
        }
        default:
            return ponto;
    }
}

float Rectifier::df(float x)
{
    //  Função auxiliar à interpolação
    float mx = fabs(x);

    if (mx < 1)
        return mx * mx * mx - 2 * mx * mx + 1;
    if ((mx >= 1) && (mx < 2))
        return -mx * mx * mx + 5 * mx * mx - 8 * mx + 4;
    else
        return 0;
}

int Rectifier::acertaPixel(int cor)
{
    if (cor < 0)
        return 0;
    if (cor > 255)
        return 255;
    return cor;
}

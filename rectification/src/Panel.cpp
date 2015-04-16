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

#include "Image.h"
#include "Panel.h"
#include <q3scrollview.h>
#include <qimage.h>
#include <qmessagebox.h>
#include <qstring.h>
#include "Rectifier.h"
#include "ReportDialog.h"

extern ReportDialog* reportDialog;

Panel::Panel(QWidget* parent) : Q3ScrollView( parent)
{
    // Construtor da classe imagem
    // Removed next, because of auto layout
//    setGeometry(200,25,710,475);
    original = new Image(0);
    retificada = new Image(1);
}

void Panel::abrirImage(QString nome)
{
    setContentsPos(0, 0); // Reseta posição do painel
    addChild(original);  // Indica que o objeto "original" é seu filho
    original->openImage(nome);
    reportDialog->append("*** STARTING A NEW RECTIFICATION ***");
    reportDialog->append("Original image: " + nome + "\n");
    reportDialog->append("Image width: " + QString::number(original->figura->width()) + " pixels");
    reportDialog->append("Image height: " + QString::number(original->figura->height()) + " pixels");
    reportDialog->append("Image depth: " + QString::number(original->figura->depth()) + " bit\n");
    resizeContents(original->figura->width(), original->figura->height());
    original->show();
    original->zeroPontos(0);
    retificada->zeroPontos(0);
    retificada->figura->create(original->figura->width(), original->figura->height(), original->figura->depth(), original->figura->numColors());
    if (original->figura->depth() <= 8)
    {
        QVector<QRgb> tabela(256);
        for (int i = 0; i < original->figura->numColors(); i++)
        {
            retificada->figura->setColor(i, tabela.data()[i]);
        }
        /*QRgb *tabela = original->figura->colorTable();
        for (int i=0; i<original->figura->numColors(); i++)
        {
            retificada->figura->setColor(i,*tabela);
            tabela++;
        }*/
    }
    retificada->setGeometry(0, 0, original->width(), original->height());
    inverte();
    original->imageInfo(0);
}

void Panel::salvarImage(QString nome)
{
    retificada->saveImage(nome);
}

void Panel::abrirModelo(QString nome)
{
    setContentsPos(0, 0);
    retificada->openImage(nome);
    resizeContents(retificada->figura->width(), retificada->figura->height());
    retificada->imageInfo(1);
}

void Panel::mudaOriginal()
{
    addChild(original);
    retificada->hide();
    original->show();
    original->imageInfo(0);
    resizeContents(original->figura->width(), original->figura->height());
}

void Panel::mudaRetificada()
{
    addChild(retificada);
    original->hide();
    retificada->show();
    retificada->imageInfo(1);
    resizeContents(retificada->figura->width(), retificada->figura->height());
}

void Panel::atualizaPontosOriginal(int pos, int x, int y)
{
    original->pontos[pos][0] = x;
    original->pontos[pos][1] = y;
    original->pontos[pos][2] = 1;
}

void Panel::atualizaPontosRetificada(int pos, int x, int y)
{
    retificada->pontos[pos][0] = x;
    retificada->pontos[pos][1] = y;
    retificada->pontos[pos][2] = 1;
}

int Panel::retornaPontos(int var, int pos)
{
    switch (var)
    {
    case 0 :
        return original->pontos[pos][0];
        break;
    case 1 :
        return original->pontos[pos][1];
        break;
    case 2 :
        return retificada->pontos[pos][0];
        break;
    case 3 :
        return retificada->pontos[pos][1];
        break;
    default :
        throw std::string("Panel::retornaPontos(): invalid value for var");
    }
}

void Panel::atualizaImage()
{
    original->repaint();
    retificada->repaint();
}

void Panel::zeraPontos(int inicio)
{
    original->zeroPontos(inicio);
    retificada->zeroPontos(inicio);
    atualizaImage();
}

void Panel::inverte()
{
    int depth = original->figura->depth();
    for (int j = 0; j < original->figura->height(); j++)
    {
        for (int i = 0; i < original->figura->width(); i++)
        {
            if (depth <= 8)
                retificada->figura->setPixel(i, j, 255 - original->figura->pixelIndex(i, j));
            else
                retificada->figura->setPixel(i, j, (~original->figura->pixel(i, j)) | ((original->figura->pixel(i, j)) & 0xFF000000));
        }
    }
}

void Panel::redimensiona(int x, int y)
{
    retificada->figura->create(x, y, original->figura->depth(), original->figura->numColors());
    if (original->figura->depth() <= 8)
    {
        QVector<QRgb> tabela(256);
        for (int i = 0; i < original->figura->numColors(); i++)
        {
            retificada->figura->setColor(i, tabela.data()[i]);
        }
        /*QRgb *tabela = original->figura->colorTable();
        for (int i=0; i<original->figura->numColors(); i++)
        {
            retificada->figura->setColor(i,*tabela);
            tabela++;
        }*/
    }
    reportDialog->append("Destiny image resized to : " + QString::number(x) + " x " + QString::number(y) + "\n");
    setContentsPos(0, 0);
    resizeContents(x, y);
    retificada->setGeometry(0, 0, x, y);
    retificada->repaint();
    retificada->imageInfo(1);
}
void Panel::retificaImage(int tipo, int intp, int totpts)
{
    // Verifica se todos os pontos foram devidamente preenchidos
    for (int i = 0; i < totpts; i++)
    {
        if ((!original->pontos[i][2]) || (!retificada->pontos[i][2]))
        {
            QMessageBox::warning( this, "Warning:",
                                  "You haven't selected all points yet !\n\n",
                                  "Ok",
                                  0);
            reportDialog->append("Message from system: not ready yet - missing points");
            return;
        }
    }
    // Imprime pontos no relatório
    reportDialog->append("Selected points:");
    for (int i = 0; i < totpts; i++)
    {
        reportDialog->append("P" + QString::number(i + 1) + " - (" + QString::number(original->pontos[i][0]) + "," + QString::number(original->pontos[i][1]) + ")");
        reportDialog->append("P'" + QString::number(i + 1) + " - (" + QString::number(retificada->pontos[i][0]) + "," + QString::number(retificada->pontos[i][1]) + ")");
    }
    // Então, começa a retificar
    Rectifier retific(original, retificada, intp);
    switch (tipo)
    {
    case 0:
        retific.afimGeral(1);
        break;
    case 1:
        retific.afimGeral(0);
        break;
    case 2:
        retific.afimGeral(2);
        break;
    case 3:
        retific.afimIsogonal();
        break;
    case 4:
        retific.linearDireta();
        break;
    case 5:
        retific.projetiva();
        break;
    }
    retificada->repaint();
    reportDialog->append(">>> End of rectification process <<<\n");
}

int Panel::pontosMedianas()
{
    for (int i = 0; i < 3; i++)
    {
        if ((!original->pontos[i][2]) || (!retificada->pontos[i][2]))
        {
            QMessageBox::warning( this, "Warning:",
                                  "You must select 4 points on both images\n "
                                  "in order to create a quadrilateral !\n\n",
                                  "Ok",
                                  0);
            return 0; // Não dá para fazer nada!
        }
    }
    // pronto para criar pontos
    original->zeroPontos(4);
    retificada->zeroPontos(4);
    for (int i = 0; i < 2; i++)
    {
        // Para a imagem original
        original->pontos[4][i] = abs((original->pontos[0][i] + original->pontos[1][i]) / 2);
        original->pontos[5][i] = abs((original->pontos[1][i] + original->pontos[2][i]) / 2);
        original->pontos[6][i] = abs((original->pontos[2][i] + original->pontos[3][i]) / 2);
        original->pontos[7][i] = abs((original->pontos[3][i] + original->pontos[0][i]) / 2);
        original->pontos[8][i] = abs((original->pontos[0][i] + original->pontos[2][i]) / 2);
        original->pontos[9][i] = abs((original->pontos[1][i] + original->pontos[3][i]) / 2);
        // Para a imagem retificada
        retificada->pontos[4][i] = abs((retificada->pontos[0][i] + retificada->pontos[1][i]) / 2);
        retificada->pontos[5][i] = abs((retificada->pontos[1][i] + retificada->pontos[2][i]) / 2);
        retificada->pontos[6][i] = abs((retificada->pontos[2][i] + retificada->pontos[3][i]) / 2);
        retificada->pontos[7][i] = abs((retificada->pontos[3][i] + retificada->pontos[0][i]) / 2);
        retificada->pontos[8][i] = abs((retificada->pontos[0][i] + retificada->pontos[2][i]) / 2);
        retificada->pontos[9][i] = abs((retificada->pontos[1][i] + retificada->pontos[3][i]) / 2);
    }
    for (int i = 4; i < 10; i++)
    {
        original->pontos[i][2] = 1;
        retificada->pontos[i][2] = 1;
    }
    original->repaint();
    retificada->repaint();
    return 1; // Ok!
}

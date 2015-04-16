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

#ifndef Panel_h
#define Panel_h

#include <QtGui/QApplication>
#include <q3scrollview.h>

class Image;

class Panel: public Q3ScrollView
{
    Q_OBJECT

public:
    Panel(QWidget* parent = 0);
    Image *original;
    Image *retificada;

public slots:
    void abrirImage(QString nome);
    void salvarImage(QString nome);
    void abrirModelo(QString nome);
    void mudaOriginal();
    void mudaRetificada();
    void atualizaPontosOriginal(int pos, int x, int y);
    void atualizaPontosRetificada(int pos, int x, int y);
    int retornaPontos(int var, int pos);
    void atualizaImage();
    void zeraPontos(int inicio);
    void inverte();
    void redimensiona(int x, int y);
    void retificaImage(int tipo, int intp, int totpts);
    int pontosMedianas();

signals:
    void clicked();
    void moved();
    void explain(const QString&);

protected:

private:
};

#endif // Panel_h

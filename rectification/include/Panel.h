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
#include <QtGui/QScrollArea>

class Image;

class Panel: public QScrollArea
{
    Q_OBJECT

public:
    Panel(QWidget* parent = 0);
    virtual ~Panel();
    Image* original;
    Image* retificada;

public:
    void showImage(Image* image);

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

    void showSourceImage();
    void showTargetImage();

    void report(const QString& message);

signals:
    void clicked();
    void moved();
    void explain(const QString&);
    void report_(const QString& message);

protected:

private:


};

#endif // Panel_h

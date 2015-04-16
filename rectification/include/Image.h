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

#ifndef Image_h
#define Image_h

#include <QtGui/QApplication>
#include <QtGui/QImage>
#include <QtGui/QMouseEvent>
#include <QtGui/QPaintEvent>
#include <QtGui/QPixmap>
#include <QtGui/QWidget>

class Image: public QWidget
{
    Q_OBJECT

public:
    Image(int ords);
    QImage *figura;
    int pontos[20][3]; // coluna, linha, exibir?
    int orides;
    QPixmap *pix;

public slots:
    void openImage(QString arquivo);
    void saveImage(QString arquivo);
    void zeroPontos(int inicio);
    void imageInfo(int enable);
    void drawZoom(int x, int y);
    void fixImageDepth();

signals:
    void clicked();
    void moved();
    void explain(const QString&);

protected:
    virtual void paintEvent(QPaintEvent*);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mousePressEvent(QMouseEvent* e);

private:
};

#endif // Image_h

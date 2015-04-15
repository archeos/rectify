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

#ifndef MainWindow_h
#define MainWindow_h

#include "ui_MainWindow.h"
#include "painel.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    virtual ~MainWindow();

    virtual int spinReturn( int spin );

public slots:
    virtual void resizeEvent( QResizeEvent * );
    virtual void opcoesGerais();
    virtual void limitPoints();
    virtual void setMinimumPoints( int min );
    virtual void maxChanged();
    virtual void abreImagem();
    virtual void salvaImagem();
    virtual void abreModelo();
    virtual void recebePontos( int x, int y );
    virtual void mudaImagem();
    virtual void updateActions();
    virtual void atualizaPontosOriginal();
    virtual void atualizaPontosRetificada();
    virtual void retornaPontos();
    virtual void linhas();
    virtual void limpar();
    virtual void dadosImagem( int x, int y, int e );
    virtual void redimensionar();
    virtual void retificaImagem();
    virtual void calculaProporcao();
    virtual void alteraAltura();
    virtual void alteraLargura();
    virtual void pontosMedianas();
    virtual void abreReport();
    virtual void aboutShow();
    virtual void paintEvent();

protected:
    Painel *painel;
    float ratio;
    int max_x;
    int max_y;

protected slots:
    virtual void languageChange();

private:
    void init();
};

#endif // MainWindow_h

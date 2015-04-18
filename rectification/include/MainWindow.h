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

class AboutDialog;
class Panel;
class QTabBar;

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    virtual ~MainWindow();

    virtual int spinReturn( int spin );
    QColor cursorColor; // ...

public slots:
    virtual void resizeEvent( QResizeEvent * );
    virtual void opcoesGerais();
    virtual void limitPoints();
    virtual void setMinimumPoints( int min );
    virtual void maxChanged();
    virtual void openImage();
    virtual void openImage(const QString& filename);
    virtual void saveImage();
    virtual void saveImage(const QString& filename);
    virtual void openModel();
    virtual void openModel(const QString& filename);
    virtual void recebePontos( int x, int y );
    virtual void mudaImage();
    virtual void updateActions();
    virtual void atualizaPontosOriginal();
    virtual void atualizaPontosRetificada();
    virtual void retornaPontos();
    virtual void linhas();
    virtual void limpar();
    virtual void dadosImage( int x, int y, int e );
    virtual void redimensionar();
    virtual void retificaImage();
    virtual void calculaProporcao();
    virtual void alteraAltura();
    virtual void alteraLargura();
    virtual void pontosMedianas();
    virtual void showReport();
    virtual void aboutShow();
    virtual void paintEvent();
    virtual void importCSV();
    void setCursorColor();

protected:
    Panel* panel;
    float ratio;
    int max_x;
    int max_y;

protected slots:
    virtual void languageChange();

private:
    void init();
    QTabBar* tabBar;
    AboutDialog* aboutDialog;
    QString cwd; // Current working directory for file dialogs.
};

#endif // MainWindow_h

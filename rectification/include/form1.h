#ifndef FORM1_H
#define FORM1_H

#include "ui_form1.h"
#include "painel.h"

class Form1 : public Q3MainWindow, public Ui::Form1
{
    Q_OBJECT

public:
    Form1(QWidget* parent = 0);
    virtual ~Form1();

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

#endif // FORM1_H

/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
#include <q3filedialog.h>
#include <qvalidator.h>
#include <qmessagebox.h>
//Added by qt3to4:
#include <QResizeEvent>
#include <math.h>
#include "form2.h"
#include "about.h"

extern Form2 *form2;
extern About *about;

/*****************************  
*  Funções Gerais de controle           *
*****************************/

void Form1::init()
{
    // Initial values
    ratio=0.0;
    max_x=0;
    max_y=0;

    // Create painel object and insert it into layout -  for tabWidget 735 x 594
    painel = new Painel(this,"original",0);
    painel->reparent(tabWidget2,0,QPoint(0,0));
    painel->setGeometry(10,35,715,549);
	
    // Validators
    XiEdit->setValidator( new QIntValidator( XiEdit ));
    YiEdit->setValidator( new QIntValidator( YiEdit ));
    XfEdit->setValidator( new QIntValidator( XfEdit ));
    YfEdit->setValidator( new QIntValidator( YfEdit ));
    XoEdit->setValidator( new QDoubleValidator( XoEdit ));
    YoEdit->setValidator( new QDoubleValidator( YoEdit ));
    XdEdit->setValidator( new QDoubleValidator( XdEdit ));
    YdEdit->setValidator( new QDoubleValidator( YdEdit ));
    alturaEdit->setValidator( new QIntValidator( alturaEdit ));
    larguraEdit->setValidator( new QIntValidator( larguraEdit ));
}

void Form1::resizeEvent (QResizeEvent *)
{
	QRect tab2 = tabWidget2->geometry();
	if ((tab2.width()<100)||(tab2.height()<100))
		return;
	painel->setGeometry(10,35,tab2.width()-20,tab2.height()-45);
}

void Form1::opcoesGerais()
{
    if (checkBox1->isChecked())
        groupBox4->setEnabled(true);
    else
        groupBox4->setEnabled(false);
    painel->atualizaImagem();
}

void Form1::minimosPontos()
{
    // Limites mínimos, de acordo com o tipo de transformação
    switch (comboBox1->currentItem())
    {
    case 0 : ajustaPontos(3); break; // Afim Corpo Rígido
    case 1: ajustaPontos(3); break; // Afim Geral
    case 2: ajustaPontos(3); break; // Afim Isogonal
    case 3: ajustaPontos(3); break; // Afim Ortogonal
    case 4: ajustaPontos(6); break; // Linear Direta
    case 5: ajustaPontos(4); break; // Prejetiva
    }
}

void Form1::ajustaPontos(int min)
{
    // Função que ajusta a quantidade de pontos a ser medida
    spinTotal->setMinValue(min);
    if (spinTotal->value()<min)
    {
        spinTotal->setValue(min);
        spinAtual->setValue(1);
        spinAtual->setMaxValue(min);    
    }
}

void Form1::maxChanged()
{
    // Limita a quantidade de pontos do atual, de acordo com o total
    spinAtual->setMaxValue(spinTotal->value());
    painel->zeraPontos(spinTotal->value());
}

/*****************************  
*  Entrada e saída de imagens           *
*****************************/
void Form1::abreImagem()
{
    // Recebe nome da imagem e abre imagem original
    QString arquivo_nome = Q3FileDialog::getOpenFileName(".",QString::null,this,"Open File Dialog","Select one image ORIGINAL to load") ;
    if (arquivo_nome=="")
        return;
    painel->abrirImagem(arquivo_nome);
}

void Form1::salvaImagem()
{
   // Recebe nome da imagem e salva imagem retificada
    QString filename = Q3FileDialog::getSaveFileName(".",QString::null,this,"Save File Dialog","Choose one name to save RECTIFED image") ;
    if (filename=="")
        return;
    // Verifica se arquivo ja existe
    if ( QFile::exists( filename ) &&
        QMessageBox::warning(
            this,
            tr("Warning: Overwrite File?"),
            tr("A file called %1 already exists. "
                "Do you want to overwrite it?")
                .arg( filename ),
            tr("&Yes"), tr("&No"),
            QString::null, 0, 1 ) )
        return;
    painel->salvarImagem(filename);
}

void Form1::abreModelo()
{
    // Recebe nome da imagem e abre o modelo
    QString arquivo_nome = Q3FileDialog::getOpenFileName(".",QString::null,this,"Open File Dialog","Select a MODEL image to load") ;
    if (arquivo_nome=="")
        return;
    painel->abrirModelo(arquivo_nome);
}

void Form1::recebePontos(int x, int y)
{
    // Recebe pontos diretamente do mouse da classe imagem
    if (!tabWidget2->currentPageIndex())
    {
        XiEdit->setText(QString::number(x));
        YiEdit->setText(QString::number(y));
    }
    else
    {
        XfEdit->setText(QString::number(x));
        YfEdit->setText(QString::number(y));
    }
}

int Form1::spinReturn(int spin)
{
    //  0 - Spin atual
    //  1- Spin total
    //  2 - CheckBox 1
    //  3 - CheckBox 2
    switch (spin)
    {     
           case 0 : return spinAtual->value(); break;
           case 1 : return spinTotal->value(); break;
           case 2: return checkBox1->isChecked(); break;
           case 3: return checkBox2->isChecked(); break;
    }
}

void Form1::mudaImagem()
{
    if (tabWidget2->currentPageIndex())
    {
        painel->mudaRetificada();
        XiEdit->setEnabled(false);
        YiEdit->setEnabled(false);
        XfEdit->setEnabled(true);
        YfEdit->setEnabled(true);
        openButton->setEnabled(false);
        retButton->setEnabled(true);
        saveButton->setEnabled(true);
    }
    else
    {
        XiEdit->setEnabled(true);
        YiEdit->setEnabled(true);
        XfEdit->setEnabled(false);
        YfEdit->setEnabled(false); 
        painel->mudaOriginal();
        openButton->setEnabled(true);
        retButton->setEnabled(false);
        saveButton->setEnabled(false);
    }
}

void Form1::atualizaPontosOriginal()
{
    int x,y;
    x=XiEdit->text().toInt();
    y=YiEdit->text().toInt();
    // Verifica se os pontos estão dentro da imagem
    if (x<0) XiEdit->setText("0");
    if (y<0) YiEdit->setText("0");
    if (x>max_x) XiEdit->setText(QString::number(max_x));
    if (y>max_y) YiEdit->setText(QString::number(max_y));
    // Atualiza os pontos da imagem original, quando modificados na caixa de texto    
    painel->atualizaPontosOriginal(spinAtual->value()-1,x,y);
    painel->atualizaImagem();
}


void Form1::atualizaPontosRetificada()
{
    int x,y;
    x=XfEdit->text().toInt();
    y=YfEdit->text().toInt();
    // Verifica se os pontos estão dentro da imagem
    if (x<0) XfEdit->setText("0");
    if (y<0) YfEdit->setText("0");
    if (x>max_x) XfEdit->setText(QString::number(max_x));
    if (y>max_y) YfEdit->setText(QString::number(max_y));
    // Atualiza os pontos da imagem retificada, quando modificados na caixa de texto
    painel->atualizaPontosRetificada(spinAtual->value()-1,XfEdit->text().toInt(),YfEdit->text().toInt());    painel->atualizaImagem();
}

void Form1::retornaPontos()
{    
    // Retorna os pontos de Imagem para este formulário
    XiEdit->setText(QString::number(painel->retornaPontos(0,spinAtual->value()-1)));
    YiEdit->setText(QString::number(painel->retornaPontos(1,spinAtual->value()-1)));    
    XfEdit->setText(QString::number(painel->retornaPontos(2,spinAtual->value()-1)));
    YfEdit->setText(QString::number(painel->retornaPontos(3,spinAtual->value()-1)));
}

void Form1::linhas()
{
    // Caso mudança de linhas x não linhas
    painel->atualizaImagem();
}

void Form1::limpar()
{
   // Limpa os dados de pontos
   painel->zeraPontos(0);
   spinAtual->setValue(1);
   retornaPontos();
}

void Form1::dadosImagem( int x, int y, int e )
{
    // Retorna a informação das imagens
    if (e)
    {
        larguraEdit->setEnabled(true);
        alturaEdit->setEnabled(true);
        redimButton->setEnabled(true);
        modeloButton->setEnabled(true);
    }
    else
    {
        larguraEdit->setEnabled(false);
        alturaEdit->setEnabled(false);
        redimButton->setEnabled(false);
        modeloButton->setEnabled(false);
    }
    larguraEdit->setText(QString::number(x));
    alturaEdit->setText(QString::number(y));
    max_x=x-1;
    max_y=y-1;
}

void Form1::redimensionar()
{
    // Redimensiona o tamenho da tela retificada
    painel->redimensiona(larguraEdit->text().toInt(),alturaEdit->text().toInt());
}

void Form1::retificaImagem()
{
    form2->mensagem(">>> Rectification begins <<<\n");
    form2->mensagem("Transformation : "+ comboBox1->currentText()+"\n");
    form2->mensagem("Interpolation : "+ comboBox2->currentText()+"\n");
    painel->retificaImagem(comboBox1->currentItem(),comboBox2->currentItem(),spinTotal->value());
}

void Form1::calculaProporcao()
{
    int a,b,c,d;
    a=XoEdit->text().toInt();
    b=YoEdit->text().toInt();
    c=XdEdit->text().toInt();
    d=YdEdit->text().toInt();
    // Calcula a proporcao X/Y
    if ((a-c==0.0)||(b-d==0.0))
        ratio=0.0;
    else
        ratio=fabs(a-c)/fabs(b-d);
    
    ratioLabel->setText(QString::number(ratio));
}

void Form1::alteraAltura()
{
    int e=larguraEdit->text().toInt();
    // Altera automaticamente a altura, se proporções estiver selecionada
    if (checkBox1->isChecked())
        alturaEdit->setText(QString::number(ceil(e/ratio)));
}

void Form1::alteraLargura()
{
    int f=alturaEdit->text().toInt();
    // Altera automaticamente a largura, se proporções estiver selecionada
    if (checkBox1->isChecked())
        larguraEdit->setText(QString::number(floor(f*ratio)));
}


void Form1::pontosMedianas()
{
    // Cria pontos nas medianas de um quadrado    
    if (painel->pontosMedianas())
 spinTotal->setValue(10);
}

/*
       Funções do report  
*/

void Form1::abreReport()
{
    form2->show();
}

void Form1::aboutShow()
{
    about->show();
}

/*
      Repaint zoom
*/  

void Form1::paintEvent()
{
    zoomLabel->setPixmap(*zoomLabel->pixmap());
}

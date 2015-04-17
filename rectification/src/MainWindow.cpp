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

#include "MainWindow.h"
#include "ReportDialog.h"
#include "AboutDialog.h"
#include "Panel.h"

#include <QtGui/QValidator>
#include <QtGui/QCursor>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtGui/QResizeEvent>
#include <QtGui/QTabBar>
#include <QtGui/QVBoxLayout>

#include <cmath>

extern ReportDialog* reportDialog;

/*
 *  Constructs a MainWindow as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */
MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setupUi(this);

    statusBar();
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
MainWindow::~MainWindow()
{
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void MainWindow::languageChange()
{
    retranslateUi(this);
}

/*****************************
*  Funções Gerais de controle           *
*****************************/

void MainWindow::init()
{
    // File actions.
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(openImage()));
    connect(actionSave, SIGNAL(triggered()), this, SLOT(saveImage()));
    connect(actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    // Edit actions.
    connect(actionRectify, SIGNAL(triggered()), this, SLOT(retificaImage()));

    // View actions.
    connect(actionReport, SIGNAL(triggered()), this, SLOT(showReport()));

    // Help actions.
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(aboutShow()));

    aboutDialog = new AboutDialog(this);

    // Initial values
    ratio = 0.0;
    max_x = 0;
    max_y = 0;

    // Create panel object and insert it into layout -  for tabWidget 735 x 594
    tabBar = new QTabBar(imageArea);
    tabBar->addTab("Original");
    tabBar->addTab("Rectified");
    panel = new Panel(imageArea);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(tabBar);
    layout->addWidget(panel);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    imageArea->setLayout(layout);

//     panel->reparent(tabWidget2, 0, QPoint(0, 0));
//     tabWidget2->setMinimumSize(600, 400);
    repaint();

    // Validators
    XoEdit->setValidator( new QDoubleValidator( XoEdit ));
    YoEdit->setValidator( new QDoubleValidator( YoEdit ));
    XdEdit->setValidator( new QDoubleValidator( XdEdit ));
    YdEdit->setValidator( new QDoubleValidator( YdEdit ));
    alturaEdit->setValidator( new QIntValidator( alturaEdit ));
    larguraEdit->setValidator( new QIntValidator( larguraEdit ));

    connect(modeloButton, SIGNAL(clicked()), this, SLOT(openModel()));
    connect(tabBar, SIGNAL(currentChanged(int)), this, SLOT(mudaImage()));

    // Coordinate inputs.
    connect(XiEdit, SIGNAL(editingFinished()), this, SLOT(atualizaPontosOriginal()));
    connect(XiEdit, SIGNAL(valueChanged(int)), this, SLOT(atualizaPontosOriginal()));
    connect(YiEdit, SIGNAL(editingFinished()), this, SLOT(atualizaPontosOriginal()));
    connect(YiEdit, SIGNAL(valueChanged(int)), this, SLOT(atualizaPontosOriginal()));
    connect(XfEdit, SIGNAL(editingFinished()), this, SLOT(atualizaPontosRetificada()));
    connect(XfEdit, SIGNAL(valueChanged(int)), this, SLOT(atualizaPontosRetificada()));
    connect(YfEdit, SIGNAL(editingFinished()), this, SLOT(atualizaPontosRetificada()));
    connect(YfEdit, SIGNAL(valueChanged(int)), this, SLOT(atualizaPontosRetificada()));

    // Update action states.
    updateActions();
}

void MainWindow::resizeEvent(QResizeEvent *)
{
//     QRect rect = tabWidget2->geometry();
//     if ((rect.width() < 100) || (rect.height() < 100))
//         return;
//     // TODO thats ugly.
//     panel->setGeometry(10, 35, rect.width() - 20, rect.height() - 45);
}

void MainWindow::opcoesGerais()
{
    if (checkBox1->isChecked())
        groupBox4->setEnabled(true);
    else
        groupBox4->setEnabled(false);
    panel->atualizaImage();
}

void MainWindow::limitPoints()
{
    // Limit minimum point count required by transformation algorythmus.
    switch (transformation->currentItem())
    {
    case 0 :
        setMinimumPoints(3);
        break; // Afim Corpo Rígido
    case 1:
        setMinimumPoints(3);
        break; // Afim Geral
    case 2:
        setMinimumPoints(3);
        break; // Afim Isogonal
    case 3:
        setMinimumPoints(3);
        break; // Afim Ortogonal
    case 4:
        setMinimumPoints(6);
        break; // Linear Direta
    case 5:
        setMinimumPoints(4);
        break; // Prejetiva
    }
}

void MainWindow::setMinimumPoints(int min)
{
    // Apply limited point range.
    spinTotal->setMinValue(min);
    if (spinTotal->value() < min)
    {
        spinTotal->setValue(min);
        spinAtual->setValue(1);
        spinAtual->setMaxValue(min);
    }
}

void MainWindow::maxChanged()
{
    // Limita a quantidade de pontos do atual, de acordo com o total
    spinAtual->setMaxValue(spinTotal->value());
    panel->zeraPontos(spinTotal->value());
}

/*****************************
*  Entrada e saída de imagens           *
*****************************/
void MainWindow::openImage()
{
    // Recebe nome da imagem e abre imagem original
    QString filename = QFileDialog::getOpenFileName(".", QString::null, this, "Open File Dialog", "Select one image ORIGINAL to load") ;
    if (filename == "")
        return;
    openImage(filename);
}

void MainWindow::openImage(const QString& filename)
{
    panel->abrirImage(filename);
}

void MainWindow::saveImage()
{
    // Recebe nome da imagem e salva imagem retificada
    QString filename = QFileDialog::getSaveFileName(".", QString::null, this, "Save File Dialog", "Choose one name to save RECTIFED image") ;
    if (filename == "")
        return;
    // Verifica se arquivo ja existe
    if ( QFile::exists(filename) &&
            QMessageBox::warning(
                this,
                tr("Warning: Overwrite File?"),
                tr("A file called %1 already exists. "
                   "Do you want to overwrite it?")
                .arg( filename ),
                tr("&Yes"), tr("&No"),
                QString::null, 0, 1 ) )
        return;
    saveImage(filename);
}

void MainWindow::saveImage(const QString& filename)
{
    panel->salvarImage(filename);
}

void MainWindow::openModel()
{
    // Recebe nome da imagem e abre o modelo
    QString filename = QFileDialog::getOpenFileName(".", QString::null, this, "Open File Dialog", "Select a MODEL image to load") ;
    if (filename == "")
        return;
    openModel(filename);
}

void MainWindow::openModel(const QString& filename)
{
    panel->abrirModelo(filename);
}

void MainWindow::recebePontos(int x, int y)
{
    // Recebe pontos diretamente do mouse da classe imagem
    if (tabBar->currentIndex() == 0)
    {
        XiEdit->disconnect(SIGNAL(valueChanged(int)));
        YiEdit->disconnect(SIGNAL(valueChanged(int)));
        XiEdit->setValue(x);
        YiEdit->setValue(y);
        connect(XiEdit, SIGNAL(valueChanged(int)), this, SLOT(atualizaPontosOriginal()));
        connect(YiEdit, SIGNAL(valueChanged(int)), this, SLOT(atualizaPontosOriginal()));
    }
    else if (tabBar->currentIndex() == 1)
    {
        XfEdit->disconnect(SIGNAL(valueChanged(int)));
        YfEdit->disconnect(SIGNAL(valueChanged(int)));
        XfEdit->setValue(x);
        YfEdit->setValue(y);
        connect(XfEdit, SIGNAL(valueChanged(int)), this, SLOT(atualizaPontosRetificada()));
        connect(YfEdit, SIGNAL(valueChanged(int)), this, SLOT(atualizaPontosRetificada()));
    }
}

int MainWindow::spinReturn(int spin)
{
    //  0 - Spin atual
    //  1- Spin total
    //  2 - CheckBox 1
    //  3 - CheckBox 2
    switch (spin)
    {
    case 0 :
        return spinAtual->value();
        break;
    case 1 :
        return spinTotal->value();
        break;
    case 2:
        return checkBox1->isChecked();
        break;
    case 3:
        return checkBox2->isChecked();
        break;
    }
}

void MainWindow::mudaImage()
{
    if (tabBar->currentIndex() == 1)
    {
        panel->mudaRetificada();
    }
    else
    {
        panel->mudaOriginal();
    }
    updateActions();
}

void MainWindow::updateActions()
{
    if (tabBar->currentIndex() == 1)
    {
        XiEdit->setEnabled(false);
        YiEdit->setEnabled(false);
        XfEdit->setEnabled(true);
        YfEdit->setEnabled(true);
        actionOpen->setEnabled(false);
        actionRectify->setEnabled(true);
        actionSave->setEnabled(true);
    }
    else
    {
        XiEdit->setEnabled(true);
        YiEdit->setEnabled(true);
        XfEdit->setEnabled(false);
        YfEdit->setEnabled(false);
        actionOpen->setEnabled(true);
        actionRectify->setEnabled(false);
        actionSave->setEnabled(false);
    }
}

void MainWindow::atualizaPontosOriginal()
{
    int x, y;
    x = XiEdit->value();
    y = YiEdit->value();
    XiEdit->disconnect(SIGNAL(valueChanged(int)));
    YiEdit->disconnect(SIGNAL(valueChanged(int)));
    // Verifica se os pontos estão dentro da imagem
    if (x > max_x) XiEdit->setValue(max_x);
    if (y > max_y) YiEdit->setValue(max_y);
    // Atualiza os pontos da imagem original, quando modificados na caixa de texto
    panel->atualizaPontosOriginal(spinAtual->value() - 1, x, y);
    panel->atualizaImage();
    connect(XiEdit, SIGNAL(valueChanged(int)), this, SLOT(atualizaPontosOriginal()));
    connect(YiEdit, SIGNAL(valueChanged(int)), this, SLOT(atualizaPontosOriginal()));
}


void MainWindow::atualizaPontosRetificada()
{
    int x, y;
    x = XfEdit->value();
    y = YfEdit->value();
    XfEdit->disconnect(SIGNAL(valueChanged(int)));
    YfEdit->disconnect(SIGNAL(valueChanged(int)));
    // Verifica se os pontos estão dentro da imagem
    if (x > max_x) XfEdit->setValue(max_x);
    if (y > max_y) YfEdit->setValue(max_y);
    // Atualiza os pontos da imagem retificada, quando modificados na caixa de texto
    panel->atualizaPontosRetificada(spinAtual->value() - 1, XfEdit->value(), YfEdit->value());
    panel->atualizaImage();
    connect(XfEdit, SIGNAL(valueChanged(int)), this, SLOT(atualizaPontosRetificada()));
    connect(YfEdit, SIGNAL(valueChanged(int)), this, SLOT(atualizaPontosRetificada()));
}

void MainWindow::retornaPontos()
{
    // Retorna os pontos deI imagem para este formulário
    XiEdit->disconnect(SIGNAL(valueChanged(int)));
    YiEdit->disconnect(SIGNAL(valueChanged(int)));
    XfEdit->disconnect(SIGNAL(valueChanged(int)));
    YfEdit->disconnect(SIGNAL(valueChanged(int)));
    XiEdit->setValue(panel->retornaPontos(0, spinAtual->value() - 1));
    YiEdit->setValue(panel->retornaPontos(1, spinAtual->value() - 1));
    XfEdit->setValue(panel->retornaPontos(2, spinAtual->value() - 1));
    YfEdit->setValue(panel->retornaPontos(3, spinAtual->value() - 1));
    connect(XiEdit, SIGNAL(valueChanged(int)), this, SLOT(atualizaPontosOriginal()));
    connect(YiEdit, SIGNAL(valueChanged(int)), this, SLOT(atualizaPontosOriginal()));
    connect(XfEdit, SIGNAL(valueChanged(int)), this, SLOT(atualizaPontosRetificada()));
    connect(YfEdit, SIGNAL(valueChanged(int)), this, SLOT(atualizaPontosRetificada()));
}

void MainWindow::linhas()
{
    // Caso mudança de linhas x não linhas
    panel->atualizaImage();
}

void MainWindow::limpar()
{
    // Limpa os dados de pontos
    panel->zeraPontos(0);
    spinAtual->setValue(1);
    retornaPontos();
}

void MainWindow::dadosImage( int x, int y, int e )
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
    max_x = x - 1;
    max_y = y - 1;
}

void MainWindow::redimensionar()
{
    // Redimensiona o tamenho da tela retificada
    panel->redimensiona(larguraEdit->text().toInt(), alturaEdit->text().toInt());
}

void MainWindow::retificaImage()
{
    reportDialog->append(">>> Rectification begins <<<");
    reportDialog->append("Transformation : " + transformation->currentText());
    reportDialog->append("Interpolation : " + interpolation->currentText());
    panel->retificaImage(transformation->currentItem(), interpolation->currentItem(), spinTotal->value());
}

void MainWindow::calculaProporcao()
{
    int a, b, c, d;
    a = XoEdit->text().toInt();
    b = YoEdit->text().toInt();
    c = XdEdit->text().toInt();
    d = YdEdit->text().toInt();
    // Calcula a proporcao X/Y
    if ((a - c == 0.0) || (b - d == 0.0))
        ratio = 0.0;
    else
        ratio = fabs(a - c) / fabs(b - d);

    ratioLabel->setText(QString::number(ratio));
}

void MainWindow::alteraAltura()
{
    int e = larguraEdit->text().toInt();
    // Altera automaticamente a altura, se proporções estiver selecionada
    if (checkBox1->isChecked())
        alturaEdit->setText(QString::number(ceil(e / ratio)));
}

void MainWindow::alteraLargura()
{
    int f = alturaEdit->text().toInt();
    // Altera automaticamente a largura, se proporções estiver selecionada
    if (checkBox1->isChecked())
        larguraEdit->setText(QString::number(floor(f * ratio)));
}


void MainWindow::pontosMedianas()
{
    // Cria pontos nas medianas de um quadrado
    if (panel->pontosMedianas())
        spinTotal->setValue(10);
}

/*
       Funções do report
*/

void MainWindow::showReport()
{
    reportDialog->setVisible(!reportDialog->isVisible());
}

void MainWindow::aboutShow()
{
    aboutDialog->show();
}

/*
      Repaint zoom
*/
void MainWindow::paintEvent()
{
    zoomLabel->setPixmap(*zoomLabel->pixmap());
}

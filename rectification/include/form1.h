/********************************************************************************
** Form generated from reading ui file 'form1.ui'
**
** Created: Fri Jan 18 12:02:54 2008
**      by: Qt User Interface Compiler version 4.2.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef FORM1_H
#define FORM1_H

#include <Qt3Support/Q3GroupBox>
#include <Qt3Support/Q3MainWindow>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "painel.h"
#include <QtGui/QStyle>

class Ui_Form1
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget2;
    QWidget *tab;
    QWidget *tab1;
    QVBoxLayout *vboxLayout;
    QLabel *EfotoLabel1;
    QLabel *pixmapLabel2;
    QLabel *LabelRetifica;
    Q3GroupBox *groupBox1;
    QToolButton *openButton;
    QToolButton *saveButton;
    QToolButton *aboutButton;
    QToolButton *retButton;
    Q3GroupBox *groupBox3;
    QLabel *textLabel3;
    QLabel *textLabel2;
    QComboBox *comboBox2;
    QComboBox *comboBox1;
    Q3GroupBox *groupBox2;
    QGridLayout *gridLayout1;
    QHBoxLayout *hboxLayout;
    QLabel *origemLinhaColunaLabel;
    QLineEdit *XiEdit;
    QLabel *origemLinhaLabel;
    QLineEdit *YiEdit;
    QHBoxLayout *hboxLayout1;
    QLabel *destinoColunaLabel;
    QLineEdit *XfEdit;
    QLabel *destinoLinhaLabel;
    QLineEdit *YfEdit;
    QLabel *LabelOrigem;
    QLabel *LabelDestino;
    QHBoxLayout *hboxLayout2;
    QVBoxLayout *vboxLayout1;
    QLabel *LabelTotal;
    QSpinBox *spinTotal;
    QVBoxLayout *vboxLayout2;
    QLabel *LabelAtual;
    QSpinBox *spinAtual;
    QVBoxLayout *vboxLayout3;
    QSpacerItem *spacerItem;
    QPushButton *limpaButton;
    QHBoxLayout *hboxLayout3;
    Q3GroupBox *groupBox19;
    QGridLayout *gridLayout2;
    QVBoxLayout *vboxLayout4;
    QLabel *colunaLabel;
    QLabel *coluna;
    QLabel *linhaLabel;
    QLabel *linha;
    QLabel *zoomLabel;
    Q3GroupBox *groupBox4;
    QLabel *textLabel9;
    QLabel *textLabel11;
    QLabel *textLabel10;
    QLabel *textLabel12;
    QLineEdit *YoEdit;
    QLineEdit *YdEdit;
    QLineEdit *XdEdit;
    QLineEdit *XoEdit;
    QLabel *ratioLabel;
    QLabel *proporcaoLabel;
    QLabel *ajustesLabel1;
    Q3GroupBox *groupBox9;
    QPushButton *medianaButton;
    QCheckBox *checkBox1;
    QCheckBox *checkBox2;
    QPushButton *reportButton;
    Q3GroupBox *groupBox6;
    QLabel *larguraLabel;
    QLabel *alturaLabel;
    QLabel *textLabel6;
    QLineEdit *larguraEdit;
    QLineEdit *alturaEdit;
    QLabel *textLabel5;
    QLabel *varAlturaLabel;
    QLabel *varLarguraLabel;
    QToolButton *modeloButton;
    QPushButton *redimButton;
    QSpacerItem *spacerItem1;

    void setupUi(Q3MainWindow *Form1)
    {
    Form1->setObjectName(QString::fromUtf8("Form1"));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(7), static_cast<QSizePolicy::Policy>(7));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(Form1->sizePolicy().hasHeightForWidth());
    Form1->setSizePolicy(sizePolicy);
    Form1->setWindowIcon(QIcon(QString::fromUtf8("images/identity.png")));
    widget = new QWidget(Form1);
    widget->setObjectName(QString::fromUtf8("widget"));
    widget->setGeometry(QRect(0, 0, 968, 776));
    gridLayout = new QGridLayout(widget);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    tabWidget2 = new QTabWidget(widget);
    tabWidget2->setObjectName(QString::fromUtf8("tabWidget2"));
    QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(tabWidget2->sizePolicy().hasHeightForWidth());
    tabWidget2->setSizePolicy(sizePolicy1);
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    tabWidget2->addTab(tab, QApplication::translate("Form1", "Original", 0, QApplication::UnicodeUTF8));
    tab1 = new QWidget();
    tab1->setObjectName(QString::fromUtf8("tab1"));
    tabWidget2->addTab(tab1, QApplication::translate("Form1", "Rectified", 0, QApplication::UnicodeUTF8));

    gridLayout->addWidget(tabWidget2, 0, 1, 5, 1);

    vboxLayout = new QVBoxLayout();
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    EfotoLabel1 = new QLabel(widget);
    EfotoLabel1->setObjectName(QString::fromUtf8("EfotoLabel1"));
    QFont font;
    font.setPointSize(14);
    font.setBold(true);
    font.setWeight(75);
    EfotoLabel1->setFont(font);
    EfotoLabel1->setAlignment(Qt::AlignCenter);
    EfotoLabel1->setWordWrap(false);

    vboxLayout->addWidget(EfotoLabel1);

    pixmapLabel2 = new QLabel(widget);
    pixmapLabel2->setObjectName(QString::fromUtf8("pixmapLabel2"));
    pixmapLabel2->setPixmap(QPixmap());
    pixmapLabel2->setAlignment(Qt::AlignCenter);
    pixmapLabel2->setWordWrap(false);

    vboxLayout->addWidget(pixmapLabel2);

    LabelRetifica = new QLabel(widget);
    LabelRetifica->setObjectName(QString::fromUtf8("LabelRetifica"));
    QFont font1;
    font1.setItalic(true);
    LabelRetifica->setFont(font1);
    LabelRetifica->setAlignment(Qt::AlignCenter);
    LabelRetifica->setWordWrap(false);

    vboxLayout->addWidget(LabelRetifica);


    gridLayout->addLayout(vboxLayout, 0, 0, 1, 1);

    groupBox1 = new Q3GroupBox(widget);
    groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
    QSizePolicy sizePolicy2(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(5));
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(groupBox1->sizePolicy().hasHeightForWidth());
    groupBox1->setSizePolicy(sizePolicy2);
    groupBox1->setMinimumSize(QSize(0, 86));
    groupBox1->setMaximumSize(QSize(201, 32767));
    groupBox1->setOrientation(Qt::Vertical);
    openButton = new QToolButton(groupBox1);
    openButton->setObjectName(QString::fromUtf8("openButton"));
    openButton->setGeometry(QRect(10, 20, 80, 26));
    openButton->setIcon(QIcon(QString::fromUtf8("images/folder.png")));
    openButton->setCheckable(false);
    openButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    saveButton = new QToolButton(groupBox1);
    saveButton->setObjectName(QString::fromUtf8("saveButton"));
    saveButton->setEnabled(false);
    saveButton->setGeometry(QRect(110, 20, 81, 26));
    saveButton->setIcon(QIcon(QString::fromUtf8("images/gnome-dev-floppy.png")));
    saveButton->setIconSize(QSize(20, 20));
    saveButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    aboutButton = new QToolButton(groupBox1);
    aboutButton->setObjectName(QString::fromUtf8("aboutButton"));
    aboutButton->setEnabled(true);
    aboutButton->setGeometry(QRect(111, 50, 80, 26));
    aboutButton->setIcon(QIcon(QString::fromUtf8("images/efoto2.png")));
    aboutButton->setIconSize(QSize(19, 19));
    aboutButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    retButton = new QToolButton(groupBox1);
    retButton->setObjectName(QString::fromUtf8("retButton"));
    retButton->setEnabled(false);
    retButton->setGeometry(QRect(10, 50, 80, 26));
    retButton->setIcon(QIcon(QString::fromUtf8("images/identity.png")));
    retButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    gridLayout->addWidget(groupBox1, 1, 0, 1, 1);

    groupBox3 = new Q3GroupBox(widget);
    groupBox3->setObjectName(QString::fromUtf8("groupBox3"));
    QSizePolicy sizePolicy3(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(5));
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(groupBox3->sizePolicy().hasHeightForWidth());
    groupBox3->setSizePolicy(sizePolicy3);
    groupBox3->setMinimumSize(QSize(0, 120));
    groupBox3->setMaximumSize(QSize(201, 32767));
    groupBox3->setOrientation(Qt::Vertical);
    textLabel3 = new QLabel(groupBox3);
    textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
    textLabel3->setGeometry(QRect(10, 70, 180, 16));
    textLabel3->setWordWrap(false);
    textLabel2 = new QLabel(groupBox3);
    textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
    textLabel2->setGeometry(QRect(10, 20, 180, 20));
    textLabel2->setWordWrap(false);
    comboBox2 = new QComboBox(groupBox3);
    comboBox2->setObjectName(QString::fromUtf8("comboBox2"));
    comboBox2->setGeometry(QRect(10, 90, 180, 21));
    comboBox1 = new QComboBox(groupBox3);
    comboBox1->setObjectName(QString::fromUtf8("comboBox1"));
    comboBox1->setGeometry(QRect(10, 40, 180, 21));

    gridLayout->addWidget(groupBox3, 3, 0, 1, 1);

    groupBox2 = new Q3GroupBox(widget);
    groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
    QSizePolicy sizePolicy4(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(groupBox2->sizePolicy().hasHeightForWidth());
    groupBox2->setSizePolicy(sizePolicy4);
    groupBox2->setMaximumSize(QSize(201, 32767));
    QFont font2;
    groupBox2->setFont(font2);
    groupBox2->setOrientation(Qt::Vertical);
    groupBox2->setColumnLayout(0, Qt::Vertical);
    groupBox2->layout()->setSpacing(6);
    groupBox2->layout()->setMargin(0);
    gridLayout1 = new QGridLayout(groupBox2->layout());
    gridLayout1->setAlignment(Qt::AlignTop);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    origemLinhaColunaLabel = new QLabel(groupBox2);
    origemLinhaColunaLabel->setObjectName(QString::fromUtf8("origemLinhaColunaLabel"));
    origemLinhaColunaLabel->setWordWrap(false);

    hboxLayout->addWidget(origemLinhaColunaLabel);

    XiEdit = new QLineEdit(groupBox2);
    XiEdit->setObjectName(QString::fromUtf8("XiEdit"));
    XiEdit->setAlignment(Qt::AlignRight);

    hboxLayout->addWidget(XiEdit);

    origemLinhaLabel = new QLabel(groupBox2);
    origemLinhaLabel->setObjectName(QString::fromUtf8("origemLinhaLabel"));
    origemLinhaLabel->setWordWrap(false);

    hboxLayout->addWidget(origemLinhaLabel);

    YiEdit = new QLineEdit(groupBox2);
    YiEdit->setObjectName(QString::fromUtf8("YiEdit"));
    YiEdit->setAlignment(Qt::AlignRight);

    hboxLayout->addWidget(YiEdit);


    gridLayout1->addLayout(hboxLayout, 2, 0, 1, 1);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    destinoColunaLabel = new QLabel(groupBox2);
    destinoColunaLabel->setObjectName(QString::fromUtf8("destinoColunaLabel"));
    destinoColunaLabel->setWordWrap(false);

    hboxLayout1->addWidget(destinoColunaLabel);

    XfEdit = new QLineEdit(groupBox2);
    XfEdit->setObjectName(QString::fromUtf8("XfEdit"));
    XfEdit->setFocusPolicy(Qt::StrongFocus);
    XfEdit->setAlignment(Qt::AlignRight);

    hboxLayout1->addWidget(XfEdit);

    destinoLinhaLabel = new QLabel(groupBox2);
    destinoLinhaLabel->setObjectName(QString::fromUtf8("destinoLinhaLabel"));
    destinoLinhaLabel->setWordWrap(false);

    hboxLayout1->addWidget(destinoLinhaLabel);

    YfEdit = new QLineEdit(groupBox2);
    YfEdit->setObjectName(QString::fromUtf8("YfEdit"));
    YfEdit->setAlignment(Qt::AlignRight);

    hboxLayout1->addWidget(YfEdit);


    gridLayout1->addLayout(hboxLayout1, 4, 0, 1, 1);

    LabelOrigem = new QLabel(groupBox2);
    LabelOrigem->setObjectName(QString::fromUtf8("LabelOrigem"));
    QFont font3;
    font3.setItalic(true);
    LabelOrigem->setFont(font3);
    LabelOrigem->setAlignment(Qt::AlignCenter);
    LabelOrigem->setWordWrap(false);

    gridLayout1->addWidget(LabelOrigem, 1, 0, 1, 1);

    LabelDestino = new QLabel(groupBox2);
    LabelDestino->setObjectName(QString::fromUtf8("LabelDestino"));
    QFont font4;
    font4.setItalic(true);
    LabelDestino->setFont(font4);
    LabelDestino->setAlignment(Qt::AlignCenter);
    LabelDestino->setWordWrap(false);

    gridLayout1->addWidget(LabelDestino, 3, 0, 1, 1);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setMargin(0);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    LabelTotal = new QLabel(groupBox2);
    LabelTotal->setObjectName(QString::fromUtf8("LabelTotal"));
    LabelTotal->setAlignment(Qt::AlignCenter);
    LabelTotal->setWordWrap(false);

    vboxLayout1->addWidget(LabelTotal);

    spinTotal = new QSpinBox(groupBox2);
    spinTotal->setObjectName(QString::fromUtf8("spinTotal"));
    spinTotal->setMaximum(20);
    spinTotal->setMinimum(3);

    vboxLayout1->addWidget(spinTotal);


    hboxLayout2->addLayout(vboxLayout1);

    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setSpacing(6);
    vboxLayout2->setMargin(0);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    LabelAtual = new QLabel(groupBox2);
    LabelAtual->setObjectName(QString::fromUtf8("LabelAtual"));
    LabelAtual->setAlignment(Qt::AlignCenter);
    LabelAtual->setWordWrap(false);

    vboxLayout2->addWidget(LabelAtual);

    spinAtual = new QSpinBox(groupBox2);
    spinAtual->setObjectName(QString::fromUtf8("spinAtual"));
    spinAtual->setMaximum(3);
    spinAtual->setMinimum(1);

    vboxLayout2->addWidget(spinAtual);


    hboxLayout2->addLayout(vboxLayout2);

    vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setSpacing(6);
    vboxLayout3->setMargin(0);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    spacerItem = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout3->addItem(spacerItem);

    limpaButton = new QPushButton(groupBox2);
    limpaButton->setObjectName(QString::fromUtf8("limpaButton"));
    QSizePolicy sizePolicy5(static_cast<QSizePolicy::Policy>(5), static_cast<QSizePolicy::Policy>(5));
    sizePolicy5.setHorizontalStretch(0);
    sizePolicy5.setVerticalStretch(0);
    sizePolicy5.setHeightForWidth(limpaButton->sizePolicy().hasHeightForWidth());
    limpaButton->setSizePolicy(sizePolicy5);
    limpaButton->setMaximumSize(QSize(50, 24));

    vboxLayout3->addWidget(limpaButton);


    hboxLayout2->addLayout(vboxLayout3);


    gridLayout1->addLayout(hboxLayout2, 0, 0, 1, 1);


    gridLayout->addWidget(groupBox2, 2, 0, 1, 1);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    groupBox19 = new Q3GroupBox(widget);
    groupBox19->setObjectName(QString::fromUtf8("groupBox19"));
    groupBox19->setMaximumSize(QSize(201, 125));
    groupBox19->setOrientation(Qt::Vertical);
    groupBox19->setColumnLayout(0, Qt::Vertical);
    groupBox19->layout()->setSpacing(6);
    groupBox19->layout()->setMargin(0);
    gridLayout2 = new QGridLayout(groupBox19->layout());
    gridLayout2->setAlignment(Qt::AlignTop);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    vboxLayout4 = new QVBoxLayout();
    vboxLayout4->setSpacing(6);
    vboxLayout4->setMargin(0);
    vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
    colunaLabel = new QLabel(groupBox19);
    colunaLabel->setObjectName(QString::fromUtf8("colunaLabel"));
    colunaLabel->setAlignment(Qt::AlignCenter);
    colunaLabel->setWordWrap(false);

    vboxLayout4->addWidget(colunaLabel);

    coluna = new QLabel(groupBox19);
    coluna->setObjectName(QString::fromUtf8("coluna"));
    coluna->setAlignment(Qt::AlignCenter);
    coluna->setWordWrap(false);

    vboxLayout4->addWidget(coluna);

    linhaLabel = new QLabel(groupBox19);
    linhaLabel->setObjectName(QString::fromUtf8("linhaLabel"));
    linhaLabel->setAlignment(Qt::AlignCenter);
    linhaLabel->setWordWrap(false);

    vboxLayout4->addWidget(linhaLabel);

    linha = new QLabel(groupBox19);
    linha->setObjectName(QString::fromUtf8("linha"));
    linha->setAlignment(Qt::AlignCenter);
    linha->setWordWrap(false);

    vboxLayout4->addWidget(linha);


    gridLayout2->addLayout(vboxLayout4, 0, 1, 1, 1);

    zoomLabel = new QLabel(groupBox19);
    zoomLabel->setObjectName(QString::fromUtf8("zoomLabel"));
    QSizePolicy sizePolicy6(static_cast<QSizePolicy::Policy>(1), static_cast<QSizePolicy::Policy>(1));
    sizePolicy6.setHorizontalStretch(0);
    sizePolicy6.setVerticalStretch(0);
    sizePolicy6.setHeightForWidth(zoomLabel->sizePolicy().hasHeightForWidth());
    zoomLabel->setSizePolicy(sizePolicy6);
    zoomLabel->setMinimumSize(QSize(100, 100));
    zoomLabel->setFrameShape(QFrame::Box);
    zoomLabel->setFrameShadow(QFrame::Raised);
    zoomLabel->setPixmap(QPixmap());
    zoomLabel->setScaledContents(true);
    zoomLabel->setWordWrap(false);

    gridLayout2->addWidget(zoomLabel, 0, 0, 1, 1);


    hboxLayout3->addWidget(groupBox19);

    groupBox4 = new Q3GroupBox(widget);
    groupBox4->setObjectName(QString::fromUtf8("groupBox4"));
    groupBox4->setEnabled(false);
    groupBox4->setMaximumSize(QSize(32767, 125));
    groupBox4->setOrientation(Qt::Vertical);
    textLabel9 = new QLabel(groupBox4);
    textLabel9->setObjectName(QString::fromUtf8("textLabel9"));
    textLabel9->setGeometry(QRect(10, 50, 20, 20));
    textLabel9->setWordWrap(false);
    textLabel11 = new QLabel(groupBox4);
    textLabel11->setObjectName(QString::fromUtf8("textLabel11"));
    textLabel11->setGeometry(QRect(100, 50, 20, 20));
    textLabel11->setWordWrap(false);
    textLabel10 = new QLabel(groupBox4);
    textLabel10->setObjectName(QString::fromUtf8("textLabel10"));
    textLabel10->setGeometry(QRect(10, 80, 20, 20));
    textLabel10->setWordWrap(false);
    textLabel12 = new QLabel(groupBox4);
    textLabel12->setObjectName(QString::fromUtf8("textLabel12"));
    textLabel12->setGeometry(QRect(100, 80, 20, 20));
    textLabel12->setWordWrap(false);
    YoEdit = new QLineEdit(groupBox4);
    YoEdit->setObjectName(QString::fromUtf8("YoEdit"));
    YoEdit->setGeometry(QRect(130, 50, 40, 21));
    YoEdit->setAlignment(Qt::AlignRight);
    YdEdit = new QLineEdit(groupBox4);
    YdEdit->setObjectName(QString::fromUtf8("YdEdit"));
    YdEdit->setGeometry(QRect(130, 80, 40, 21));
    YdEdit->setAlignment(Qt::AlignRight);
    XdEdit = new QLineEdit(groupBox4);
    XdEdit->setObjectName(QString::fromUtf8("XdEdit"));
    XdEdit->setGeometry(QRect(40, 80, 40, 21));
    XdEdit->setAlignment(Qt::AlignRight);
    XoEdit = new QLineEdit(groupBox4);
    XoEdit->setObjectName(QString::fromUtf8("XoEdit"));
    XoEdit->setGeometry(QRect(40, 50, 40, 21));
    XoEdit->setAlignment(Qt::AlignRight);
    ratioLabel = new QLabel(groupBox4);
    ratioLabel->setObjectName(QString::fromUtf8("ratioLabel"));
    ratioLabel->setGeometry(QRect(180, 80, 100, 20));
    ratioLabel->setAlignment(Qt::AlignCenter);
    ratioLabel->setWordWrap(false);
    proporcaoLabel = new QLabel(groupBox4);
    proporcaoLabel->setObjectName(QString::fromUtf8("proporcaoLabel"));
    proporcaoLabel->setGeometry(QRect(176, 50, 110, 20));
    proporcaoLabel->setAlignment(Qt::AlignCenter);
    proporcaoLabel->setWordWrap(false);
    ajustesLabel1 = new QLabel(groupBox4);
    ajustesLabel1->setObjectName(QString::fromUtf8("ajustesLabel1"));
    ajustesLabel1->setGeometry(QRect(10, 20, 270, 20));
    ajustesLabel1->setWordWrap(false);

    hboxLayout3->addWidget(groupBox4);

    groupBox9 = new Q3GroupBox(widget);
    groupBox9->setObjectName(QString::fromUtf8("groupBox9"));
    groupBox9->setMaximumSize(QSize(32767, 125));
    groupBox9->setOrientation(Qt::Vertical);
    medianaButton = new QPushButton(groupBox9);
    medianaButton->setObjectName(QString::fromUtf8("medianaButton"));
    medianaButton->setGeometry(QRect(20, 60, 180, 20));
    checkBox1 = new QCheckBox(groupBox9);
    checkBox1->setObjectName(QString::fromUtf8("checkBox1"));
    checkBox1->setGeometry(QRect(10, 16, 190, 21));
    checkBox1->setChecked(false);
    checkBox2 = new QCheckBox(groupBox9);
    checkBox2->setObjectName(QString::fromUtf8("checkBox2"));
    checkBox2->setGeometry(QRect(10, 36, 200, 21));
    reportButton = new QPushButton(groupBox9);
    reportButton->setObjectName(QString::fromUtf8("reportButton"));
    reportButton->setGeometry(QRect(20, 84, 180, 20));

    hboxLayout3->addWidget(groupBox9);

    groupBox6 = new Q3GroupBox(widget);
    groupBox6->setObjectName(QString::fromUtf8("groupBox6"));
    groupBox6->setMaximumSize(QSize(32767, 125));
    groupBox6->setOrientation(Qt::Vertical);
    larguraLabel = new QLabel(groupBox6);
    larguraLabel->setObjectName(QString::fromUtf8("larguraLabel"));
    larguraLabel->setGeometry(QRect(10, 19, 50, 20));
    larguraLabel->setWordWrap(false);
    alturaLabel = new QLabel(groupBox6);
    alturaLabel->setObjectName(QString::fromUtf8("alturaLabel"));
    alturaLabel->setGeometry(QRect(10, 49, 50, 20));
    alturaLabel->setWordWrap(false);
    textLabel6 = new QLabel(groupBox6);
    textLabel6->setObjectName(QString::fromUtf8("textLabel6"));
    textLabel6->setGeometry(QRect(105, 50, 50, 20));
    textLabel6->setWordWrap(false);
    larguraEdit = new QLineEdit(groupBox6);
    larguraEdit->setObjectName(QString::fromUtf8("larguraEdit"));
    larguraEdit->setGeometry(QRect(60, 20, 40, 21));
    alturaEdit = new QLineEdit(groupBox6);
    alturaEdit->setObjectName(QString::fromUtf8("alturaEdit"));
    alturaEdit->setGeometry(QRect(60, 50, 40, 21));
    textLabel5 = new QLabel(groupBox6);
    textLabel5->setObjectName(QString::fromUtf8("textLabel5"));
    textLabel5->setGeometry(QRect(105, 19, 50, 20));
    textLabel5->setWordWrap(false);
    varAlturaLabel = new QLabel(groupBox6);
    varAlturaLabel->setObjectName(QString::fromUtf8("varAlturaLabel"));
    varAlturaLabel->setGeometry(QRect(144, 50, 70, 20));
    varAlturaLabel->setAlignment(Qt::AlignCenter);
    varAlturaLabel->setWordWrap(false);
    varLarguraLabel = new QLabel(groupBox6);
    varLarguraLabel->setObjectName(QString::fromUtf8("varLarguraLabel"));
    varLarguraLabel->setGeometry(QRect(144, 20, 70, 20));
    varLarguraLabel->setAlignment(Qt::AlignCenter);
    varLarguraLabel->setWordWrap(false);
    modeloButton = new QToolButton(groupBox6);
    modeloButton->setObjectName(QString::fromUtf8("modeloButton"));
    modeloButton->setGeometry(QRect(120, 76, 80, 26));
    modeloButton->setIcon(QIcon(QString::fromUtf8("images/folder.png")));
    modeloButton->setCheckable(false);
    modeloButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    redimButton = new QPushButton(groupBox6);
    redimButton->setObjectName(QString::fromUtf8("redimButton"));
    redimButton->setGeometry(QRect(10, 76, 100, 26));
    redimButton->setIcon(QIcon(QString::fromUtf8("images/frame_edit.png")));
    redimButton->setIconSize(QSize(20, 20));

    hboxLayout3->addWidget(groupBox6);


    gridLayout->addLayout(hboxLayout3, 5, 0, 1, 2);

    spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout->addItem(spacerItem1, 4, 0, 1, 1);

    Form1->setCentralWidget(widget);
    QWidget::setTabOrder(spinTotal, spinAtual);
    QWidget::setTabOrder(spinAtual, XiEdit);
    QWidget::setTabOrder(XiEdit, YiEdit);
    QWidget::setTabOrder(YiEdit, XfEdit);
    QWidget::setTabOrder(XfEdit, YfEdit);
    QWidget::setTabOrder(YfEdit, comboBox1);
    QWidget::setTabOrder(comboBox1, comboBox2);
    QWidget::setTabOrder(comboBox2, XoEdit);
    QWidget::setTabOrder(XoEdit, YoEdit);
    QWidget::setTabOrder(YoEdit, XdEdit);
    QWidget::setTabOrder(XdEdit, YdEdit);
    QWidget::setTabOrder(YdEdit, checkBox1);
    QWidget::setTabOrder(checkBox1, checkBox2);
    QWidget::setTabOrder(checkBox2, medianaButton);
    QWidget::setTabOrder(medianaButton, reportButton);
    QWidget::setTabOrder(reportButton, larguraEdit);
    QWidget::setTabOrder(larguraEdit, alturaEdit);
    QWidget::setTabOrder(alturaEdit, redimButton);
    QWidget::setTabOrder(redimButton, tabWidget2);

    retranslateUi(Form1);

    QSize size(968, 776);
    size = size.expandedTo(Form1->minimumSizeHint());
    Form1->resize(size);

    QObject::connect(checkBox1, SIGNAL(stateChanged(int)), Form1, SLOT(opcoesGerais()));
    QObject::connect(comboBox1, SIGNAL(activated(QString)), Form1, SLOT(minimosPontos()));
    QObject::connect(spinTotal, SIGNAL(valueChanged(int)), Form1, SLOT(maxChanged()));
    QObject::connect(openButton, SIGNAL(clicked()), Form1, SLOT(abreImagem()));
    QObject::connect(tabWidget2, SIGNAL(currentChanged(QWidget*)), Form1, SLOT(mudaImagem()));
    QObject::connect(XiEdit, SIGNAL(lostFocus()), Form1, SLOT(atualizaPontosOriginal()));
    QObject::connect(YiEdit, SIGNAL(lostFocus()), Form1, SLOT(atualizaPontosOriginal()));
    QObject::connect(XfEdit, SIGNAL(lostFocus()), Form1, SLOT(atualizaPontosRetificada()));
    QObject::connect(YfEdit, SIGNAL(lostFocus()), Form1, SLOT(atualizaPontosRetificada()));
    QObject::connect(spinAtual, SIGNAL(valueChanged(int)), Form1, SLOT(retornaPontos()));
    QObject::connect(checkBox2, SIGNAL(stateChanged(int)), Form1, SLOT(linhas()));
    QObject::connect(redimButton, SIGNAL(clicked()), Form1, SLOT(redimensionar()));
    QObject::connect(modeloButton, SIGNAL(clicked()), Form1, SLOT(abreModelo()));
    QObject::connect(retButton, SIGNAL(clicked()), Form1, SLOT(retificaImagem()));
    QObject::connect(saveButton, SIGNAL(clicked()), Form1, SLOT(salvaImagem()));
    QObject::connect(XdEdit, SIGNAL(lostFocus()), Form1, SLOT(calculaProporcao()));
    QObject::connect(XoEdit, SIGNAL(lostFocus()), Form1, SLOT(calculaProporcao()));
    QObject::connect(YdEdit, SIGNAL(lostFocus()), Form1, SLOT(calculaProporcao()));
    QObject::connect(YoEdit, SIGNAL(lostFocus()), Form1, SLOT(calculaProporcao()));
    QObject::connect(alturaEdit, SIGNAL(lostFocus()), Form1, SLOT(alteraLargura()));
    QObject::connect(larguraEdit, SIGNAL(lostFocus()), Form1, SLOT(alteraAltura()));
    QObject::connect(medianaButton, SIGNAL(clicked()), Form1, SLOT(pontosMedianas()));
    QObject::connect(reportButton, SIGNAL(clicked()), Form1, SLOT(abreReport()));
    QObject::connect(aboutButton, SIGNAL(clicked()), Form1, SLOT(aboutShow()));

    tabWidget2->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(Form1);
    } // setupUi

    void retranslateUi(Q3MainWindow *Form1)
    {
    Form1->setWindowTitle(QApplication::translate("Form1", "Efoto :: Rectification - v 1.2 - Dec 2006", 0, QApplication::UnicodeUTF8));
    tabWidget2->setTabText(tabWidget2->indexOf(tab), QApplication::translate("Form1", "Original", 0, QApplication::UnicodeUTF8));
    tabWidget2->setTabText(tabWidget2->indexOf(tab1), QApplication::translate("Form1", "Rectified", 0, QApplication::UnicodeUTF8));
    EfotoLabel1->setText(QApplication::translate("Form1", "E-FOTO", 0, QApplication::UnicodeUTF8));
    LabelRetifica->setText(QApplication::translate("Form1", "Rectification", 0, QApplication::UnicodeUTF8));
    groupBox1->setTitle(QApplication::translate("Form1", "Image", 0, QApplication::UnicodeUTF8));
    openButton->setText(QApplication::translate("Form1", "Open", 0, QApplication::UnicodeUTF8));
    saveButton->setText(QApplication::translate("Form1", "Save", 0, QApplication::UnicodeUTF8));
    aboutButton->setText(QApplication::translate("Form1", "About", 0, QApplication::UnicodeUTF8));
    retButton->setText(QApplication::translate("Form1", "Rectify", 0, QApplication::UnicodeUTF8));
    groupBox3->setTitle(QApplication::translate("Form1", "Rectification Options", 0, QApplication::UnicodeUTF8));
    textLabel3->setText(QApplication::translate("Form1", "Interpolation:", 0, QApplication::UnicodeUTF8));
    textLabel2->setText(QApplication::translate("Form1", "Transformation:", 0, QApplication::UnicodeUTF8));
    comboBox2->clear();
    comboBox2->addItem(QApplication::translate("Form1", "Nearest Neighbor", 0, QApplication::UnicodeUTF8));
    comboBox2->addItem(QApplication::translate("Form1", "Bi-linear", 0, QApplication::UnicodeUTF8));
    comboBox2->addItem(QApplication::translate("Form1", "Bi-cubic", 0, QApplication::UnicodeUTF8));
    comboBox2->addItem(QApplication::translate("Form1", "Lagrange", 0, QApplication::UnicodeUTF8));
    comboBox1->clear();
    comboBox1->addItem(QApplication::translate("Form1", "Non-Linear Rigid Body", 0, QApplication::UnicodeUTF8));
    comboBox1->addItem(QApplication::translate("Form1", "Linear General Affine", 0, QApplication::UnicodeUTF8));
    comboBox1->addItem(QApplication::translate("Form1", "Non-Linear Orthogonal", 0, QApplication::UnicodeUTF8));
    comboBox1->addItem(QApplication::translate("Form1", "Linear Isogonal", 0, QApplication::UnicodeUTF8));
    comboBox1->addItem(QApplication::translate("Form1", "DLT", 0, QApplication::UnicodeUTF8));
    comboBox1->addItem(QApplication::translate("Form1", "Projective", 0, QApplication::UnicodeUTF8));
    groupBox2->setTitle(QApplication::translate("Form1", "Control Points", 0, QApplication::UnicodeUTF8));
    origemLinhaColunaLabel->setText(QApplication::translate("Form1", "Column:", 0, QApplication::UnicodeUTF8));
    XiEdit->setText(QApplication::translate("Form1", "0", 0, QApplication::UnicodeUTF8));
    origemLinhaLabel->setText(QApplication::translate("Form1", "Line:", 0, QApplication::UnicodeUTF8));
    YiEdit->setText(QApplication::translate("Form1", "0", 0, QApplication::UnicodeUTF8));
    destinoColunaLabel->setText(QApplication::translate("Form1", "Column:", 0, QApplication::UnicodeUTF8));
    XfEdit->setText(QApplication::translate("Form1", "0", 0, QApplication::UnicodeUTF8));
    destinoLinhaLabel->setText(QApplication::translate("Form1", "Line:", 0, QApplication::UnicodeUTF8));
    YfEdit->setText(QApplication::translate("Form1", "0", 0, QApplication::UnicodeUTF8));
    LabelOrigem->setText(QApplication::translate("Form1", "Source:", 0, QApplication::UnicodeUTF8));
    LabelDestino->setText(QApplication::translate("Form1", "Destiny:", 0, QApplication::UnicodeUTF8));
    LabelTotal->setText(QApplication::translate("Form1", "Total", 0, QApplication::UnicodeUTF8));
    spinTotal->setToolTip(QApplication::translate("Form1", "Maximum number of control points", 0, QApplication::UnicodeUTF8));
    LabelAtual->setText(QApplication::translate("Form1", "Point", 0, QApplication::UnicodeUTF8));
    spinAtual->setToolTip(QApplication::translate("Form1", "Point in use", 0, QApplication::UnicodeUTF8));
    limpaButton->setToolTip(QApplication::translate("Form1", "Erase all points", 0, QApplication::UnicodeUTF8));
    limpaButton->setText(QApplication::translate("Form1", "Clear", 0, QApplication::UnicodeUTF8));
    groupBox19->setTitle(QApplication::translate("Form1", "Zoom 5X", 0, QApplication::UnicodeUTF8));
    colunaLabel->setText(QApplication::translate("Form1", "Column:", 0, QApplication::UnicodeUTF8));
    coluna->setText(QApplication::translate("Form1", "0", 0, QApplication::UnicodeUTF8));
    linhaLabel->setText(QApplication::translate("Form1", "Line:", 0, QApplication::UnicodeUTF8));
    linha->setText(QApplication::translate("Form1", "0", 0, QApplication::UnicodeUTF8));
    zoomLabel->setText(QString());
    groupBox4->setTitle(QApplication::translate("Form1", "Adjusts", 0, QApplication::UnicodeUTF8));
    textLabel9->setText(QApplication::translate("Form1", "Xo:", 0, QApplication::UnicodeUTF8));
    textLabel11->setText(QApplication::translate("Form1", "Yo:", 0, QApplication::UnicodeUTF8));
    textLabel10->setText(QApplication::translate("Form1", "Xf:", 0, QApplication::UnicodeUTF8));
    textLabel12->setText(QApplication::translate("Form1", "Yf:", 0, QApplication::UnicodeUTF8));
    YoEdit->setText(QApplication::translate("Form1", "0", 0, QApplication::UnicodeUTF8));
    YdEdit->setText(QApplication::translate("Form1", "0", 0, QApplication::UnicodeUTF8));
    XdEdit->setText(QApplication::translate("Form1", "0", 0, QApplication::UnicodeUTF8));
    XoEdit->setText(QApplication::translate("Form1", "0", 0, QApplication::UnicodeUTF8));
    ratioLabel->setText(QApplication::translate("Form1", "0", 0, QApplication::UnicodeUTF8));
    proporcaoLabel->setText(QApplication::translate("Form1", "X/Y Aspect Ratio:", 0, QApplication::UnicodeUTF8));
    ajustesLabel1->setText(QApplication::translate("Form1", "Image metric coordinates:", 0, QApplication::UnicodeUTF8));
    groupBox9->setTitle(QApplication::translate("Form1", "General Options", 0, QApplication::UnicodeUTF8));
    medianaButton->setToolTip(QApplication::translate("Form1", "Create six points on all quadrilateral medians", 0, QApplication::UnicodeUTF8));
    medianaButton->setText(QApplication::translate("Form1", "Create median points", 0, QApplication::UnicodeUTF8));
    checkBox1->setToolTip(QApplication::translate("Form1", "Calculate new image proportions acoording to original metric", 0, QApplication::UnicodeUTF8));
    checkBox1->setText(QApplication::translate("Form1", "Keep metric proportions", 0, QApplication::UnicodeUTF8));
    checkBox2->setToolTip(QApplication::translate("Form1", "Link all points in sequence", 0, QApplication::UnicodeUTF8));
    checkBox2->setText(QApplication::translate("Form1", "Sequential C.Points linkage", 0, QApplication::UnicodeUTF8));
    reportButton->setToolTip(QApplication::translate("Form1", "Open a report which describes all steps done in your job", 0, QApplication::UnicodeUTF8));
    reportButton->setText(QApplication::translate("Form1", "Open report", 0, QApplication::UnicodeUTF8));
    groupBox6->setTitle(QApplication::translate("Form1", "Informations", 0, QApplication::UnicodeUTF8));
    larguraLabel->setText(QApplication::translate("Form1", "Width:", 0, QApplication::UnicodeUTF8));
    alturaLabel->setText(QApplication::translate("Form1", "Height:", 0, QApplication::UnicodeUTF8));
    textLabel6->setText(QApplication::translate("Form1", "pixels", 0, QApplication::UnicodeUTF8));
    textLabel5->setText(QApplication::translate("Form1", "pixels", 0, QApplication::UnicodeUTF8));
    varAlturaLabel->setText(QApplication::translate("Form1", "(0-0)", 0, QApplication::UnicodeUTF8));
    varLarguraLabel->setText(QApplication::translate("Form1", "(0-0)", 0, QApplication::UnicodeUTF8));
    modeloButton->setToolTip(QApplication::translate("Form1", "Load a correct image (if available) to help on rectification points identification", 0, QApplication::UnicodeUTF8));
    modeloButton->setText(QApplication::translate("Form1", "Model", 0, QApplication::UnicodeUTF8));
    redimButton->setToolTip(QApplication::translate("Form1", "Resize image according above information", 0, QApplication::UnicodeUTF8));
    redimButton->setText(QApplication::translate("Form1", "Resize", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Form1);
    } // retranslateUi

};

namespace Ui {
    class Form1: public Ui_Form1 {};
} // namespace Ui

class Form1 : public Q3MainWindow, public Ui::Form1
{
    Q_OBJECT

public:
    Form1(QWidget* parent = 0, const char* name = 0, Qt::WindowFlags fl = Qt::WType_TopLevel);
    ~Form1();

    virtual int spinReturn( int spin );

public slots:
    virtual void resizeEvent( QResizeEvent * );
    virtual void opcoesGerais();
    virtual void minimosPontos();
    virtual void ajustaPontos( int min );
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

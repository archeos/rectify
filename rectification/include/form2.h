/********************************************************************************
** Form generated from reading ui file 'form2.ui'
**
** Created: Fri Jan 18 12:03:03 2008
**      by: Qt User Interface Compiler version 4.2.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef FORM2_H
#define FORM2_H

#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <Qt3Support/Q3MimeSourceFactory>

class Ui_Form2
{
public:
    QGridLayout *gridLayout;
    Q3TextEdit *textEdit1;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QToolButton *cleanButton;
    QSpacerItem *spacerItem1;
    QToolButton *saveButton;
    QSpacerItem *spacerItem2;

    void setupUi(QDialog *Form2)
    {
    Form2->setObjectName(QString::fromUtf8("Form2"));
    Form2->setWindowIcon(QIcon(qPixmapFromMimeSource("images/identity.png")));
    Form2->setModal(true);
    gridLayout = new QGridLayout(Form2);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    textEdit1 = new Q3TextEdit(Form2);
    textEdit1->setObjectName(QString::fromUtf8("textEdit1"));
    textEdit1->setEnabled(true);
    QFont font;
    font.setFamily(QString::fromUtf8("Courier [ibm]"));
    textEdit1->setFont(font);
    textEdit1->setReadOnly(true);

    gridLayout->addWidget(textEdit1, 0, 0, 1, 1);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);

    cleanButton = new QToolButton(Form2);
    cleanButton->setObjectName(QString::fromUtf8("cleanButton"));
    cleanButton->setEnabled(true);
    cleanButton->setIcon(QIcon(qPixmapFromMimeSource("images/limpar.png")));

    hboxLayout->addWidget(cleanButton);

    spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem1);

    saveButton = new QToolButton(Form2);
    saveButton->setObjectName(QString::fromUtf8("saveButton"));
    saveButton->setEnabled(true);
    saveButton->setIcon(QIcon(qPixmapFromMimeSource("images/gnome-dev-floppy.png")));

    hboxLayout->addWidget(saveButton);

    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem2);


    gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);


    retranslateUi(Form2);

    QSize size(591, 374);
    size = size.expandedTo(Form2->minimumSizeHint());
    Form2->resize(size);

    QObject::connect(cleanButton, SIGNAL(clicked()), textEdit1, SLOT(clear()));
    QObject::connect(saveButton, SIGNAL(clicked()), Form2, SLOT(salvarImagem()));

    QMetaObject::connectSlotsByName(Form2);
    } // setupUi

    void retranslateUi(QDialog *Form2)
    {
    Form2->setWindowTitle(QApplication::translate("Form2", "Rectification Report", 0, QApplication::UnicodeUTF8));
    cleanButton->setText(QApplication::translate("Form2", " Clear", 0, QApplication::UnicodeUTF8));
    saveButton->setText(QApplication::translate("Form2", " Save", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Form2);
    } // retranslateUi

};

namespace Ui {
    class Form2: public Ui_Form2 {};
} // namespace Ui

class Form2 : public QDialog, public Ui::Form2
{
    Q_OBJECT

public:
    Form2(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~Form2();

public slots:
    virtual void mensagem( QString s );
    virtual void salvarImagem();

protected slots:
    virtual void languageChange();

};

#endif // FORM2_H

/********************************************************************************
** Form generated from reading ui file 'about.ui'
**
** Created: Fri Jan 18 12:03:20 2008
**      by: Qt User Interface Compiler version 4.2.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef ABOUT_H
#define ABOUT_H

#include <Qt3Support/Q3TextBrowser>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QPushButton>
#include <Qt3Support/Q3MimeSourceFactory>

class Ui_About
{
public:
    QPushButton *pushButton1;
    Q3TextBrowser *textBrowser1;

    void setupUi(QDialog *About)
    {
    About->setObjectName(QString::fromUtf8("About"));
    About->setWindowIcon(QIcon(qPixmapFromMimeSource("images/identity.png")));
    pushButton1 = new QPushButton(About);
    pushButton1->setObjectName(QString::fromUtf8("pushButton1"));
    pushButton1->setGeometry(QRect(187, 270, 50, 30));
    textBrowser1 = new Q3TextBrowser(About);
    textBrowser1->setObjectName(QString::fromUtf8("textBrowser1"));
    textBrowser1->setGeometry(QRect(10, 10, 410, 250));

    retranslateUi(About);

    QSize size(432, 310);
    size = size.expandedTo(About->minimumSizeHint());
    About->resize(size);

    QObject::connect(pushButton1, SIGNAL(clicked()), About, SLOT(close()));

    QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
    About->setWindowTitle(QApplication::translate("About", "About Rectification", 0, QApplication::UnicodeUTF8));
    pushButton1->setText(QApplication::translate("About", "Ok", 0, QApplication::UnicodeUTF8));
    textBrowser1->setText(QApplication::translate("About", "<u>Rectification Module</u><br><br>\n"
"\n"
"<u>What's new:</u><br><br>\n"
"Version 1.2 - Dec 2006<br>\n"
"- Layout improvement. <br>\n"
"- Resize main window. <br>\n"
"- Resize report window.<br>\n"
"- Interpolation for images less than 32 bit color.<br><br><br>\n"
"\n"
"Version 1.1<br>\n"
"- Results statistics added.<br>\n"
"- Proportional rectangle aid added.<br><br><br>\n"
"\n"
"<u>Programmers:</u><br><br>\n"
"Marcelo Teixeira Silveira, M.Sc.<br>\n"
"- Final layout design<br>\n"
"- Image handle code<br>\n"
"- Image interpolation code<br>\n"
"- Image transformations convertion to C++ (all but general affine)<br>\n"
"- Report <br><br>\n"
"Rafael Paz <br>\n"
"- First prototype<br>\n"
"- Matrix library converted to class<br>\n"
"- Image transformations convertion to C++ (general affine)<br><br>\n"
"Orlando Bernardo Filho, D.Sc.<br>\n"
"- Professor responsible for converting some codes to classes<br>\n"
"- Matrix library converted to class<br>\n"
"- Image transformations convertion to C++ (general affine)<br>\n"
""
        "- Statistics<br><br>\n"
"Sidney Andrade de Lima<br>\n"
"- All transformation work done in Mathcad<br><br>\n"
"Luiz Coelho, M.Sc.<br>\n"
"- E-FOTO creator<br>\n"
"- Matrix code<br><br>\n"
"<br>\n"
"<u>Bibliography</u><br><br>\n"
"E-BOOK<br>\n"
"- Luiz Coelho, M.Sc.<br>\n"
"- Jorge Nunes Brito, Ph.D.<br>\n"
"<br>\n"
"Estrategias para Retificacao de Imagens Digitais -<i> UERJ Engineering Course monograph</i><br>\n"
"- Sidney Andrade de Lima, Cartographic Engineer<br>\n"
"- Jorge Nunes Brito, Ph.D.<br>\n"
"<br>\n"
"Contact: <a href=\"http://www.efoto.eng.uerj.br\">http://www.efoto.eng.uerj.br</a>", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(About);
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

class About : public QDialog, public Ui::About
{
    Q_OBJECT

public:
    About(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    ~About();

protected slots:
    virtual void languageChange();

};

#endif // ABOUT_H

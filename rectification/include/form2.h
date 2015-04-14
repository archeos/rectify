#ifndef FORM2_H
#define FORM2_H

#include "ui_form2.h"

class Form2 : public QDialog, public Ui::Form2
{
    Q_OBJECT

public:
    Form2(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);
    virtual ~Form2();

public slots:
    virtual void mensagem( QString s );
    virtual void salvarImagem();

protected slots:
    virtual void languageChange();

};

#endif // FORM2_H

#ifndef ABOUT_H
#define ABOUT_H

#include "ui_about.h"

class About : public QDialog, public Ui::About
{
    Q_OBJECT

public:
    About(QWidget* parent = 0);
    virtual ~About();

protected slots:
    virtual void languageChange();

};

#endif // ABOUT_H

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

#include "AboutDialog.h"

#include <QDialogButtonBox>
#include <QFile>
#include <QIcon>
#include <QTextEdit>
#include <QTextStream>
#include <QVBoxLayout>

AboutDialog::AboutDialog(QWidget* parent)
    : QDialog(parent)
{
    // Setup dialog appeareance.
    setWindowTitle(tr("About"));
    setWindowIcon(QIcon(":/icons/indentity.png"));
    resize(400, 300);
    setModal(true);

    // Create about text browser.
    QTextEdit* textEdit = new QTextEdit(this);
    textEdit->setText(readContent());
    textEdit->setReadOnly(true);

    // Create button box.
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(close()));

    // Setup layout.
    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(textEdit);
    vbox->addWidget(buttonBox);

    setLayout(vbox);
}

AboutDialog::~AboutDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

QString AboutDialog::readContent()
{
    QFile file(":/etc/about.htm");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    return in.readAll();
}

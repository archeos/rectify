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

#include "ReportDialog.h"
#include "Toolbox.h"

#include <QDir>
#include <QFileDialog>
#include <QFont>
#include <QHBoxLayout>
#include <QImage>
#include <QMessageBox>
#include <QPixmap>
#include <QPushButton>
#include <QTextEdit>
#include <QTextStream>
#include <QVBoxLayout>

/*
 *  Constructs a ReportDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
ReportDialog::ReportDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Report"));
    setWindowIcon(QIcon(":/icons/identity.png"));
    resize(500, 300);

    QFont font;
    font.setFamily("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    font.setItalic(true);

    textEdit = new QTextEdit(this);
    textEdit->setFont(font);
    textEdit->setTextColor(QColor("#666"));
    textEdit->setReadOnly(true);

    clearButton = new QPushButton(Toolbox::icon("edit-clear"), tr("Clea&r"), this);
    saveAsButton = new QPushButton(Toolbox::icon("document-save-as"), tr("&Save"), this);
    closeButton = new QPushButton(Toolbox::icon("application-exit"), tr("&Close"), this);
    closeButton->setDefault(true);

    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addStretch();
    hbox->addWidget(clearButton);
    hbox->addWidget(saveAsButton);
    hbox->addWidget(closeButton);
    QVBoxLayout* vbox = new QVBoxLayout();
    vbox->addWidget(textEdit);
    vbox->addLayout(hbox);
    setLayout(vbox);

    connect(clearButton, SIGNAL(clicked()), textEdit, SLOT(clear()));
    connect(saveAsButton, SIGNAL(clicked()), this, SLOT(saveReport()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
ReportDialog::~ReportDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

void ReportDialog::append(const QString& text)
{
    textEdit->append(text);
}

void ReportDialog::saveReport()
{
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Choose one name to save Report text"),
        QDir::homePath(), "Text (*.txt)"
    );

    if (filename == "")
        return;

    saveReport(filename);
}

void ReportDialog::saveReport(const QString& filename)
{
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

    QString text = textEdit->toPlainText();
    QFile f( filename );
    if ( !f.open( QIODevice::WriteOnly ) )
        return;

    QTextStream t( &f );
    t << text;
    f.close();
}

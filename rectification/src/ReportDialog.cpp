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

#include <q3filedialog.h>
#include <Q3TextStream>
#include <qimage.h>
#include <qmessagebox.h>
#include <qpixmap.h>
#include <qvariant.h>

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
    setupUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
ReportDialog::~ReportDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ReportDialog::languageChange()
{
    retranslateUi(this);
}

void ReportDialog::mensagem(QString s)
{
    textEdit1->insert(s);
}

void ReportDialog::salvarImagem()
{
    QString filename = Q3FileDialog::getSaveFileName(".", "Text (*.txt)", this, "Save Report Dialog", "Choose one name to save Report text") ;
    if (filename == "")
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

    QString text = textEdit1->text();
    QFile f( filename );
    if ( !f.open( QIODevice::WriteOnly ) )
        return;

    Q3TextStream t( &f );
    t << text;
    f.close();
}

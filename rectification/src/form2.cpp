#include "form2.h"

#include <q3filedialog.h>
#include <Q3TextStream>
#include <qimage.h>
#include <qmessagebox.h>
#include <qpixmap.h>
#include <qvariant.h>

/*
 *  Constructs a Form2 as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
Form2::Form2(QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl)
    : QDialog(parent, name, modal, fl)
{
    setupUi(this);
}

/*
 *  Destroys the object and frees any allocated resources
 */
Form2::~Form2()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void Form2::languageChange()
{
    retranslateUi(this);
}

void Form2::mensagem(QString s)
{
    textEdit1->insert(s);
}

void Form2::salvarImagem()
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

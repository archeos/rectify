/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
#include <q3filedialog.h>
#include <qmessagebox.h>
#include <Q3TextStream>

void Form2::mensagem(QString s)
{
    textEdit1->insert(s);
}

void Form2::salvarImagem()
{
    QString filename = Q3FileDialog::getSaveFileName(".","Text (*.txt)",this,"Save Report Dialog","Choose one name to save Report text") ;
    if (filename=="")
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

#include <qapplication.h>
#include "form1.h"
#include "form2.h"
#include "about.h"

Form1 *form1;
Form2 *form2;
About *about;

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    Form1 w;
    form1 = &w;
    w.show();
    Form2 w2(&w); // Adiciona form2 como "child" de form 1
    About w3(&w);
    form2 = &w2;
    about = &w3;
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}

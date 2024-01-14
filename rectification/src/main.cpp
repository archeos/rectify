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

#include "MainWindow.h"
#include "ReportDialog.h"

#include <QtWidgets/QApplication>

// TODO remove global pointers.
MainWindow* mainWindow;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow window;
    mainWindow = &window;
    window.show();

    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));

    if (argc > 1)
    {
        window.openImage(argv[1]);
    }

    return app.exec();
}

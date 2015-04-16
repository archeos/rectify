#
#  rectify - Orthophoto rectification for archaeological use.
#  Copyright (C) 2015  Bernhard Arnold
#                2004  Marcelo Teixeira Silveira, Rafael Paz,
#                      Orlando Bernardo Filho, Sidney Andrade de Lima,
#                      Luiz Coelho
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see {http://www.gnu.org/licenses/}.
#

TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

TARGET = rectify
DESTDIR = bin

INCLUDEPATH += include/

HEADERS	+= \
    include/Image.h \
    include/Panel.h \
    include/Rectifier.h \
    include/Matrix.h \
    include/MainWindow.h \
    include/ReportDialog.h \
    include/AboutDialog.h

SOURCES	+= \
    src/main.cpp \
    src/Image.cpp \
    src/Panel.cpp \
    src/Rectifier.cpp \
    src/Matrix.cpp \
    src/MainWindow.cpp \
    src/ReportDialog.cpp \
    src/AboutDialog.cpp

# The following line was changed from FORMS to FORMS3 by qt3to4
FORMS += \
    ui/MainWindow.ui \
    ui/ReportDialog.ui \
    ui/AboutDialog.ui

RESOURCES = rectify.qrc

unix {
    RCC_DIR = resources
    UI_DIR = .ui
    MOC_DIR = .moc
    OBJECTS_DIR = .obj
}

mystaticconfig {
    QMAKE_LIBS_QT =
    QMAKE_LIBS_QT_THREAD =
    LIBS += $(QTDIR)/lib/libqt-mt.so.3.3.3
}

QT +=  qt3support

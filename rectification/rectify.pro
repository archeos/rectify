TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

TARGET = rectify
DESTDIR = bin

INCLUDEPATH += include/

HEADERS	+= include/imagem.h \
	include/painel.h \
	include/retif.h \
	include/Matrix.h \
	include/form1.h \
	include/form2.h \
	include/about.h

SOURCES	+= \
	src/main.cpp \
	src/imagem.cpp \
	src/painel.cpp \
	src/retif.cpp \
	src/Matrix.cpp \
	src/form1.cpp \
	src/form2.cpp \
	src/about.cpp

# The following line was changed from FORMS to FORMS3 by qt3to4
FORMS += \
	ui/form1.ui \
	ui/form2.ui \
	ui/about.ui

IMAGES	= \
	images/salvar.png \
	images/limpar.png

unix {
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

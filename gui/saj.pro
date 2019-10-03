QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = saj-gui
TEMPLATE = app

HEADERS += configdialog.h \
pages.h \
readwritefile.h

SOURCES += saj-gui.cpp \
configdialog.cpp \
pages.cpp \
readwritefile.cpp

LIBS += -L"/usr/local/lib" -Wl,-rpath,/usr/local/lib\
-L"/usr/local/lib" -Wl,-rpath,/usr/local/lib

# -------------------------------------------------
# Project created by QtCreator 2009-12-18T00:47:59
# -------------------------------------------------
TARGET = mediark
TEMPLATE = app
CONFIG += debug
SOURCES += main.cpp \
    mainwindow.cpp \
    capturedialog.cpp \
    settings.cpp \
    imagescanner.cpp \
    preferencesdialog.cpp
HEADERS += mainwindow.h \
    capturedialog.h \
    settings.h \
    common.h \
    imagescanner.h \
    preferencesdialog.h
FORMS += mainwindow.ui \
    capturedialog.ui \
    preferencesdialog.ui
LIBS += -lsane
OTHER_FILES += TODO.txt
RESOURCES += images.qrc

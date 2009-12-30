# -------------------------------------------------
# Project created by QtCreator 2009-12-18T00:47:59
# -------------------------------------------------
TARGET = mediark
TEMPLATE = app
CONFIG += debug
QT += dbus
SOURCES += main.cpp \
    mainwindow.cpp \
    capturedialog.cpp \
    settings.cpp \
    imagescanner.cpp \
    preferencesdialog.cpp \
    newsequencedialog.cpp \
    ddplugin.cpp \
    copycat.cpp \
    plugin.cpp \
    devicefinder.cpp \
    hal_manager_interface.cpp
HEADERS += mainwindow.h \
    capturedialog.h \
    settings.h \
    common.h \
    imagescanner.h \
    preferencesdialog.h \
    newsequencedialog.h \
    ddplugin.h \
    copycat.h \
    plugin.h \
    devicefinder.h \
    hal_manager_interface.h
FORMS += mainwindow.ui \
    capturedialog.ui \
    preferencesdialog.ui \
    newsequencedialog.ui
LIBS += -lsane
OTHER_FILES += TODO.txt
RESOURCES += images.qrc

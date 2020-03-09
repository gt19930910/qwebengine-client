#-------------------------------------------------
#
# Project created by QtCreator 2020-02-17T14:33:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vcd-web-client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#gt add
QT += webenginewidgets
LIBS += -lAdvapi32
include(log4qt/log4qt.pri)
INCLUDEPATH += log4qt
#gt add

SOURCES +=\
        mainwindow.cpp \
    jscontext.cpp \
    main.cpp \
    vcdlog4qt.cpp \
    webview.cpp \
    webpage.cpp \
    downloadmanager.cpp \
    softinfo.cpp \
    commonmeth.cpp

HEADERS  += mainwindow.h \
    jscontext.h \
    vcdlog4qt.h \
    webview.h \
    webpage.h \
    downloadmanager.h \
    softinfo.h \
    commonmeth.h

FORMS    += mainwindow.ui

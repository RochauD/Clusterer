#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T15:26:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graph
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingsdialog.cpp \
    frontendconfig.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    frontendconfig.h

FORMS    += mainwindow.ui \
    settingsdialog.ui

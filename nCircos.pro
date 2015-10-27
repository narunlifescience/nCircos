#-------------------------------------------------
#
# Project created by QtCreator 2015-10-18T01:29:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nCircos
TEMPLATE = app


SOURCES += main.cpp\
    ui/mainwindow.cpp \
    commandline/commandline.cpp

HEADERS  += ui/mainwindow.h \
    commandline/commandline.h

FORMS    += ui/mainwindow.ui

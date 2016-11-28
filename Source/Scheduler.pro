#-------------------------------------------------
#
# Project created by QtCreator 2016-11-14T19:14:14
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Scheduler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addwindow.cpp \
    notifywindow.cpp

HEADERS  += mainwindow.h \
    addwindow.h \
    notifywindow.h

FORMS    += mainwindow.ui \
    addwindow.ui \
    notifywindow.ui

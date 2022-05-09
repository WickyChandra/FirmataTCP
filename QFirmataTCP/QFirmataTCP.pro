#-------------------------------------------------
#
# Project created by QtCreator 2015-04-02T18:17:16
#
#-------------------------------------------------

QT       += core gui network
QT_MAJOR_VERSION = 5
QT_MINOR_VERSION = 5

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QFirmataDO
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    digitalpin.cpp \
    analogpin.cpp \
    pin.cpp

HEADERS  += mainwindow.h \
    digitalpin.h \
    analogpin.h \
    pin.h

CONFIG += mobility
MOBILITY =

include(C:\Users\sgu\Downloads\QFirmataWallFollower-master\QFirmataTCP.pri)

FORMS += \
    mainwindow.ui


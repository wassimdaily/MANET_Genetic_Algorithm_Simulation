#-------------------------------------------------
#
# Project created by QtCreator 2014-10-17T14:26:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = GA_Simulation
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11
QMAKE_LFLAGS= -enable-auto-import -WI

SOURCES += main.cpp\
           mainwindow.cpp \
         qcustomplot.cpp \
            node.cpp

HEADERS  += mainwindow.h \
         qcustomplot.h \
    node.h \
    qcustomplot.h

FORMS    += mainwindow.ui


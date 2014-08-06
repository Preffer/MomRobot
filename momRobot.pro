#-------------------------------------------------
#
# Project created by QtCreator 2014-08-02T17:02:21
#
#-------------------------------------------------

QT       += core gui
QT       += axcontainer
QT       += concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = momRobot
TEMPLATE = app


SOURCES += main.cpp\
        momrobot.cpp \
        textreader.cpp \
        excelreader.cpp

HEADERS += momrobot.h \
        textreader.h \
        excelreader.h

FORMS   += momrobot.ui

RC_FILE += logo.rc

RESOURCES += \
    resource.qrc

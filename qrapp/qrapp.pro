
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qrapp
TEMPLATE = app


SOURCES += main.cpp\
        qrwidget.cpp

HEADERS  += qrwidget.h

include(../pods.pri)

RESOURCES += \
    resources.qrc

#-------------------------------------------------
#
# Project created by QtCreator 2016-09-29T21:47:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StopNotebook
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        widget.cpp \
    lastuserinput.cpp \
    usertimesettings.cpp

HEADERS  += widget.h \
    lastuserinput.h \
    usertimesettings.h \
    singleton.h

LIBS += -lKernel32

RESOURCES += \
    resources.qrc

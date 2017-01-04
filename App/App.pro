#-------------------------------------------------
#
# Project created by QtCreator 2016-09-29T21:47:27
#
#-------------------------------------------------

QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

APPNAME = StopNotebook
VERSION = 0.1.1

TARGET = "$$APPNAME"

CONFIG += c++11

DEFINES += APP_NAME=\\\"$$APPNAME\\\"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

CONFIG += c++11

SOURCES += \
    main.cpp\
    widget.cpp \
    userinputwatcher.cpp \
    usertimesettings.cpp \
    systeminput.cpp \
    settingstorage.cpp \
    programupdater.cpp \
    urldownloader.cpp

HEADERS += \
    widget.h \
    userinputwatcher.h \
    usertimesettings.h \
    singleton.h \
    systeminput.h \
    timeformat.h \
    settingstorage.h \
    programupdater.h \
    urldownloader.h

LIBS += -lKernel32 -lWinmm

RESOURCES += \
    resources.qrc

RC_FILE = app.rc

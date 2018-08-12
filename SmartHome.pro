#-------------------------------------------------
#
# Project created by QtCreator 2017-07-15T10:59:52
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += webkit


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartHome
TEMPLATE = app


SOURCES +=\
    smarthome.cpp \
    userlock.cpp \
    main.cpp \
    about.cpp \
    serialform.cpp \
    appdatashow.cpp \
    database.cpp \
    flameweibo.cpp \
    speedcontrol.cpp \
    form.cpp

HEADERS  += \
    smarthome.h \
    userlock.h \
    main.h \
    about.h \
    serialform.h \
    appdatashow.h \
    database.h \
    flameweibo.h \
    speedcontrol.h \
    form.h

FORMS    += \
    smarthome.ui \
    userlock.ui \
    about.ui \
    serialform.ui \
    appdatashow.ui \
    flameweibo.ui \
    form.ui

RESOURCES += \
    resource.qrc

#-------------------------------------------------
#
# Project created by QtCreator 2018-09-19T18:11:04
#
#-------------------------------------------------


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    w_setting.cpp \
    redactor.cpp \
    otvet.cpp \
    quest.cpp \
    rezz.cpp \
    quest_2.cpp

HEADERS  += mainwindow.h \
    w_setting.h \
    redactor.h \
    otvet.h \
    quest.h \
    rezz.h \
    quest_2.h


FORMS    += mainwindow.ui \
    w_setting.ui \
    redactor.ui \
    otvet.ui \
    quest.ui \
    rezz.ui \
    quest_2.ui


RESOURCES += \
    image.qrc

DISTFILES +=

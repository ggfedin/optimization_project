#-------------------------------------------------
#
# Project created by QtCreator 2018-02-23T11:03:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = optimisation
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QT   += xml network
QT -= gui

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    milp.cpp \
    client.cpp

HEADERS += \
        mainwindow.h \
    milp.h \
    client.h

FORMS += \
        mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-maia-Desktop_Qt_5_10_1_MinGW_32bit-Debug/release/ -lmaia
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-maia-Desktop_Qt_5_10_1_MinGW_32bit-Debug/debug/ -lmaia
else:unix: LIBS += -L$$PWD/../build-maia-Desktop_Qt_5_10_1_MinGW_32bit-Debug/ -lmaia

INCLUDEPATH += $$PWD/../build-maia-Desktop_Qt_5_10_1_MinGW_32bit-Debug/debug
DEPENDPATH += $$PWD/../build-maia-Desktop_Qt_5_10_1_MinGW_32bit-Debug/debug

DISTFILES += \
    jobinfo.txt \
    SolverTemplate.txt \
    task.txt \
    xmljob.txt

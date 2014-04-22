#-------------------------------------------------
#
# Project created by QtCreator 2014-04-18T19:01:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestProject
TEMPLATE = app

INCLUDEPATH += includes
DEPENDPATH += sources \
        ui


SOURCES += sources\main.cpp\
    sources\TestWidget.cpp \
    sources/CustomTitleBar.cpp \
    sources/CustomSwitcher.cpp

HEADERS  += includes\TestWidget.h \
    includes/CustomTitleBar.h \
    includes/CustomSwitcher.h

FORMS    += ui\TestWidget.ui \
    ui/CustomTitleBar.ui

RESOURCES += resources/TestProject.qrc

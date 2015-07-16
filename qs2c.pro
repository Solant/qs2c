#-------------------------------------------------
#
# Project created by QtCreator 2014-08-19T13:03:12
#
#-------------------------------------------------

QT      += core gui
QT	    += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qs2c
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmlparser.cpp \
    settings.cpp \
    settingscontainer.cpp \
    appdata.cpp \
    syncprovider.cpp \
    applicationproperties.cpp \
    applicationpropertiestablemodel.cpp \
    createapplicationdialog.cpp \
    applicationpropertieslistmodel.cpp \
    mainwindowapplicationlistmodel.cpp \
    pcgamingwikidialog.cpp \
    pathnode.cpp \
    mainwindowlistview.cpp

HEADERS  += mainwindow.h \
    xmlparser.h \
    settings.h \
    settingscontainer.h \
    appdata.h \
    syncprovider.h \
    applicationproperties.h \
    applicationpropertiestablemodel.h \
    createapplicationdialog.h \
    applicationpropertieslistmodel.h \
    mainwindowapplicationlistmodel.h \
    pcgamingwikidialog.h \
    pathnode.h \
    mainwindowlistview.h

FORMS    += mainwindow.ui \
    settings.ui \
    applicationproperties.ui \
    createapplicationdialog.ui \
    pcgamingwikidialog.ui

OTHER_FILES +=

CONFIG += c++11

RESOURCES += \
    res.qrc

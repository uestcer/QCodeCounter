#-------------------------------------------------
#
# Project created by QtCreator 2014-02-03T22:25:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QCodeCounter
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    PercentageTableView.cpp \
    FileTypePlugin.cpp \
    FileTypePluginManager.cpp \
    FileTypeChooseDialog.cpp \
    CounterThread.cpp \
    CheckBoxDelegate.cpp \
    Counter.cpp

HEADERS  += MainWindow.h \
    PercentageTableView.h \
    FileTypePlugin.h \
    FileTypePluginManager.h \
    FileTypeChooseDialog.h \
    CounterThread.h \
    CheckBoxDelegate.h \
    Counter.h

TRANSLATIONS += QCodeCounter_zh_CN.ts

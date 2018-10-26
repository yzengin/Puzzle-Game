#-------------------------------------------------
#
# Project created by QtCreator 2017-12-24T18:56:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Puzzle_Odev
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    parca_liste.cpp \
    puzzle_sinif.cpp

HEADERS  += mainwindow.h \
    parca_liste.h \
    puzzle_sinif.h

FORMS    += mainwindow.ui

RESOURCES += \
    resimler.qrc

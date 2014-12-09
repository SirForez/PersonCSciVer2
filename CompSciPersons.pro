#-------------------------------------------------
#
# Project created by QtCreator 2014-11-27T21:03:27
#
#-------------------------------------------------

QT       += core sql

QT       -= gui

TARGET = CompSciPersons
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ui.cpp \
    person.cpp \
    personservice.cpp \
    personrepository.cpp \
    comparer.cpp \
    computerservice.cpp \
    computerrepository.cpp \
    computer.cpp

HEADERS += \
    ui.h \
    person.h \
    personservice.h \
    personrepository.h \
    comparer.h \
    computerservice.h \
    computerrepository.h \
    computer.h

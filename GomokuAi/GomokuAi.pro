#-------------------------------------------------
#
# Project created by QtCreator 2019-11-06T01:16:46
#
#-------------------------------------------------

QT       -= core gui

TARGET = GomokuAi
TEMPLATE = lib

DEFINES += GOMOKUAI_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        gomokuai.cpp \
    ai.cpp \
    constants.cpp

INCLUDEPATH += D:\ProgramPackage\Python\Python36\include

LIBS += -LD:\ProgramPackage\Python\Python36\libs -lpython36

HEADERS += \
    ai.h \
    constants.h

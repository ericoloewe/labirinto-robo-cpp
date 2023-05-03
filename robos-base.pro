#-------------------------------------------------
#
# Project created by QtCreator 2011-10-30T20:07:40
#
#-------------------------------------------------

QT       -= core
QT       -= gui

TARGET = robos-base
CONFIG   += console
CONFIG   += opengl
CONFIG   += glut
CONFIG   -= app_bundle

LIBS += -framework GLUT -ljpeg

TEMPLATE = app


SOURCES += main.cpp \
    LabirintoChar.cpp \
    GL.cpp \
    RoboB9.cpp \
    Texture.cpp \
    LabirintoTeste.cpp

HEADERS += \
    Robo.h \
    Point.h \
    LabirintoChar.h \
    Labirinto.h \
    GL.h \
    RoboB9.h \
    Texture.h \
    LabirintoTeste.h

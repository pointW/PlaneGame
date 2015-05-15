#-------------------------------------------------
#
# Project created by QtCreator 2015-03-08T16:40:47
#
#-------------------------------------------------

CONFIG += c++11

QT       += core gui widgets opengl


TARGET = plane
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    plane.cpp \
    gamecontroller.cpp \
    flyitem.cpp \
    playerbullet.cpp \
    enemyplane.cpp \
    explosion.cpp \
    playerlaser.cpp \
    buffitem.cpp \
    playermissile.cpp \
    playerhp.cpp \
    score.cpp \
    playerlife.cpp \
    background.cpp \
    wingman.cpp \
    playerlightingball.cpp \
    timer.cpp

HEADERS  += mainwindow.h \
    plane.h \
    gamecontroller.h \
    flyitem.h \
    playerbullet.h \
    enemyplane.h \
    constants.h \
    explosion.h \
    playerlaser.h \
    buffitem.h \
    playermissile.h \
    playerhp.h \
    score.h \
    playerlife.h \
    background.h \
    wingman.h \
    playerlightingball.h \
    timer.h

RESOURCES += \
    res.qrc


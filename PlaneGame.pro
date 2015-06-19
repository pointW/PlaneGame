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
    timer.cpp \
    enemyboss.cpp \
    enemybullet.cpp \
    bosshp.cpp \
    lists.cpp \
    laser.cpp

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
    timer.h \
    enemyboss.h \
    enemybullet.h \
    bosshp.h \
    lists.h \
    laser.h

RESOURCES += \
    res.qrc


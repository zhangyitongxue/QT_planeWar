#-------------------------------------------------
#
# Project created by QtCreator 2022-06-28T16:33:55
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = planeWar_e1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        titlescene.cpp \
    mypushbutton.cpp \
    chooselevel.cpp \
    playscene.cpp \
    plane.cpp \
    enemyplane.cpp \
    projectile.cpp

HEADERS += \
        titlescene.h \
    mypushbutton.h \
    chooselevel.h \
    playscene.h \
    mydefine.h \
    plane.h \
    enemyplane.h \
    projectile.h

FORMS +=

RESOURCES += \
    res.qrc

CONFIG += resources_big

#-------------------------------------------------
#
# Project created by QtCreator 2022-05-29T20:22:26
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = naicha
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
    mainwindow.cpp \
    manager.cpp \
    qsteeing.cpp \
    specifications.cpp \
    sql.cpp \
    userWindow.cpp \
    enroll.cpp

HEADERS += \
        mainwindow.h \
    manager.h \
    qsteeing.h \
    specifications.h \
    sql.h \
    userWindow.h \
    enroll.h

FORMS += \
        mainwindow.ui \
    manager.ui \
    specifications.ui \
    user.ui \
    enroll.ui

RESOURCES += \
    image.qrc

DISTFILES += \
    Resources/多肉桃桃.jpg \
    Resources/多肉葡萄冻.jpg \
    Resources/满杯红柚.jpg \
    Resources/芝芝多肉杨梅.jpg \
    Resources/轻芒芒甘露.jpg

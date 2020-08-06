#-------------------------------------------------
#
# Project created by QtCreator 2020-07-01T12:41:26
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = angryNerds
TEMPLATE = app

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
        main.cpp \
    backgrounditem.cpp \
    level.cpp \
    goal.cpp \
    staticobject.cpp \
    globalvariables.cpp \
    dynamicobject.cpp \
    projectile.cpp \
    cvl.cpp \
    mainwindow.cpp \
    setting.cpp \
    mensa.cpp \
    forcefield.cpp \
    logic.cpp \
    bib.cpp

HEADERS += \
    backgrounditem.h \
    level.h \
    box2d/box2d.h \
    goal.h \
    staticobject.h \
    globalvariables.h \
    dynamicobject.h \
    projectile.h \
    cvl.h \
    mainwindow.h \
    setting.h \
    mensa.h \
    forcefield.h \
    logic.h \
    bib.h

RESOURCES += \
    anresources.qrc


FORMS += \
    mainwindow.ui \
    setting.ui




unix:!macx: LIBS += -L$$PWD/./ -lbox2d

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

unix:!macx: PRE_TARGETDEPS += $$PWD/./libbox2d.a

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

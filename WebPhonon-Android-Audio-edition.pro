#-------------------------------------------------
#
# Project created by QtCreator 2016-07-04T13:48:40
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia androidextras

TARGET = WebPhonon-Android-Audio-edition
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    visualizer.cpp

HEADERS  += mainwindow.h \
    visualizer.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    icons.qrc \
    shaders.qrc

DISTFILES += \
    fshader.fsh \
    vshader.vsh \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

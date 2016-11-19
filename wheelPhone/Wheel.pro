#-------------------------------------------------
#
# Project created by QtCreator 2016-11-16T06:20:32
#
#-------------------------------------------------

QT       += core gui sensors

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Wheel
TEMPLATE = app


SOURCES += main.cpp\
        wheel.cpp \

HEADERS  += wheel.h

RESOURCES += \
    res.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

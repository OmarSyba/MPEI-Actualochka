QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/../../ActualochkaAndroidDebug
} else {
    DESTDIR = $$OUT_PWD/../../ActualochkaAndroidRelease
}

android {
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

    DISTFILES += \
        android/AndroidManifest.xml \
	android/build.gradle \
	android/res/values/libs.xml
}

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    include/Mainwindow/mainwindow.hpp

FORMS += \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

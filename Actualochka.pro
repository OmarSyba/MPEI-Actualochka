QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/../../ActualochkaDebug
} else {
    DESTDIR = $$OUT_PWD/../../ActualochkaRelease
}

TEMPLATE = app

MOC_DIR = ../common/build/moc
RCC_DIR = ../common/build/rcc
UI_DIR =  ../common/build/ui

CONFIG(debug, debug|release) {
    QMAKE_POST_LINK = windeployqt $$OUT_PWD/../../ActualochkaDebug
} else {
    QMAKE_POST_LINK = windeployqt $$OUT_PWD/../../ActualochkaRelease
}

win32:OBJECTS_DIR = ../common/build/o/win32
macx:OBJECTS_DIR = ../common/build/o/macx
unix:OBJECTS_DIR = ../common/build/o/unix

SOURCES += \
    src/confighandler.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/networreplyer.cpp \
    src/serverjsonparser.cpp

HEADERS += \
    include/General/general.hpp \
    include/Mainwindow/mainwindow.hpp \
    include/General/confighandler.hpp \
    include/Receiver/serverjsonparser.hpp \
    include/Receiver/networreplyer.hpp

FORMS += \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/res.qrc


RC_ICONS = resources/favicon.ico
#TARGET = "Actualochka Пetter"

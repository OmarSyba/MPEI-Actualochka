QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/confighandler.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/serverdatahandler.cpp

HEADERS += \
    include/General/general.hpp \
    include/Mainwindow/mainwindow.hpp \
    include/General/confighandler.hpp \
    include/Receiver/iserveractualochka.hpp \
    include/Receiver/iservershedule.hpp \
    include/Receiver/serverdatahandler.hpp

FORMS += \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/res.qrc


RC_ICONS = favicon.ico
#TARGET = "Actualochka Пetter"

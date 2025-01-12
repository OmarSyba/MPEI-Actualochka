QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(debug, debug|release) {
    DESTDIR = ../ActualochkaDebug
} else {
    DESTDIR = ../ActualochkaRelease
}

OPENSSL = D:/Frameworks/Qt/Tools/OpenSSL/Win_x64/bin
win32 {
    EXTRA_BINFILES += \
        $$OPENSSL\libcrypto-1_1-x64.dll \
	$$OPENSSL\libssl-1_1-x64.dll
    EXTRA_BINFILES_WIN = $${EXTRA_BINFILES}
    EXTRA_BINFILES_WIN ~= s,/,\\,g
        DESTDIR_WIN = $${DESTDIR}
    DESTDIR_WIN ~= s,/,\\,g
    for(FILE,EXTRA_BINFILES_WIN){
            QMAKE_POST_LINK +=$$quote(cmd /c copy /y $${FILE} $${DESTDIR_WIN}$$escape_expand(\n\t))
    }
}

TEMPLATE = app

MOC_DIR = ../common/build/moc
RCC_DIR = ../common/build/rcc
UI_DIR =  ../common/build/ui

CONFIG(debug, debug|release) {
    QMAKE_POST_LINK += windeployqt ../ActualochkaDebug
} else {
    QMAKE_POST_LINK += windeployqt ../ActualochkaRelease
}

win32:OBJECTS_DIR = ../common/build/o/win32
macx:OBJECTS_DIR = ../common/build/o/macx
unix:OBJECTS_DIR = ../common/build/o/unix

SOURCES += \
    src/adminloginwindow.cpp \
    src/calendardatehandler.cpp \
    src/contentfileio.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/serverjsonparser.cpp \
    src/switchbutton.cpp \
    src/usystemtray.cpp \
    src/utimerhandler.cpp \
    src/uwebhandler.cpp \
    src/configerexplorer.cpp

HEADERS += \
    include/General/configerexplorer.hpp \
    include/General/general.hpp \
    include/General/themechanger.hpp \
    include/Mainwindow/adminloginwindow.hpp \
    include/Mainwindow/mainwindow.hpp \
    include/System/calendardatehandler.hpp \
    include/System/contentfileio.hpp \
    include/System/serverjsonparser.hpp \
    include/System/usystemtray.hpp \
    include/System/utimerhandler.hpp \
    include/System/uwebhandler.hpp \
    include/UI/switchbutton.hpp

FORMS += \
    ui/adminloginwindow.ui \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/qdarkstyle/darkstyle.qrc \
    resources/qlightstyle/style.qrc \
    resources/res.qrc

win32:VERSION = 1.3.5.0
else:VERSION = 1.3.5

WINRT_MANIFEST.publisher = mpei.space

RC_ICONS = resources/favicon.ico
#TARGET = "Actualochka Пetter"

DISTFILES += \
    resources/qdarkstyle/style.qss

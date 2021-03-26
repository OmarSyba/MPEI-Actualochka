# Before run make project, need to put executable file and dlls into
 
TEMPLATE = aux
 
# В зависимости от режима сборки, определяем, куда именно будут собираться инсталляторы
CONFIG(debug, debug|release) {
    INSTALLER_OFFLINE = $$OUT_PWD/../../InstallerDebug/Actualochkaoff.exe
    INSTALLER_ONLINE = $$OUT_PWD/../../InstallerDebug/Actualochkaon.exe
    DESTDIR_WIN = $$PWD/packages/ru.sybabubik.actualochkainstaller/data
    DESTDIR_WIN ~= s,/,\\,g
    PWD_WIN = $$OUT_PWD/../../ActualochkaDebug
    PWD_WIN ~= s,/,\\,g
 
    copydata.commands = $(COPY_DIR) $$PWD_WIN $$DESTDIR_WIN
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
} else {
    # Задаём переменные, которые будут содержать пути с названиями инсталляторов
    INSTALLER_OFFLINE = $$OUT_PWD/../../InstallerRelease/Actualochkaoff.exe
    INSTALLER_ONLINE = $$OUT_PWD/../../InstallerRelease/Actualochkaon.exe
 
    # Задаём переменную, которая должна содержать путь к папке с данными
    DESTDIR_WIN = $$PWD/packages/ru.sybabubik.actualochkainstaller/data
    DESTDIR_WIN ~= s,/,\\,g
    # Задаём путь откуда всё приложение с DLL-ками нужно будет скопировать
    PWD_WIN = $$OUT_PWD/../../ActualochkaRelease
    PWD_WIN ~= s,/,\\,g
 
    # Прежде, чем выполнять сборку инсталляторов, необходимо скопировать файлы
    # из выходной папки проекта вместе со всеми DLL в папку data, которая относится
    # к собираемому пакету
    copydata.commands = $(COPY_DIR) $$PWD_WIN $$DESTDIR_WIN
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    # задаём кастомную цель сборки, при которой сначала выполним компирование файлов
    # а потом уже и остальное, что следует по скрипту QMake
    QMAKE_EXTRA_TARGETS += first copydata
}
 
# Создаём цель по сборке Оффлайн Инсталлятора
INPUT = $$PWD/config/config.xml $$PWD/packages
offlineInstaller.depends = copydata
offlineInstaller.input = INPUT
offlineInstaller.output = $$INSTALLER_OFFLINE
offlineInstaller.commands = $$(QTDIR)/../../bin/binarycreator --offline-only -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}
offlineInstaller.CONFIG += target_predeps no_link combine
 
QMAKE_EXTRA_COMPILERS += offlineInstaller
 
# Создаём цель по сборке Онлайн Инсталлятора
INPUT = $$PWD/config/config.xml $$PWD/packages
onlineInstaller.depends = copydata
onlineInstaller.input = INPUT
onlineInstaller.output = $$INSTALLER_ONLINE
onlineInstaller.commands = $$(QTDIR)/../../bin/binarycreator --online-only -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}
onlineInstaller.CONFIG += target_predeps no_link combine
 
QMAKE_EXTRA_COMPILERS += onlineInstaller
 
# репозиторий будем собирать только в случае режима release
CONFIG(release, debug|release) {
    # Сборку репозитория производим после того, как были собраны Инсталляторы
    # Для этого воспользуемся QMAKE_POST_LINK вместо QMAKE_EXTRA_COMPILERS
    # Поскольку он хорошо для этого подходит
    QMAKE_POST_LINK += $$(QTDIR)/../../bin/repogen -p $$PWD/packages -i ru.sybabubik.actualochkainstaller --update $$PWD/../../repository
}
 
DISTFILES += \
    config/config.xml \
    config/style.qss \
    packages/ru.sybabubik.actualochkainstaller/meta/installscript.qs \
    packages/ru.sybabubik.actualochkainstaller/meta/package.xml \
    config/config.xml \
    packages/ru.sybabubik.actualochkainstaller/meta/package.xml

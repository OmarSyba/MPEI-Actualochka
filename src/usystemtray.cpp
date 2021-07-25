#include "../include/System/usystemtray.hpp"

USystemTray::USystemTray(QObject *parent) : QSystemTrayIcon(parent)
{
    setIcon(QIcon(":/icon/favicon.ico"));
    systemTrayMenu = new QMenu();
    tooltip = new QMenu();

    QAction *exit           = new QAction(tr("Выход"));
    QAction *devConnect     = new QAction(tr("Связаться с разработчиками"));
    QAction *settingsTab    = new QAction(tr("Настройки"));
    QAction *calendarTab    = new QAction(tr("Календарь"));

    systemTrayMenu->addAction(calendarTab);
    systemTrayMenu->addAction(settingsTab);
    systemTrayMenu->addSeparator();
    systemTrayMenu->addAction(devConnect);
    systemTrayMenu->addSeparator();
    systemTrayMenu->addAction(exit);

    exit->setIcon(QIcon(":menu/exit.png"));
    settingsTab->setIcon(QIcon(":menu/settings.png"));
    calendarTab->setIcon(QIcon(":menu/calendar.png"));
    devConnect->setIcon(QIcon(":menu/dev.png"));

    setContextMenu(systemTrayMenu);
    actions.append(calendarTab);
    actions.append(settingsTab);
    actions.append(devConnect);
    actions.append(exit);
    show();
}

USystemTray::~USystemTray()
{
    actions.clear();
    if (tooltip)
        delete tooltip;
    if (systemTrayMenu)
        delete systemTrayMenu;
}

QAction *USystemTray::GetSettingsAction() const
{
    return actions.at(1);
}

QAction *USystemTray::GetCalendarAction() const
{
    return actions.at(0);
}

QAction *USystemTray::GetExitAction() const
{
    return actions.at(3);
}

QAction *USystemTray::GetDevConnectAction() const
{
    return actions.at(2);
}

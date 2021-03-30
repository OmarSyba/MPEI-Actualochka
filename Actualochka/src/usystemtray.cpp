#include "../include/System/usystemtray.hpp"

USystemTray::USystemTray(QObject *parent) : QSystemTrayIcon(parent)
{
    setIcon(QIcon(":/icon/favicon.ico"));
    systemTrayMenu = new QMenu();

    QAction *exit           = new QAction(tr("Выход"));
    QAction *settingsTab    = new QAction(tr("Настройки"));
    QAction *calendarTab    = new QAction(tr("Календарь"));

    systemTrayMenu->addAction(calendarTab);
    systemTrayMenu->addAction(settingsTab);
    systemTrayMenu->addSeparator();
    systemTrayMenu->addAction(exit);

    setContextMenu(systemTrayMenu);
    actions.append(calendarTab);
    actions.append(settingsTab);
    actions.append(exit);

    show();
}

USystemTray::~USystemTray()
{
    for (auto& x : actions)
    {
        delete x;
    }
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
    return actions.at(2);
}

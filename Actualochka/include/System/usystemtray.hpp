#ifndef USYSTEMTRAY_HPP
#define USYSTEMTRAY_HPP

#include <QSystemTrayIcon>
#include <QObject>
#include <QAction>
#include <QMenu>

class USystemTray : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit USystemTray(QObject *parent = nullptr);
    virtual ~USystemTray() override;

    QAction *GetSettingsAction()    const;
    QAction *GetCalendarAction()    const;
    QAction *GetExitAction()        const;

    void setContextMenuTimer(qint64 time);

private:
    QMenu *toolTipTimer = nullptr;
    QVector<QAction *> actions;
    QMenu *systemTrayMenu = nullptr;
};

#endif // USYSTEMTRAY_HPP

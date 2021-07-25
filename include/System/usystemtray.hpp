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
    QAction *GetDevConnectAction()  const;

public:
    void setContextMenuTimer(qint64 time);

private:
    QVector<QAction *> actions;
    QMenu *tooltip = nullptr;
    QMenu *systemTrayMenu = nullptr;
};

#endif // USYSTEMTRAY_HPP

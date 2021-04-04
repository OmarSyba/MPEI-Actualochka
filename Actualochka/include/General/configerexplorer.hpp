#ifndef CONFIGEREXPLORER_HPP
#define CONFIGEREXPLORER_HPP

#include "general.hpp"

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

struct ConfigData
{
    quint32 appRun;
    quint64 interval;

    bool isAutoRunEnable;
    bool isNotifyEnable;

    quint32 groupId;
    QString groupName;
};

class ConfigerExplorer : public QObject
{
    Q_OBJECT
public:
    explicit ConfigerExplorer(QObject *parent = nullptr);
    virtual ~ConfigerExplorer() override;

    void OpenJsonConfig();
    void SaveConfigIntoFile();

    ConfigData& GetConfigData();
    quint32 GetAppRuns() const;
    quint64 GetInterval() const;
    bool isFirstRun() const;
    bool isAutoRunEnabled() const;
    bool isNotifyEnabled() const;
    quint32 GetGroupId() const;
    QString GetGroupName() const;

    void AppRunsAdd();
    void SetInterval(quint64 ms);
    void SetAutoRunEnabled(bool tRun);
    void SetNotifyEnabled(bool tNotify);
    void SetGroupId(quint32 tId);
    void SetGroupName(QString& tName);

private:
    void HandleConfig();
    void SetDefaultConfig();

private:
    QJsonObject *_jsonObject = nullptr;
    ConfigData _cData;
};

#endif // CONFIGEREXPLORER_HPP

#include "include/General/configerexplorer.hpp"
#include <QFile>

ConfigerExplorer::ConfigerExplorer(QObject *parent) : QObject(parent)
{

}

ConfigerExplorer::~ConfigerExplorer()
{
    if (_jsonObject)
        delete _jsonObject;
}

void ConfigerExplorer::OpenJsonConfig()
{
    QFile config(act::ConfigPath);
    if (!config.open(QIODevice::ReadWrite))
    {
        qDebug() << "Can't open config file";
        return;
    }
    QJsonDocument jsonDocument = QJsonDocument::fromJson(config.readAll());
    _jsonObject = new QJsonObject(jsonDocument.object());

    /* means that config hadn't existed */
    if (config.pos() == 0)
    {
        (*_jsonObject)["runs"] = 0;
        (*_jsonObject)["interval"] = QString::number(act::Interval).toStdString().c_str();
        (*_jsonObject)["autorun"] = false;
        (*_jsonObject)["notify"] = true;
        (*_jsonObject)["groupId"] = 12861;
        (*_jsonObject)["groupName"] = tr("40a-20");
    }
    config.close();
    HandleConfig();
}

void ConfigerExplorer::SaveConfigIntoFile()
{
    if (_jsonObject)
    {
        qDebug() << "Config doesn't exist! Can't save!";
        return;
    }

    QFile config(act::ConfigPath);
    if (!config.open(QIODevice::WriteOnly))
    {
        qDebug() << "Config can't open to save!";
        SetDefaultConfig();
    }
    else
    {
        (*_jsonObject)["runs"]      = QString::number(_cData.appRun).toStdString().c_str();
        (*_jsonObject)["interval"]  = QString::number(_cData.interval).toStdString().c_str();
        (*_jsonObject)["autorun"]   = _cData.isAutoRunEnable;
        (*_jsonObject)["notify"]    = _cData.isNotifyEnable;
        (*_jsonObject)["groupId"]   =  QString::number(_cData.groupId).toStdString().c_str();
        (*_jsonObject)["groupName"] = _cData.groupName.toStdString().c_str();

        config.write(QJsonDocument(*_jsonObject).toJson(QJsonDocument::Indented));
        config.close();
    }
}

void ConfigerExplorer::HandleConfig()
{
    if (!_jsonObject)
    {
        qDebug() << "Config doesn't exist";
        SetDefaultConfig();
    }

    _cData.appRun           = (*_jsonObject)["runs"].toInteger();
    _cData.interval         = (*_jsonObject)["interval"].toInteger();
    _cData.isAutoRunEnable  = (*_jsonObject)["autorun"].toBool();
    _cData.isNotifyEnable   = (*_jsonObject)["notify"].toBool();
    _cData.groupId          = (*_jsonObject)["groupId"].toInteger();
    _cData.groupName        = (*_jsonObject)["groupName"].toString();

    /* for backward compatibility */
    if (_cData.groupId == 0)
    {
        _cData.groupId = 12861;
        _cData.groupName = tr("40а-20");
    }
}

void ConfigerExplorer::SetDefaultConfig()
{
    _cData.appRun           = 0;
    _cData.interval         = act::Interval;
    _cData.isAutoRunEnable  = false;
    _cData.isNotifyEnable   = true;
    _cData.groupId          = 12861;
    _cData.groupName        = tr("40a-20");
}

ConfigData &ConfigerExplorer::GetConfigData()
{
    return _cData;
}

quint32 ConfigerExplorer::GetAppRuns() const
{
    return _cData.appRun;
}

quint64 ConfigerExplorer::GetInterval() const
{
    return _cData.interval;
}

bool ConfigerExplorer::isFirstRun() const
{
    return !_cData.appRun;
}

bool ConfigerExplorer::isAutoRunEnabled() const
{
    return _cData.isAutoRunEnable;
}

bool ConfigerExplorer::isNotifyEnabled() const
{
    return _cData.isNotifyEnable;
}

quint32 ConfigerExplorer::GetGroupId() const
{
    return _cData.groupId;
}

QString ConfigerExplorer::GetGroupName() const
{
    return _cData.groupName;
}

void ConfigerExplorer::AppRunsAdd()
{
    _cData.appRun++;
}

void ConfigerExplorer::SetInterval(quint64 ms)
{
    _cData.interval = ms;
}

void ConfigerExplorer::SetAutoRunEnabled(bool tRun)
{
    _cData.isAutoRunEnable = tRun;
}

void ConfigerExplorer::SetNotifyEnabled(bool tNotify)
{
    _cData.isNotifyEnable = tNotify;
}

void ConfigerExplorer::SetGroupId(quint32 tId)
{
    _cData.groupId = tId;
}

void ConfigerExplorer::SetGroupName(QString &tName)
{
    _cData.groupName = tName;
}

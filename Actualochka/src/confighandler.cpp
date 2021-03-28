#include "../include/General/confighandler.hpp"
#include "../include/General/general.hpp"

#include <QFile>

SConfig::SConfig()
{

}

SConfig::~SConfig()
{
    delete _jsonObject;
}

QJsonObject *SConfig::OpenConfigJson()
{
    QFile file(act::ConfigPath);
    if (!file.open(QIODevice::ReadWrite))
    {
        return nullptr;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(saveData);

    _jsonObject = new QJsonObject(jsonDocument.object());

    if (file.pos() == 0)
    {
        (*_jsonObject)["runs"] = 1;
        (*_jsonObject)["interval"] = (int)Interval;
        (*_jsonObject)["autorun"] = false;
        (*_jsonObject)["notify"] = true;
        (*_jsonObject)["groupId"] = 12861;
        (*_jsonObject)["groupName"] = "40a-20";
    }

    file.close();
    return _jsonObject;
}

void SConfig::HandleConfigJson(QJsonObject *jsonObject)
{
    if (!jsonObject)
    {
        return;
    }

    _appRuns = (*jsonObject)["runs"].toInt();
    _interval = (*jsonObject)["interval"].toInt();
    _autoRun = (*jsonObject)["autorun"].toBool();
    _notify = (*jsonObject)["notify"].toBool();
    _groupId = (*jsonObject)["groupId"].toInteger();
    _groupName = (*jsonObject)["groupName"].toString();

    if (_appRuns == 1)
    {
        _interval = Interval;
        _autoRun = false;
        _groupId = 12861;
        _groupName = "40a-20";
    }

    if (_groupId == 0)
    {
        _groupId = 12861;
        _groupName = "40a-20";
    }
}

void SConfig::WriteJson(QJsonObject *jsonObject)
{
    if (!jsonObject)
    {
        return;
    }
    (*jsonObject)["runs"] = (int)_appRuns + 1;
    (*jsonObject)["interval"] = (int)_interval;
    (*jsonObject)["autorun"] = _autoRun;
    (*jsonObject)["notify"] = _notify;
    (*jsonObject)["groupId"] = (int)_groupId;
    (*jsonObject)["groupName"] = _groupName.toStdString().c_str();

    QFile jsonFile(act::ConfigPath);
    if (!jsonFile.open(QIODevice::WriteOnly))
    {
        return;
    }

    jsonFile.write(QJsonDocument(*jsonObject).toJson(QJsonDocument::Indented));
    jsonFile.close();
}

bool SConfig::isFirstRun() const noexcept
{
    return !(*_jsonObject)["runs"].toInt();
}

bool SConfig::isAutoRunEnable() const
{
    return _autoRun;
}

bool SConfig::isNotify() const
{
    return _notify;
}

quint32 SConfig::GetGroupId()
{
    return _groupId;
}

QString SConfig::GetGroupName() const
{
    return _groupName;
}

void SConfig::SetAutoRun(bool run)
{
    _autoRun = run;
}

void SConfig::SetInterval(uint32_t ms)
{
    _interval = (int)ms;
}

void SConfig::SetUrl(QString &url)
{
    act::MpeiActuallity = url;
}

void SConfig::SetNotify(bool notify)
{
    _notify = notify;
}

void SConfig::SetGroupId(quint32 id)
{
    _groupId = id;
}

void SConfig::SetGroupName(QString name)
{
    _groupName = name;
}

QString SConfig::GetUrl() const noexcept
{
    return act::MpeiActuallity;
}

uint32_t SConfig::GetInterval() const noexcept
{
    return _interval;
}

QJsonObject *SConfig::GetJson() const
{
    return _jsonObject;
}

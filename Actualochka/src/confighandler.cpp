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
        //TODO
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

    //qDebug() << (*jsonObject)["autorun"].toBool() << (*jsonObject)["autorun"];

    if (_appRuns == 1)
    {
        _interval = Interval;
        _autoRun = false;
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

    QFile jsonFile(act::ConfigPath);
    if (!jsonFile.open(QIODevice::WriteOnly))
    {
        //TODO
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

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
    QFile file(act::configPath);
    if (!file.open(QIODevice::ReadWrite))
    {
        //TODO
    }

    if (file.pos() == 0)
    {
        qDebug() << "Here";
    }

    QByteArray saveData = file.readAll();
    QJsonDocument jsonDocument = QJsonDocument::fromJson(saveData);

    _jsonObject = new QJsonObject(jsonDocument.object());

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
    _autoRun = (*jsonObject)["autorun"].isBool();
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

    QFile jsonFile(act::configPath);
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

void SConfig::SetAutoRun(bool run)
{
    (*_jsonObject)["autorun"] = (int)run;
}

void SConfig::SetInterval(uint32_t ms)
{
    (*_jsonObject)["interval"] = (int)ms;
}

void SConfig::SetUrl(QString &url)
{
    act::mpei_url = url;
}

QString SConfig::GetUrl() const noexcept
{
    return act::mpei_url;
}

uint32_t SConfig::GetInterval() const noexcept
{
    return (*_jsonObject)["interval"].toInteger();
}

QJsonObject *SConfig::GetJson() const
{
    return _jsonObject;
}

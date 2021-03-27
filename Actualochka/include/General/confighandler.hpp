#ifndef CONFIGHANDLER_HPP
#define CONFIGHANDLER_HPP

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

static uint32_t Interval = 28800000;

class SConfig
{
public:
    SConfig();
    ~SConfig();

    QJsonObject *OpenConfigJson();
    void HandleConfigJson(QJsonObject *jsonObject);
    void WriteJson(QJsonObject *jsonObject);

    bool isFirstRun() const noexcept;
    bool isAutoRunEnable() const;
    bool isNotify() const;
    uint32_t GetRunsCount() const noexcept;

    void SetAutoRun(bool run);
    void SetInterval(uint32_t ms);
    void SetUrl(QString& url);
    void SetNotify(bool notify);

    QString GetUrl() const noexcept;
    uint32_t GetInterval() const noexcept;

    QJsonObject *GetJson() const;
private:
    QJsonObject *_jsonObject = nullptr;

    uint32_t _appRuns;
    uint32_t _interval;
    bool _notify;
    bool _autoRun;
};

#endif // CONFIGHANDLER_HPP

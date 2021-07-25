#ifndef THEMECHANGER_H
#define THEMECHANGER_H

#include <QList>
#include <QObject>

class IListnerTheme : public QObject
{
    Q_OBJECT
public:
    virtual void update(bool isDark) = 0;
};

class ThemeManager
{
public:
    void subscribe(IListnerTheme *object)
    {
        if (object)
            _listeners.append(object);
    }

    void unsubscribe(IListnerTheme *object)
    {
        QList<IListnerTheme *>::iterator it = std::find_if(_listeners.begin(), _listeners.end(), [&](IListnerTheme *t_object)
        {
            return object == t_object;
        });

        if (it)
            _listeners.erase(it);
    }

    void notify(bool isDark)
    {
        std::for_each(_listeners.cbegin(), _listeners.cend(), [&](IListnerTheme *t_object)
        {
            t_object->update(isDark);
        });
    }

private:
    QList<IListnerTheme *> _listeners;

};

#endif // THEMECHANGER_H

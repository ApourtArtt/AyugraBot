#ifndef EVENTBASE_H
#define EVENTBASE_H

#include <QObject>

class EventBase : public QObject
{
    Q_OBJECT
public:
    EventBase(){}
    EventBase(QObject *parent, bool Subscribed);
    virtual QStringList getPackets() const;
    virtual std::vector<int> getDelays() const;
    void unsubscribe();
    void subscribe();

protected:
    bool subscribed;
};


#endif // EVENTBASE_H

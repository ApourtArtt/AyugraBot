#include "eventbase.h"

EventBase::EventBase(QObject *parent, bool Subscribed)
    : QObject(parent)
{
    subscribed = Subscribed;
}

void EventBase::unsubscribe()
{
    subscribed = false;
}

void EventBase::subscribe()
{
    subscribed = true;
}

QStringList EventBase::getPackets() const
{
    return {};
}

std::vector<int> EventBase::getDelays() const
{
    return {};
}

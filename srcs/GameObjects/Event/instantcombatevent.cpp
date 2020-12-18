#include "instantcombatevent.h"

InstantCombatEvent::InstantCombatEvent(QObject *parent, bool subscribe, QString Answer)
    : EventBase(parent, subscribe)
{
    answer = Answer;
}

QStringList InstantCombatEvent::getPackets() const
{
    return
    {
        "guri 508",
        answer
    };
}

std::vector<int> InstantCombatEvent::getDelays() const
{
    return
    {
        15 + qrand() % 500,
        15 + qrand() % 500
    };
}

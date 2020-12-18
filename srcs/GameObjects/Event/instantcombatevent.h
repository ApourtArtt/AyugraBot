#ifndef INSTANTCOMBATEVENT_H
#define INSTANTCOMBATEVENT_H

//Rainbow Crystal Battle
#include <QTimer>
#include "srcs/GameObjects/Event/eventbase.h"

class InstantCombatEvent : public EventBase
{
public:
    explicit InstantCombatEvent(QObject *parent, bool Subscribed, QString Answer);
    QStringList getPackets() const override;
    std::vector<int> getDelays() const override;

private:
    QString answer;
};

#endif // INSTANTCOMBATEVENT_H

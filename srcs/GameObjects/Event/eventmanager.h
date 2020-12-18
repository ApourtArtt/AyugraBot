#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <QObject>
#include <QTimer>
#include <QMap>
#include "srcs/Packets/Server/World/packetqnamli.h"
#include "srcs/Packets/Server/World/packetesf.h"
#include "srcs/GameObjects/Event/instantcombatevent.h"

class EventManager : public QObject
{
    Q_OBJECT
public:
    EventManager(QObject *parent);
    void handleQnamliPacket(PacketQnamli Packet);
    void handleEsfPacket(PacketEsf Packet);
    void subscribeToEvent(EventType event, bool subscribe, QString answer = "");
    void unsubscribeFromEvent(EventType event);

signals:
    void newEvent(EventType eventType);
    void sendPacket(QString packet);

private:
    void handleEvent(EventType event);
    void createEvent(EventType event, bool subscribe, QString answer);
    QMap<EventType, EventBase*> events;
};

#endif // EVENTMANAGER_H

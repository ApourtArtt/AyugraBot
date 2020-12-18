#include "eventmanager.h"

EventManager::EventManager(QObject *parent)
    : QObject(parent)
{

}

void EventManager::handleQnamliPacket(PacketQnamli Packet)
{
    EventType event = Packet.getEventType();
    if(!events.contains(event))
        subscribeToEvent(event, false, Packet.getResponsePacket());
    else
        handleEvent(event);
    emit newEvent(event);
}
// Well, need to design this function, not hardcoded value and
// this kind of condition.
void EventManager::handleEsfPacket(PacketEsf Packet)
{
    int eventID = Packet.getID();
    if(eventID == 0)
    {
         // No more Rainbow
    }
    else if(eventID == 4)
    {
        // No more IC
    }
    // Total unsubscription ?..
    // Just saying "not available anymore" ?..
}

void EventManager::subscribeToEvent(EventType event, bool subscribe, QString answer)
{
    if(!events.contains(event))
        createEvent(event, subscribe, answer);
    else
    {
        if(!subscribe)
            events[event]->unsubscribe();
        else
            events[event]->subscribe();
    }
}

void EventManager::unsubscribeFromEvent(EventType event)
{
    events.remove(event);
}

void EventManager::handleEvent(EventType event)
{
    if(!events.contains(event))
        return;
    QStringList packets = events[event]->getPackets();
    std::vector<int> delays = events[event]->getDelays();
    for(size_t i = 0 ; static_cast<int>(i) < packets.size() ; i++)
    {
        QTimer::singleShot(delays.size() > i ? delays[i] : 0, [=]
        {
            sendPacket(packets[static_cast<int>(i)]);
        });
    }
}

void EventManager::createEvent(EventType event, bool subscribe, QString answer)
{
    if(event == EventType::INSTANTCOMBAT)
    {
        events.insert(event, new InstantCombatEvent(this, subscribe, answer));
    }
    else if(event == EventType::ICEBREAKER)
    {
        // Todo
    }
    else if(event == EventType::RAINBOWCRYSTALBATTLE)
    {
        // Todo
    }
    else
    {
        // Sheep event, ...
        // Won't add it for now. Focus on IC.
    }
}

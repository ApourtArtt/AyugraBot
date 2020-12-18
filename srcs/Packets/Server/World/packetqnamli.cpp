#include "packetqnamli.h"

PacketQnamli::PacketQnamli(QStringList Packet)
    : BasePacket(Packet)
{

}

EventType PacketQnamli::getEventType()
{
    return static_cast<EventType>(packet[1].toInt());
}
//qnamli2 100 #rl 1646 11 3027 -Tetsuga- => liste, packet different
//qnamli 2 #guri^501 365 4 10000 0
// ice
QString PacketQnamli::getResponsePacket()
{
    if(packet.size() > 2)
        return packet[2];
    return nullptr;
}

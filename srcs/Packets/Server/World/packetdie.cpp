#include "packetdie.h"

PacketDie::PacketDie(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketDie::getEntityType()
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketDie::getID()
{
    return packet[2].toInt();
}

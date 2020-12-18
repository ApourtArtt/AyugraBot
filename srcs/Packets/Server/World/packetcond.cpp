#include "packetcond.h"

PacketCond::PacketCond(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketCond::getEntityType()
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketCond::getID()
{
    return packet[2].toInt();
}

bool PacketCond::isStunned()
{
    return packet[3].toInt();
}

bool PacketCond::isRooted()
{
    return packet[4].toInt();
}

short PacketCond::getSpeed()
{
    return packet[5].toShort();
}

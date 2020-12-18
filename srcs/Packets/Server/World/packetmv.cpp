#include "packetmv.h"

PacketMv::PacketMv(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketMv::getEntityType()
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketMv::getID()
{
    return packet[2].toInt();
}

short PacketMv::getX()
{
    return packet[3].toShort();
}

short PacketMv::getY()
{
    return packet[4].toShort();
}

short PacketMv::getSpeed()
{
    return packet[5].toShort();
}

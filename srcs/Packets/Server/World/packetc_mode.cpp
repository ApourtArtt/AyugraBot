#include "packetc_mode.h"

PacketC_mode::PacketC_mode(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketC_mode::getEntityType()
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketC_mode::getEntityID()
{
    return packet[2].toInt();
}

int PacketC_mode::getMorphID()
{
    return packet[3].toInt();
}

short PacketC_mode::getSPUpgrade()
{
    return packet[4].toShort();
}

Wings PacketC_mode::getWingsType()
{
    return static_cast<Wings>(packet[5].toInt());
}

bool PacketC_mode::isADMWinner()
{
    return packet[6].toInt();
}

short PacketC_mode::getSize()
{
    return packet[7].toShort();
}

#include "packetgp.h"

PacketGp::PacketGp(QStringList Packet)
    : BasePacket(Packet)
{

}

short PacketGp::getX()
{
    return packet[1].toShort();
}

short PacketGp::getY()
{
    return packet[2].toShort();
}

int PacketGp::getMapID()
{
    return packet[3].toInt();
}

PortalType PacketGp::getType()
{
    return static_cast<PortalType>(packet[4].toInt());
}

int PacketGp::getID()
{
    return packet[5].toInt();
}

bool PacketGp::isInvisible()
{
    return packet[6].toInt();
}

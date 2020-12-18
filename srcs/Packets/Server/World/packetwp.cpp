#include "packetwp.h"

PacketWp::PacketWp(QStringList Packet)
    : BasePacket(Packet)
{

}

short PacketWp::getX()
{
    return packet[1].toShort();
}

short PacketWp::getY()
{
    return packet[2].toShort();
}

int PacketWp::getID()
{
    return packet[3].toInt();
}

TimeSpaceType PacketWp::getType()
{
    return static_cast<TimeSpaceType>(packet[4].toInt());
}

short PacketWp::getLvlMin()
{
    return packet[5].toShort();
}

short PacketWp::getLvlMax()
{
    return packet[6].toShort();
}

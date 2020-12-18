#include "packetc_map.h"

PacketC_map::PacketC_map(QStringList Packet)
    : BasePacket(Packet)
{

}

int PacketC_map::getMapID()
{
    return packet[2].toInt();
}

bool PacketC_map::isGoingTo()
{
    return packet[3].toInt();
}

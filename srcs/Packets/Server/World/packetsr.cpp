#include "packetsr.h"

PacketSr::PacketSr(QStringList Packet)
    : BasePacket(Packet)
{

}

int PacketSr::getEventID()
{
    return packet[1].toInt();
}

int PacketSr::getCastID()
{
    return packet.size() == 2 ? packet[1].toInt() : packet[2].toInt();
}

int PacketSr::getRemainingCooldown()
{
    return packet.size() == 4 ? packet[3].toInt() : 0;
}

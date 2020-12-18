#include "packetstat.h"

PacketStat::PacketStat(QStringList Packet)
    : BasePacket(Packet)
{

}

int PacketStat::getCurrentHP()
{
    return packet[1].toInt();
}

int PacketStat::getMaxHP()
{
    return packet[2].toInt();
}

int PacketStat::getCurrentMP()
{
    return packet[3].toInt();
}

int PacketStat::getMaxMP()
{
    return packet[4].toInt();
}

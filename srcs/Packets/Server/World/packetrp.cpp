#include "packetrp.h"

PacketRp::PacketRp(QStringList Packet)
    : BasePacket(Packet)
{

}

int PacketRp::getMapID() const
{
    return packet[1].toInt();
}

int PacketRp::getX() const
{
    return packet[2].toInt();
}

int PacketRp::getY() const
{
    return packet[3].toInt();
}

QString PacketRp::getPacketToAccept() const
{
    return packet[4];
}

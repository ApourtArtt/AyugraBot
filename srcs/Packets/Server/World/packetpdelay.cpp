#include "packetpdelay.h"

PacketPdelay::PacketPdelay(QStringList Packet)
    : BasePacket(Packet)
{

}

int PacketPdelay::msToWait() const
{
    return packet[1].toInt();
}

int PacketPdelay::getGuriArgument() const
{
    return packet[2].toInt();
}

QString PacketPdelay::getPacketAnswer() const
{
    return packet[3];
}

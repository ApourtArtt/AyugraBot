#include "packetdelay.h"

PacketDelay::PacketDelay(QStringList Packet)
    : BasePacket(Packet)
{

}

int PacketDelay::msToWait() const
{
    return packet[1].toInt();
}

int PacketDelay::getGuriArgument() const
{
    return packet[2].toInt();
}

QString PacketDelay::getPacketAnswer() const
{
    return packet[3];
}

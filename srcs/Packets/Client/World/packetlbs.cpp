#include "packetlbs.h"

PacketLbs::PacketLbs(short Value)
    : BasePacket("lbs")
{
    value = Value;
    packet.push_back(QString::number(value));
}

bool PacketLbs::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    if(value != 0)
        return false;
    return true;
}

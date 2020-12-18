#include "packetc_close.h"

PacketC_close::PacketC_close(short Value)
    : BasePacket("c_close")
{
    value = Value;
    packet.push_back(QString::number(value));
}

bool PacketC_close::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    if(value < 0 || value > 1)
        return false;
    return true;
}

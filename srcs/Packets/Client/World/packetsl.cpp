#include "packetsl.h"

PacketSl::PacketSl(bool Instant)
    : BasePacket("sl")
{
    instant = Instant;
    packet.push_back(QString::number(instant));
}

bool PacketSl::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    return true;
}

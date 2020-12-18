#include "packetpsl.h"

PacketPsl::PacketPsl(bool Instant)
    : BasePacket("psl")
{
    instant = Instant;
    packet.push_back(QString::number(instant));
}

bool PacketPsl::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    return true;
}

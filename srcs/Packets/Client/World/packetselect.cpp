#include "packetselect.h"

PacketSelect::PacketSelect(short Slot)
    : BasePacket("select")
{
    slot = Slot;
    packet.push_back(QString::number(slot));
}

bool PacketSelect::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    if(slot < 0 || slot > 3)
        return false;
    return true;
}

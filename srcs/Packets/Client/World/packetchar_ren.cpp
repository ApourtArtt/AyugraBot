#include "packetchar_ren.h"

PacketCHAR_REN::PacketCHAR_REN(short Slot, QString Pseudonym)
    : BasePacket("CHAR_REN")
{
    slot = Slot;
    pseudonym = Pseudonym;
    packet.push_back(QString::number(slot));
    packet.push_back(pseudonym);
}

bool PacketCHAR_REN::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    if(slot < 0 || slot > 3)
        return false;
    if(pseudonym.size() < 3)
        return false;
    return true;
}

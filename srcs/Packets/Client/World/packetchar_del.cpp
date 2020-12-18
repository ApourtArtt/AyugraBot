#include "packetchar_del.h"

PacketChar_DEL::PacketChar_DEL(short Slot, QString Username)
    : BasePacket("Char_DEL")
{
    slot = Slot;
    username = Username;
    packet.push_back(QString::number(slot));
    packet.push_back(username);
}

bool PacketChar_DEL::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    if(slot < 0 || slot > 3)
        return false;
    if(username.size() < 4) // Not sure about size, so let's put 4 and no max.
        return false;
    return true;
}

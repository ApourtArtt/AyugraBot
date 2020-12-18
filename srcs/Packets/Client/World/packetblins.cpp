#include "packetblins.h"

PacketBlins::PacketBlins(int characterID)
    : BasePacket("blins")
{
    id = characterID;
    packet.push_back(QString::number(id));
}

bool PacketBlins::isSendable()
{
    if(id < 0)
        return false;
    if(packet.size() != PACKET_SIZE)
        return false;
    return true;
}

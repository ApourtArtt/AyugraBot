#include "packetfins.h"

PacketFins::PacketFins(int characterID)
    : BasePacket("fins")
{
    id = characterID;
    packet.push_back("1");
    packet.push_back(QString::number(id));
}

bool PacketFins::isSendable()
{
    if(id < 0)
        return false;
    if(packet.size() != PACKET_SIZE)
        return false;
    return true;
}

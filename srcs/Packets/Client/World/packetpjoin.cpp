#include "packetpjoin.h"

PacketPjoin::PacketPjoin(PartyRequestType PartyType, int characterID)
    : BasePacket("pjoin")
{
    partyRequestType = PartyType;
    id = characterID;
    packet.push_back(QString::number(static_cast<int>(partyRequestType)));
    packet.push_back(QString::number(id));
}

bool PacketPjoin::isSendable()
{
    if(id < 0)
        return false;
    if(packet.size() != PACKET_SIZE)
        return false;
    return true;
}

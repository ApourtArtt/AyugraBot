#ifndef PACKETPJOIN_H
#define PACKETPJOIN_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/partyenum.h"

class PacketPjoin : public BasePacket
{
public:
    PacketPjoin(PartyRequestType PartyType, int characterID);
    virtual bool isSendable() override;

private:
    PartyRequestType partyRequestType;
    int id;
    const int PACKET_SIZE = 3;
};

#endif // PACKETPJOIN_H

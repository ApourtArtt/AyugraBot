#ifndef PACKETFINS_H
#define PACKETFINS_H

#include "srcs/Packets/basepacket.h"

class PacketFins : public BasePacket
{
public:
    PacketFins(int characterID);
    virtual bool isSendable() override;

private:
    int id;
    const int PACKET_SIZE = 3;
};

#endif // PACKETFINS_H

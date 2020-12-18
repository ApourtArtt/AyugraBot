#ifndef PACKETBLINS_H
#define PACKETBLINS_H

#include "srcs/Packets/basepacket.h"

class PacketBlins : public BasePacket
{
public:
    PacketBlins(int characterID);
    virtual bool isSendable() override;

private:
    int id;
    const int PACKET_SIZE = 2;
};

#endif // PACKETBLINS_H

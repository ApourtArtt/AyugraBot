#ifndef PACKETPSL_H
#define PACKETPSL_H

#include "srcs/Packets/basepacket.h"

class PacketPsl : public BasePacket
{
public:
    PacketPsl(bool Instant);
    virtual bool isSendable() override;

private:
    bool instant;
    const int PACKET_SIZE = 2;
};

#endif // PACKETPSL_H

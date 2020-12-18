#ifndef PACKETSL_H
#define PACKETSL_H

#include "srcs/Packets/basepacket.h"

class PacketSl : public BasePacket
{
public:
    PacketSl(bool Instant);
    virtual bool isSendable() override;

private:
    bool instant;
    const int PACKET_SIZE = 2;
};

#endif // PACKETSL_H

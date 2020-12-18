#ifndef PACKETPREQ_H
#define PACKETPREQ_H

#include "srcs/Packets/basepacket.h"

class PacketPreq : public BasePacket
{
public:
    PacketPreq();
    virtual bool isSendable() override;

private:
    const int PACKET_SIZE = 1;
};

#endif // PACKETPREQ_H

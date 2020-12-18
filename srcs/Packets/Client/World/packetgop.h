#ifndef PACKETGOP_H
#define PACKETGOP_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/blockingoption.h"

class PacketGop : public BasePacket
{
public:
    PacketGop(BlockingOption option, bool activated);
    virtual bool isSendable() override;

private:
    BlockingOption blockingOption;
    bool isActivated;
    const int PACKET_SIZE = 3;
};

#endif // PACKETGOP_H

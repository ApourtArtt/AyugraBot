#ifndef PACKETLBS_H
#define PACKETLBS_H

#include "srcs/Packets/basepacket.h"

class PacketLbs : public BasePacket
{
public:
    PacketLbs(short Value);
    virtual bool isSendable() override;

private:
    short value;
    const int PACKET_SIZE = 2;
};

#endif // PACKETLBS_H

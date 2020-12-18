#ifndef PACKETC_CLOSE_H
#define PACKETC_CLOSE_H

#include "srcs/Packets/basepacket.h"

class PacketC_close : public BasePacket
{
public:
    PacketC_close(short Value);
    virtual bool isSendable() override;

private:
    short value;
    const int PACKET_SIZE = 2;
};

#endif // PACKETC_CLOSE_H

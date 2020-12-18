#ifndef PACKETPLEAVE_H
#define PACKETPLEAVE_H

#include "srcs/Packets/basepacket.h"

class PacketPleave : public BasePacket
{
public:
    PacketPleave();
    virtual bool isSendable() override;

private:
    const int PACKET_SIZE = 1;
};

#endif // PACKETPLEAVE_H

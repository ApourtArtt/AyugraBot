#ifndef PACKETF_STASH_END_H
#define PACKETF_STASH_END_H

#include "srcs/Packets/basepacket.h"

class PacketF_stash_end : public BasePacket
{
public:
    PacketF_stash_end();
    virtual bool isSendable() override;

private:
    const int PACKET_SIZE = 1;
};

#endif // PACKETF_STASH_END_H

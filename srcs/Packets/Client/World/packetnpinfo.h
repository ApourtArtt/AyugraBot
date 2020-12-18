#ifndef PACKETNPINFO_H
#define PACKETNPINFO_H

#include "srcs/Packets/basepacket.h"

class PacketNpinfo : public BasePacket
{
public:
    PacketNpinfo(short Page);
    virtual bool isSendable() override;

private:
    short page;
    const int PACKET_SIZE = 2;
};

#endif // PACKETNPINFO_H

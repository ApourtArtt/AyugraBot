#ifndef PACKETGLIST_H
#define PACKETGLIST_H

#include "srcs/Packets/basepacket.h"

class PacketGlist : public BasePacket
{
public:
    PacketGlist(short FirstValue, short SecondValue);
    virtual bool isSendable() override;

private:
    short firstValue;
    short secondValue;
    const int PACKET_SIZE = 3;
};

#endif // PACKETGLIST_H

#ifndef PACKETWALK_H
#define PACKETWALK_H

#include "srcs/Packets/basepacket.h"

class PacketWalk : public BasePacket
{
public:
    PacketWalk(int X, int Y, int Check, short Speed);
    virtual bool isSendable() override;

private:
    int x;
    int y;
    int check;
    short speed;
    const int PACKET_SIZE = 5;
};

#endif // PACKETWALK_H

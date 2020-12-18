#ifndef PACKETPTCTL_H
#define PACKETPTCTL_H

#include "srcs/Packets/basepacket.h"

class PacketPtctl : public BasePacket
{
public:
    PacketPtctl(int MapID, int MovingAmount, int EntityID, int X, int Y, short Speed);
    virtual bool isSendable() override;

private:
    int mapID;
    int movingAmount;
    int entityID;
    int x;
    int y;
    short speed;
    const int PACKET_SIZE = 8;
};

#endif // PACKETPTCTL_H

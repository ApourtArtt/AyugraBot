#ifndef PACKETWP_H
#define PACKETWP_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/timespaceenum.h"

class PacketWp : public BasePacket
{
public:
    PacketWp(QStringList Packet);
    short getX();
    short getY();
    int getID();
    TimeSpaceType getType();
    short getLvlMin();
    short getLvlMax();
};

#endif // PACKETWP_H

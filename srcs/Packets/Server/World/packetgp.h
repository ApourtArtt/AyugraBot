#ifndef PACKETGP_H
#define PACKETGP_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/portalenum.h"

class PacketGp : public BasePacket
{
public:
    PacketGp(QStringList Packet);
    short getX();
    short getY();
    int getMapID();
    PortalType getType();
    int getID();
    bool isInvisible();
};

#endif // PACKETGP_H

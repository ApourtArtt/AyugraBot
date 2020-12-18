#ifndef PACKETMV_H
#define PACKETMV_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"

class PacketMv : public BasePacket
{
public:
    PacketMv(QStringList Packet);
    EntityType getEntityType();
    int getID();
    short getX();
    short getY();
    short getSpeed();
};

#endif // PACKETMV_H

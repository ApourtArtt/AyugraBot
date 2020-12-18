#ifndef PACKETCOND_H
#define PACKETCOND_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"

class PacketCond : public BasePacket
{
public:
    PacketCond(QStringList Packet);
    EntityType getEntityType();
    int getID();
    bool isStunned();
    bool isRooted();
    short getSpeed();
};

#endif // PACKETCOND_H

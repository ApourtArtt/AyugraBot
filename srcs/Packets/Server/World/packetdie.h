#ifndef PACKETDIE_H
#define PACKETDIE_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"

class PacketDie : public BasePacket
{
public:
    PacketDie(QStringList Packet);
    EntityType getEntityType();
    int getID();
    // ???
    // ???
};

#endif // PACKETDIE_H

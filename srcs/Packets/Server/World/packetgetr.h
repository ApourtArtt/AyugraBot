#ifndef PACKETGETR_H
#define PACKETGETR_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"

// There is two type of Get packet : R(ecieved) and S(ent)

class PacketGetR : public BasePacket
{
public:
    PacketGetR(QStringList Packet);
    EntityType getEntityType();
    int getEntityID();
    int getDropID();
    // ???
};

#endif // PACKETGETR_H

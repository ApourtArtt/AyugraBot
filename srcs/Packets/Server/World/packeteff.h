#ifndef PACKETEFF_H
#define PACKETEFF_H

#include "srcs/Enum/entityenum.h"
#include "srcs/Packets/basepacket.h"

class PacketEff : public BasePacket
{
public:
    PacketEff(QStringList Packet);
    EntityType getEntityType();
    int getEntityID();
    int getEmoteID();
};

#endif // PACKETEFF_H

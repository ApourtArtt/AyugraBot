#ifndef PACKETRESTR_H
#define PACKETRESTR_H

#include "srcs/Enum/entityenum.h"
#include "srcs/Packets/basepacket.h"

class PacketRestR : public BasePacket
{
public:
    PacketRestR(QStringList Packet);
    EntityType getEntityType();
    int getEntityID();
    bool isResting();
};

#endif // PACKETRESTR_H

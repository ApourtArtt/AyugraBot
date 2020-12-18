#ifndef PACKETOUT_H
#define PACKETOUT_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"

class PacketOut : public BasePacket
{
public:
    PacketOut(QStringList Packet);
    EntityType getEntityType();
    int getID();
};

#endif // PACKETOUT_H

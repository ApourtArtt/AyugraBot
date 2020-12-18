#ifndef PACKETREVIVE_H
#define PACKETREVIVE_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"

class PacketRevive : public BasePacket
{
public: // revive 1 1075194 0
    PacketRevive(QStringList Packet);
    EntityType getEntityType() const;
    int getEntityID() const;
    // ??
};

#endif // PACKETREVIVE_H

#ifndef PACKETGET_H
#define PACKETGET_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"

class PacketGet : public BasePacket
{
public:
    PacketGet(EntityType EntityType, int DropperID, int DropID);
    virtual bool isSendable() override;

private:
    EntityType entityType;
    int dropperID;
    int dropID;
    const int PACKET_SIZE = 4;
};

#endif // PACKETGET_H

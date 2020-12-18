#ifndef PACKETGURI_H
#define PACKETGURI_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"

class PacketGuri : public BasePacket
{
public:
    PacketGuri(int Type);
    PacketGuri(int Type, EntityType _EntityType, int EntityID, int Timer, int Argument);
    virtual bool isSendable() override;

private:
    int type;
    EntityType entityType;
    int entityID;
    int timer;
    int argument;
};

#endif // PACKETGURI_H

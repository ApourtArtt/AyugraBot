#ifndef PACKETSUCTL_H
#define PACKETSUCTL_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"
// suctl 1 1 609445 3 2089
class PacketSuctl : public BasePacket
{
public:
    PacketSuctl(int MapID, int AttackingAmount, int EntityID, EntityType EntityType, int TargetID);
    virtual bool isSendable() override;

private:
    int mapID;
    int attackingAmount;
    int entityID;
    EntityType entityType;
    int targetID;
    const int PACKET_SIZE = 6;
};

#endif // PACKETSUCTL_H

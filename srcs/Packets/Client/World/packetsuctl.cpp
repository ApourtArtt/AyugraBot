#include "packetsuctl.h"

PacketSuctl::PacketSuctl(int MapID, int AttackingAmount, int EntityID, EntityType EntityType, int TargetID)
    : BasePacket("suctl")
{
    mapID = MapID;
    attackingAmount = AttackingAmount;
    entityID = EntityID;
    entityType = EntityType;
    targetID = TargetID;
    packet.push_back(QString::number(mapID));
    packet.push_back(QString::number(attackingAmount));
    packet.push_back(QString::number(entityID));
    packet.push_back(QString::number(static_cast<int>(entityType)));
    packet.push_back(QString::number(targetID));
}

bool PacketSuctl::isSendable()
{
    if(mapID < 0)
        return false;
    if(attackingAmount < 1 || attackingAmount > 2)
        return false;
    if(entityID < 0)
        return false;
    if(targetID < 0)
        return false;
    if(packet.size() != PACKET_SIZE)
        return false;
    return true;
}

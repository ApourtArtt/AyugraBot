#include "packetget.h"

PacketGet::PacketGet(EntityType EntityType, int DropperID, int DropID)
    : BasePacket("get")
{
    entityType = EntityType;
    dropperID = DropperID;
    dropID = DropID;
    packet.push_back(QString::number(static_cast<int>(entityType)));
    packet.push_back(QString::number(dropperID));
    packet.push_back(QString::number(dropID));
}

bool PacketGet::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    if(dropID < 0)
        return false;
    if(dropperID < 0)
        return false;
    return true;
}

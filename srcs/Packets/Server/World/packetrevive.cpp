#include "packetrevive.h"

PacketRevive::PacketRevive(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketRevive::getEntityType() const
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketRevive::getEntityID() const
{
    return packet[2].toInt();
}

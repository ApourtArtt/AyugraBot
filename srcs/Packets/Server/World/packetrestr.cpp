#include "packetrestr.h"

PacketRestR::PacketRestR(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketRestR::getEntityType()
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketRestR::getEntityID()
{
    return packet[2].toInt();
}

bool PacketRestR::isResting()
{
    return packet[3].toInt();
}

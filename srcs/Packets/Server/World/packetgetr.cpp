#include "packetgetr.h"

PacketGetR::PacketGetR(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketGetR::getEntityType()
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketGetR::getEntityID()
{
    return packet[2].toInt();
}

int PacketGetR::getDropID()
{
    return packet[3].toInt();
}

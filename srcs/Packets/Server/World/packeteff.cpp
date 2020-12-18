#include "packeteff.h"

PacketEff::PacketEff(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketEff::getEntityType()
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketEff::getEntityID()
{
    return packet[2].toInt();
}

int PacketEff::getEmoteID()
{
    return packet[3].toInt();
}

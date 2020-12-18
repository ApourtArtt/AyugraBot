#include "packetout.h"

PacketOut::PacketOut(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketOut::getEntityType()
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketOut::getID()
{
    return packet[2].toInt();
}

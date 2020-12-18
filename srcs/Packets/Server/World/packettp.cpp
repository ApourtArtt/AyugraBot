#include "packettp.h"

PacketTp::PacketTp(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketTp::getEntityType() const
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketTp::getEntityID() const
{
    return packet[2].toInt();
}

int PacketTp::getX() const
{
    return packet[3].toInt();
}

int PacketTp::getY() const
{
    return packet[4].toInt();
}

#include "packetivn.h"

PacketIvn::PacketIvn(QStringList Packet)
    : BasePacket(Packet)
{

}

InventoryType PacketIvn::getInventoryType()
{
    return static_cast<InventoryType>(packet[1].toInt());
}

PacketInvSub PacketIvn::getInfo()
{
    return PacketInvSub(packet[2]);
}

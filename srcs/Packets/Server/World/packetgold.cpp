#include "packetgold.h"

PacketGold::PacketGold(QStringList Packet)
    : BasePacket(Packet)
{

}

int PacketGold::getGoldInventory()
{
    return packet[1].toInt();
}

int PacketGold::getGoldBank()
{
    return packet[2].toInt();
}

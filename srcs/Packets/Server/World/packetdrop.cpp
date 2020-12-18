#include "packetdrop.h"

PacketDrop::PacketDrop(QStringList Packet)
    : BasePacket(Packet)
{

}

QString PacketDrop::getName()
{
    return packet[1];
}

int PacketDrop::getID()
{
    return packet[2].toInt();
}

short PacketDrop::getX()
{
    return packet[3].toShort();
}

short PacketDrop::getY()
{
    return packet[4].toShort();
}

short PacketDrop::getQuantity()
{
    return packet[5].toShort();
}

bool PacketDrop::isQuest()
{
    return packet[6].toInt();
}

int PacketDrop::getOwnerID()
{
    return packet[7].toInt();
}

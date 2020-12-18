#include "packetat.h"

PacketAt::PacketAt(QStringList Packet)
    : BasePacket(Packet)
{

}

int PacketAt::getCharacterID()
{
    return packet[1].toInt();
}

int PacketAt::getMapID()
{
    return packet[2].toInt();
}

int PacketAt::getPosX()
{
    return packet[3].toInt();
}

int PacketAt::getPosY()
{
    return packet[4].toInt();
}

short PacketAt::getDirection()
{
    return packet[5].toShort();
}






int PacketAt::getMusicID()
{
    return packet[7].toInt();
}


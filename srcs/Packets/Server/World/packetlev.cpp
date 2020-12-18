#include "packetlev.h"

PacketLev::PacketLev(QStringList Packet)
    : BasePacket(Packet)
{

}

short PacketLev::getLevel()
{
    return packet[1].toShort();
}

long PacketLev::getLevelXP()
{
    return packet[2].toLong();
}

short PacketLev::getLevelJob()
{
    return packet[3].toShort();
}

long PacketLev::getLevelJobXP()
{
    return packet[4].toLong();
}

long PacketLev::getLevelMaxXP()
{
    return packet[5].toLong();
}

long PacketLev::getLevelJobMaxXP()
{
    return packet[6].toLong();
}

int PacketLev::getReputation()
{
    return packet[7].toInt();
}

int PacketLev::getSkillCP()
{
    return packet[8].toInt();
}

long PacketLev::getLevelHeroXP()
{
    return packet[9].toLong();
}

short PacketLev::getLevelHero()
{
    return packet[10].toShort();
}

long PacketLev::getLevelHeroMaxXP()
{
    return packet[11].toLong();
}

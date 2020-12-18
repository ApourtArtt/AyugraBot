#include "packetclist.h"

PacketClist::PacketClist(QStringList Packet)
    : BasePacket(Packet)
{

}

short PacketClist::getSlot()
{
    return packet[1].toShort();
}

QString PacketClist::getPseudonym()
{
    return packet[2];
}

Gender PacketClist::getSexe()
{
    return static_cast<Gender>(packet[4].toInt());
}

HairStyle PacketClist::getHairStyle()
{
    return static_cast<HairStyle>(packet[5].toInt());
}

short PacketClist::getHairColor()
{
    return packet[6].toShort();
}

Class PacketClist::getClass()
{
    return static_cast<Class>(packet[8].toInt());
}

short PacketClist::getLevel()
{
    return packet[9].toShort();
}

short PacketClist::getLevelHero()
{
    return packet[10].toShort();
}

QString PacketClist::getWornStuff()
{
    return packet[11];
}

short PacketClist::getLevelJob()
{
    return packet[12].toShort();
}

short PacketClist::getQuestAct()
{
    return packet[13].toShort();
}

short PacketClist::getQuestChapter()
{
    return packet[14].toShort();
}

QString PacketClist::getPetsSkin()
{
    return packet[15];
}

bool PacketClist::shouldBeRenamed()
{
    return packet[17].toInt();
}

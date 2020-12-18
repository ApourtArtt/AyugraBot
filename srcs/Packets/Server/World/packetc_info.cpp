#include "packetc_info.h"

PacketC_info::PacketC_info(QStringList Packet)
    : BasePacket(Packet)
{

}

QString PacketC_info::getPseudonym()
{
    return packet[1];
}

int PacketC_info::getGroupID()
{
    return packet[3].toInt();
}

int PacketC_info::getFamilyID()
{
    return packet[4].toInt();
}

QString PacketC_info::getFamilyNameRole()
{
    return packet[5];
}

int PacketC_info::getCharacterID()
{
    return packet[6].toInt();
}

Authority PacketC_info::getAuthority()
{
    return static_cast<Authority>(packet[7].toInt());
}

Gender PacketC_info::getGender()
{
    return static_cast<Gender>(packet[8].toInt());
}

HairStyle PacketC_info::getHairStyle()
{
    return static_cast<HairStyle>(packet[9].toInt());
}

short PacketC_info::getHairColor()
{
    return packet[10].toShort();
}

Class  PacketC_info::getClass()
{
    return static_cast<Class>(packet[11].toInt());
}

ReputationIcon PacketC_info::getReputationIcon()
{
    return static_cast<ReputationIcon>(packet[12].toInt());
}

short PacketC_info::getAdmiration()
{
    return packet[13].toShort();
}

short PacketC_info::getMorph()
{
    return packet[14].toShort();
}

bool PacketC_info::isInvisible()
{
    return packet[15].toInt();
}

short PacketC_info::getFamilyLevel()
{
    return packet[16].toShort();
}

short PacketC_info::getSpUpgrade()
{
    return packet[17].toShort();
}

bool PacketC_info::isArenaWinner()
{
    return packet[18].toInt();
}

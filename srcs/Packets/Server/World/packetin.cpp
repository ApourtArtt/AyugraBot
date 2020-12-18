#include "packetin.h"
#include <QDebug>

BasePacketIn::BasePacketIn(QStringList Packet)
    : BasePacket(Packet)
{
    entityType = static_cast<EntityType>(packet[1].toInt());
}

QString BasePacketIn::getName()
{
    return packet[2];
}

int BasePacketIn::getID()
{
    if(entityType == EntityType::PLAYER)
        return packet[4].toInt();
    return packet[3].toInt();
}

short BasePacketIn::getX()
{
    if(entityType == EntityType::PLAYER)
        return packet[5].toShort();
    return packet[4].toShort();
}

short BasePacketIn::getY()
{
    if(entityType == EntityType::PLAYER)
        return packet[6].toShort();
    return packet[5].toShort();
}

short BasePacketIn::getDir()
{
    if(entityType == EntityType::PLAYER)
        return packet[7].toShort();
    return entityType == EntityType::DROP ? 2 : packet[6].toShort();
}



PacketIn1::PacketIn1(QStringList Packet)
    : BasePacketIn(Packet)
{
    //packet.removeAt(3);
}

Authority PacketIn1::getAuthority()
{
    return static_cast<Authority>(packet[8].toShort());
}

Gender PacketIn1::getGender()
{
    return static_cast<Gender>(packet[9].toShort());
}

HairStyle PacketIn1::getHairStyle()
{
    return static_cast<HairStyle>(packet[10].toInt());
}

short PacketIn1::getHairColor()
{
    return packet[11].toShort();
}

Class PacketIn1::getClass()
{
    return static_cast<Class>(packet[12].toInt());
}

QString PacketIn1::getWornStuff()
{
    return packet[13];
}

short PacketIn1::getPercentHP()
{
    return packet[14].toShort();
}

short PacketIn1::getPercentMP()
{
    return packet[15].toShort();
}

bool PacketIn1::isSitting()
{
    return packet[16].toInt();
}

int PacketIn1::getGroupID()
{
    return packet[17].toInt();
}
// 18 = fairyposition
FairyElement PacketIn1::getFairyElement()
{
    return static_cast<FairyElement>(packet[19].toInt());
}
/*
short PacketIn1::getFairyPercent()
{
    return packet[19].toShort();
}*/

// 20 ?
short PacketIn1::getFairyMorph()
{
    return packet[21].toShort();
}

// 22 : pop animation (spiders)

short PacketIn1::getSkin()
{
    return packet[23].toShort();
}

QString PacketIn1::getFirstHandUpgrade()
{
    QString tmp = packet[24];
    tmp.insert(tmp.size() - 1, '+');
    return tmp;
}

QString PacketIn1::getArmorUpgrade()
{
    QString tmp = packet[25];
    tmp.insert(tmp.size() - 1, '+');
    return tmp;
}

int PacketIn1::getFamilyID()
{
    return packet[26].toInt();
    // has been changed
    // function will still work
    // but missing familly role
}

QString PacketIn1::getFamilyName()
{
    return packet[27];
}

ReputationIcon PacketIn1::getReputationIcon()
{
    return static_cast<ReputationIcon>(packet[28].toInt());
}

bool PacketIn1::isInvisible()
{
    return packet[29].toInt();
}

short PacketIn1::getSPUpgrade()
{
    return packet[30].toShort();
}

Faction PacketIn1::getFaction()
{
    return static_cast<Faction>(packet[31].toInt());
}

Wings PacketIn1::getWingsSkin()
{
    return static_cast<Wings>(packet[32].toInt());
}

short PacketIn1::getLevel()
{
    return packet[33].toShort();
}

short PacketIn1::getFamilyLevel()
{
    return packet[34].toShort();
}

QString PacketIn1::getFamilyIcon()
{
    return packet[35];
}

bool PacketIn1::isArenaWinner()
{
    return packet[36].toInt();
}

short PacketIn1::getAdmiration()
{
    return packet[37].toShort();
}

short PacketIn1::getSize()
{
    return packet[38].toShort();
}

short PacketIn1::getLevelHero()
{
    return packet[39].toShort();
}

short PacketIn1::getTitle()
{
    return packet[40].toShort();
}



PacketIn23::PacketIn23(QStringList Packet)
    : BasePacketIn(Packet)
{

}

short PacketIn23::getPercentHP()
{
    return packet[7].toShort();
}

short PacketIn23::getPercentMP()
{
    return packet[8].toShort();
}

short PacketIn23::getDialog()
{
    return packet[9].toShort();
}

short PacketIn23::getFaction()
{
    return packet[10].toShort();
}

short PacketIn23::getGroupEffect()
{
    return packet[11].toShort();
}

int PacketIn23::getOwnerID()
{
    return packet[12].toInt();
}

SpawnEffect PacketIn23::getSpawnEffect()
{
    return static_cast<SpawnEffect>(packet[13].toShort());
}

bool PacketIn23::isSitting()
{
    return packet[14].toInt();
}

short PacketIn23::getMorph()
{
    return packet[15].toShort();
}

QString PacketIn23::getCustomName()
{
    return packet[16];
}

bool PacketIn23::isPartner()
{
    if(packet[17] == "1")
        return true;
    return false;
}

short PacketIn23::getSkill1()
{
    return packet[20].toShort();
}

short PacketIn23::getSkill2()
{
    return packet[21].toShort();
}

short PacketIn23::getSkill3()
{
    return packet[22].toShort();
}

short PacketIn23::getSkill1Rank()
{
    return packet[23].toShort();
}

short PacketIn23::getSkill2Rank()
{
    return packet[24].toShort();
}

short PacketIn23::getSkill3Rank()
{
    return packet[25].toShort();
}

bool PacketIn23::isInvisible()
{
    return packet[26].toInt();
}



PacketIn9::PacketIn9(QStringList Packet)
    : BasePacketIn(Packet)
{

}

short PacketIn9::getQuantity()
{
    return packet[6].toShort();
}

bool PacketIn9::isQuest()
{
    return packet[7].toUInt();
}

int PacketIn9::getOwnerID()
{
    return packet[9].toInt();
}

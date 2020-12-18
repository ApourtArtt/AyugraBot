#ifndef PACKETIN_H
#define PACKETIN_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"
#include "srcs/Enum/characterenum.h"
#include "srcs/Enum/fairyenum.h"
#include "srcs/Enum/reputationenum.h"
#include "srcs/Enum/factionenum.h"
#include "srcs/Enum/wingsenum.h"

/*
Some changes have been made in game
The packet needs a rework

*/

class BasePacketIn : public BasePacket
{
public:
    BasePacketIn(QStringList Packet);
    EntityType getEntityType(){return entityType;}
    QString getName();
    int getID();
    short getX();
    short getY();
    short getDir();

protected:
    EntityType entityType;
};



class PacketIn1 : public BasePacketIn
{
public:
    PacketIn1(QStringList Packet);
    Authority getAuthority();
    Gender getGender();
    HairStyle getHairStyle();
    short getHairColor();
    Class getClass();
    QString getWornStuff();
    short getPercentHP();
    short getPercentMP();
    bool isSitting();
    int getGroupID();
    FairyElement getFairyElement();
    //short getFairyPercent();
    // ???
    short getFairyMorph();
    // ???
    short getSkin();
    QString getFirstHandUpgrade();
    QString getArmorUpgrade();
    int getFamilyID();
    QString getFamilyName();
    ReputationIcon getReputationIcon();
    bool isInvisible();
    short getSPUpgrade();
    Faction getFaction();
    Wings getWingsSkin();
    short getLevel();
    short getFamilyLevel();
    QString getFamilyIcon();
    bool isArenaWinner();
    short getAdmiration();
    short getSize();
    short getLevelHero();
    short getTitle();
};



class PacketIn23 : public BasePacketIn
{
public:
    PacketIn23(QStringList Packet);
    short getPercentHP();
    short getPercentMP();
    short getDialog();
    short getFaction();
    short getGroupEffect();
    int getOwnerID();
    SpawnEffect getSpawnEffect();
    bool isSitting();
    short getMorph();
    QString getCustomName();
    bool isPartner();
    // ???
    // ???
    short getSkill1();
    short getSkill2();
    short getSkill3();
    short getSkill1Rank();
    short getSkill2Rank();
    short getSkill3Rank();
    bool isInvisible();
};



class PacketIn9 : public BasePacketIn
{
public:
    PacketIn9(QStringList Packet);
    short getQuantity();
    bool isQuest();
    // ???
    int getOwnerID();
};

#endif // PACKETIN_H

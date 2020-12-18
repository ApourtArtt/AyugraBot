#ifndef PLAYER_H
#define PLAYER_H

#include "srcs/Enum/characterenum.h"
#include "srcs/Enum/fairyenum.h"
#include "srcs/Enum/reputationenum.h"
#include "srcs/Enum/factionenum.h"
#include "srcs/Enum/wingsenum.h"
#include "srcs/GameObjects/Entity/baseentity.h"
#include "srcs/Packets/Server/World/packetin.h"
#include "srcs/Packets/Server/World/packetsu.h"
#include "srcs/GameObjects/Properties/shop.h"

class Player : public BaseEntity
{
public:
    Player(){}
    Player(PacketIn1 Packet);

    void handleShopPacket(PacketShop Packet);
    void handleSuPacket(PacketSu Packet);

    Authority getAuthority() const;
    Gender getGender() const;
    HairStyle getHairStyle() const;
    short getHairColor() const;
    Class getClass() const;
    QString getWornStuff() const;
    short getPercentHP() const;
    short getPercentMP() const;
    bool isSitting() const;
    int getGroupID() const;
    FairyElement getFairyElement() const;
    short getFairyPercent() const;
    // ???
    short getFairyMorph() const;
    // ???
    short getSkin() const;
    QString getFirstHandUpgrade() const;
    QString getArmorUpgrade() const;
    int getFamilyID() const;
    QString getFamilyName() const;
    ReputationIcon getReputationIcon() const;
    bool isInvisible() const;
    short getSPUpgrade() const;
    Faction getFaction() const;
    Wings getWingsSkin() const;
    short getLevel() const;
    short getFamilyLevel() const;
    QString getFamilyIcon() const;
    bool isArenaWinner() const;
    short getAdmiration() const;
    short getSize() const;
    short getLevelHero() const;
    short getTitle() const;
    int getActualHP() const;
    int getActualMP() const;
    int getMaximumHP() const;
    int getMaximumMP() const;
    bool isDead() const;
    Shop getShopProperties() const;

private:
    Authority authority;
    Gender gender;
    HairStyle hairStyle;
    short hairColor;
    Class playerClass;
    QString wornStuff; // Move to Equipment class (create it)
    short percentHP; // Already in Statistics, remove it
    short percentMP; // Already in Statistics, remove it
    bool rest;
    int groupID;
    FairyElement fairyElement; // Move to Equipment class (create it)
    short fairyPercent; // Move to Equipment class (create it)
    // ???
    short fairyMorph; // Move to Equipment class (create it)
    // ???
    short skin;
    QString firstHandUpgrade; // Move to Equipment class (create it)
    QString armorUpgrade; // Move to Equipment class (create it)
    int familyID; // Move to Family class (create it)
    QString familyName; // Move to Family class (create it)
    ReputationIcon reputationIcon; // Already in Reputation
    bool invisible;
    short spUpgrade; // Move to Equipment class
    Faction faction;
    Wings wingsSkin; // Move to equipment class
    short level; // Already in Level
    short familyLevel; // Move to Family
    QString familyIcon; // Same
    bool arenaWinner;
    short admiration;
    short size;
    short levelHero; // Already in Level
    short title;
    int hpActu; // Stat
    int mpActu; // Stat
    int hpMax; // Stat
    int mpMax; // Stat
    bool dead; // Should be in stat (isn't already)
    Shop shop;
};

#endif // PLAYER_H

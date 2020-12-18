#include "player.h"

Player::Player(PacketIn1 Packet)
    : BaseEntity(Packet)
{
    authority = Packet.getAuthority();
    gender = Packet.getGender();
    hairStyle = Packet.getHairStyle();
    hairColor = Packet.getHairColor();
    playerClass = Packet.getClass();
    wornStuff = Packet.getWornStuff();
    percentHP = Packet.getPercentHP();
    percentMP = Packet.getPercentMP();
    rest = Packet.isSitting();
    groupID = Packet.getGroupID();
    fairyElement = Packet.getFairyElement();
    //fairyPercent = Packet.getFairyPercent();
    fairyMorph = Packet.getFairyMorph();
    skin = Packet.getSkin();
    firstHandUpgrade = Packet.getFirstHandUpgrade();
    armorUpgrade = Packet.getArmorUpgrade();
    familyID = Packet.getFamilyID();
    familyName = Packet.getFamilyName();
    reputationIcon = Packet.getReputationIcon();
    invisible = Packet.isInvisible();
    spUpgrade = Packet.getSPUpgrade();
    faction = Packet.getFaction();
    wingsSkin = Packet.getWingsSkin();
    level = Packet.getLevel();
    familyLevel = Packet.getFamilyLevel();
    familyIcon = Packet.getFamilyIcon();
    arenaWinner = Packet.isArenaWinner();
    admiration = Packet.getAdmiration();
    size = Packet.getSize();
    levelHero = Packet.getLevelHero();
    title = Packet.getTitle();
    hpActu = -1;
    mpActu = -1;
    hpMax = -1;
    mpMax = -1;
}

void Player::handleShopPacket(PacketShop Packet)
{
    shop.handleShopPacket(Packet);
}

void Player::handleSuPacket(PacketSu Packet)
{
    if(hpActu != -1)
        hpActu -= Packet.getDamageDealt();
    percentHP = Packet.getTargetPercentHP();
    dead = Packet.isTargetStillAlive();
}

Authority Player::getAuthority() const
{
    return authority;
}

Gender Player::getGender() const
{
    return gender;
}

HairStyle Player::getHairStyle() const
{
    return hairStyle;
}

short Player::getHairColor() const
{
    return hairColor;
}

Class Player::getClass() const
{
    return playerClass;
}

QString Player::getWornStuff() const
{
    return wornStuff;
}

short Player::getPercentHP() const
{
    return (hpActu == -1 ? percentHP : static_cast<short>(hpActu / hpMax));
}

short Player::getPercentMP() const
{
    return (mpActu == -1 ? percentMP : static_cast<short>(mpActu / mpMax));
}

bool Player::isSitting() const
{
    return rest;
}

int Player::getGroupID() const
{
    return groupID;
}

FairyElement Player::getFairyElement() const
{
    return fairyElement;
}

short Player::getFairyPercent() const
{
    return fairyPercent;
}

short Player::getFairyMorph() const
{
    return fairyMorph;
}

short Player::getSkin() const
{
    return skin;
}

QString Player::getFirstHandUpgrade() const
{
    return firstHandUpgrade;
}

QString Player::getArmorUpgrade() const
{
    return armorUpgrade;
}

int Player::getFamilyID() const
{
    return familyID;
}

QString Player::getFamilyName() const
{
    return familyName;
}

ReputationIcon Player::getReputationIcon() const
{
    return reputationIcon;
}

bool Player::isInvisible() const
{
    return invisible;
}

short Player::getSPUpgrade() const
{
    return spUpgrade;
}

Faction Player::getFaction() const
{
    return faction;
}

Wings Player::getWingsSkin() const
{
    return wingsSkin;
}

short Player::getLevel() const
{
    return level;
}

short Player::getFamilyLevel() const
{
    return familyLevel;
}

QString Player::getFamilyIcon() const
{
    return familyIcon;
}

bool Player::isArenaWinner() const
{
    return arenaWinner;
}

short Player::getAdmiration() const
{
    return admiration;
}

short Player::getSize() const
{
    return size;
}

short Player::getLevelHero() const
{
    return levelHero;
}

short Player::getTitle() const
{
    return title;
}

int Player::getActualHP() const
{
    return hpActu;
}

int Player::getActualMP() const
{
    return mpActu;
}

int Player::getMaximumHP() const
{
    return hpMax;
}

int Player::getMaximumMP() const
{
    return mpMax;
}

bool Player::isDead() const
{
    return dead;
}

Shop Player::getShopProperties() const
{
    return shop;
}

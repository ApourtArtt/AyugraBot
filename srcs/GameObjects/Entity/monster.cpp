#include "monster.h"

Monster::Monster(PacketIn23 Packet)
    : BaseEntity(Packet)
{
    percentHP = Packet.getPercentHP();
    percentMP = Packet.getPercentMP();
    dialog = Packet.getDialog();
    faction = Packet.getFaction();
    groupEffect = Packet.getGroupEffect();
    ownerID = Packet.getOwnerID();
    spawnEffect = Packet.getSpawnEffect();
    rest = Packet.isSitting();
    morph = Packet.getMorph();
    customName = Packet.getCustomName();
    skill1 = Packet.getSkill1();
    skill2 = Packet.getSkill2();
    skill3 = Packet.getSkill3();
    skill1Rank = Packet.getSkill1Rank();
    skill2Rank = Packet.getSkill2Rank();
    skill3Rank = Packet.getSkill3Rank();
    invisible = Packet.isInvisible();
    hpActu = -1;
    mpActu = -1;
    hpMax = -1;
    mpMax = -1;
}

void Monster::handleSuPacket(PacketSu Packet)
{
    if(hpActu != -1)
        hpActu -= Packet.getDamageDealt();
    percentHP = Packet.getTargetPercentHP();
}

short Monster::getPercentHP() const
{
    return (hpActu == -1 ? percentHP : static_cast<short>(hpActu / hpMax));
}

short Monster::getPercentMP() const
{
    return (mpActu == -1 ? percentMP : static_cast<short>(mpActu / mpMax));
}

short Monster::getDialog() const
{
    return dialog;
}

short Monster::getFaction() const
{
    return faction;
}

short Monster::getGroupEffect() const
{
    return groupEffect;
}

int Monster::getOwnerID() const
{
    return ownerID;
}

SpawnEffect Monster::getSpawnEffect() const
{
    return spawnEffect;
}

bool Monster::isSitting() const
{
    return rest;
}

short Monster::getMorph() const
{
    return morph;
}

QString Monster::getCustomName() const
{
    return customName == "-" ? "" : customName;
}

short Monster::getSkill1() const
{
    return skill1;
}

short Monster::getSkill2() const
{
    return skill2;
}

short Monster::getSkill3() const
{
    return skill3;
}

short Monster::getSkill1Rank() const
{
    return skill1Rank;
}

short Monster::getSkill2Rank() const
{
    return skill2Rank;
}

short Monster::getSkill3Rank() const
{
    return skill3Rank;
}

bool Monster::isInvisible() const
{
    return invisible;
}

int Monster::getActualHP() const
{
    return hpActu;
}

int Monster::getActualMP() const
{
    return mpActu;
}

int Monster::getMaximumHP() const
{
    return hpMax;
}

int Monster::getMaximumMP() const
{
    return mpMax;
}

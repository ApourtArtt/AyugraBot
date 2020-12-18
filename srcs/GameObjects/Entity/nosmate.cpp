#include "nosmate.h"

Nosmate::Nosmate(PacketIn23 Packet)
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
    dead = false;
}

void Nosmate::handleSuPacket(PacketSu Packet)
{
    if(hpActu != -1)
        hpActu -= Packet.getDamageDealt();
    percentHP = Packet.getTargetPercentHP();
    dead = Packet.isTargetStillAlive();
}

short Nosmate::getPercentHP() const
{
    return (hpActu == -1 ? percentHP : static_cast<short>(hpActu / hpMax));
}

short Nosmate::getPercentMP() const
{
    return (mpActu == -1 ? percentMP : static_cast<short>(mpActu / mpMax));
}

short Nosmate::getDialog() const
{
    return dialog;
}

short Nosmate::getFaction() const
{
    return faction;
}

short Nosmate::getGroupEffect() const
{
    return groupEffect;
}

int Nosmate::getOwnerID() const
{
    return ownerID;
}

SpawnEffect Nosmate::getSpawnEffect() const
{
    return spawnEffect;
}

bool Nosmate::isSitting() const
{
    return rest;
}

short Nosmate::getMorph() const
{
    return morph;
}

QString Nosmate::getCustomName() const
{
    return customName == "-" ? "" : customName;
}

short Nosmate::getSkill1() const
{
    return skill1;
}

short Nosmate::getSkill2() const
{
    return skill2;
}

short Nosmate::getSkill3() const
{
    return skill3;
}

short Nosmate::getSkill1Rank() const
{
    return skill1Rank;
}

short Nosmate::getSkill2Rank() const
{
    return skill2Rank;
}

short Nosmate::getSkill3Rank() const
{
    return skill3Rank;
}

bool Nosmate::isInvisible() const
{
    return invisible;
}

int Nosmate::getActualHP() const
{
    return hpActu;
}

int Nosmate::getActualMP() const
{
    return mpActu;
}

int Nosmate::getMaximumHP() const
{
    return hpMax;
}

int Nosmate::getMaximumMP() const
{
    return mpMax;
}

bool Nosmate::isDead() const
{
    return dead;
}

QString Nosmate::getImageFile(int morph)
{
    return QString::number(8000+morph) + ".png";
}

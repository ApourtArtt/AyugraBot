#include "npc.h"

NPC::NPC(PacketIn23 Packet)
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

void NPC::handleShopPacket(PacketShop Packet)
{
    shop.handleShopPacket(Packet);
}

void NPC::handleSuPacket(PacketSu Packet)
{
    if(hpActu != -1)
        hpActu -= Packet.getDamageDealt();
    percentHP = Packet.getTargetPercentHP();
    dead = Packet.isTargetStillAlive();
}

short NPC::getPercentHP() const
{
    return (hpActu == -1 ? percentHP : static_cast<short>(hpActu / hpMax));
}

short NPC::getPercentMP() const
{
    return (mpActu == -1 ? percentMP : static_cast<short>(mpActu / mpMax));
}

short NPC::getDialog() const
{
    return dialog;
}

short NPC::getFaction() const
{
    return faction;
}

short NPC::getGroupEffect() const
{
    return groupEffect;
}

int NPC::getOwnerID() const
{
    return ownerID;
}

SpawnEffect NPC::getSpawnEffect() const
{
    return spawnEffect;
}

bool NPC::isSitting() const
{
    return rest;
}

short NPC::getMorph() const
{
    return morph;
}

QString NPC::getCustomName() const
{
    return customName == "-" ? "" : customName;
}

short NPC::getSkill1() const
{
    return skill1;
}

short NPC::getSkill2() const
{
    return skill2;
}

short NPC::getSkill3() const
{
    return skill3;
}

short NPC::getSkill1Rank() const
{
    return skill1Rank;
}

short NPC::getSkill2Rank() const
{
    return skill2Rank;
}

short NPC::getSkill3Rank() const
{
    return skill3Rank;
}

bool NPC::isInvisible() const
{
    return invisible;
}

int NPC::getActualHP() const
{
    return hpActu;
}

int NPC::getActualMP() const
{
    return mpActu;
}

int NPC::getMaximumHP() const
{
    return hpMax;
}

int NPC::getMaximumMP() const
{
    return mpMax;
}

bool NPC::isDead() const
{
    return dead;
}

Shop NPC::getShopProperties() const
{
    return shop;
}

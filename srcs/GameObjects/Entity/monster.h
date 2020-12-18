#ifndef MONSTER_H
#define MONSTER_H

#include "srcs/GameObjects/Entity/baseentity.h"
#include "srcs/Packets/Server/World/packetin.h"
#include "srcs/Packets/Server/World/packetsu.h"

class Monster : public BaseEntity
{
public:
    Monster(){}
    Monster(PacketIn23 Packet);

    void handleSuPacket(PacketSu Packet);

    short getPercentHP() const;
    short getPercentMP() const;
    short getDialog() const;
    short getFaction() const;
    short getGroupEffect() const;
    int getOwnerID() const;
    SpawnEffect getSpawnEffect() const;
    bool isSitting() const;
    short getMorph() const;
    QString getCustomName() const;
    short getSkill1() const;
    short getSkill2() const;
    short getSkill3() const;
    short getSkill1Rank() const;
    short getSkill2Rank() const;
    short getSkill3Rank() const;
    bool isInvisible() const;
    int getActualHP() const;
    int getActualMP() const;
    int getMaximumHP() const;
    int getMaximumMP() const;

private:
    short percentHP;
    short percentMP;
    short dialog;
    short faction;
    short groupEffect;
    int ownerID;
    SpawnEffect spawnEffect;
    bool rest;
    short morph;
    QString customName;
    short skill1;
    short skill2;
    short skill3;
    short skill1Rank;
    short skill2Rank;
    short skill3Rank;
    bool invisible;
    int hpActu;
    int mpActu;
    int hpMax;
    int mpMax;
};

#endif // MONSTER_H

#ifndef PACKETSU_H
#define PACKETSU_H

#include "srcs/Enum/attackenum.h"
#include "srcs/Enum/entityenum.h"
#include "srcs/Packets/basepacket.h"

class PacketSu : public BasePacket
{
public:
    PacketSu(QStringList Packet);
    EntityType getLauncherEntityType();
    int getLauncherID();
    EntityType getTargetEntityType();
    int getTargetID();
    int getSkillID();
    int getSkillCD();
    int getAttackAnimation();
    int getSkillEffect();
    // ??? Maybe understandable with skillshot skill (it is always 0, except for some case, as Skill 16 SP4 Archer which is 1
    // ??? same except that I always found 0
    bool isTargetStillAlive();
    short getTargetPercentHP();
    int getDamageDealt();
    HitType getHitType();
    DamageType getDamageType();
};

#endif // PACKETSU_H

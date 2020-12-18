#include "packetsu.h"

PacketSu::PacketSu(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketSu::getLauncherEntityType()
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketSu::getLauncherID()
{
    return packet[2].toInt();
}

EntityType PacketSu::getTargetEntityType()
{
    return static_cast<EntityType>(packet[3].toInt());
}

int PacketSu::getTargetID()
{
    return packet[4].toInt();
}

int PacketSu::getSkillID()
{
    return packet[5].toInt();
}

int PacketSu::getSkillCD()
{
    return packet[6].toInt();
}

int PacketSu::getAttackAnimation()
{
    return packet[7].toInt();
}

int PacketSu::getSkillEffect()
{
    return packet[8].toInt();
}

bool PacketSu::isTargetStillAlive()
{
    return packet[11].toInt();
}

short PacketSu::getTargetPercentHP()
{
    return packet[10].toShort();
}

int PacketSu::getDamageDealt()
{
    return packet[11].toInt();
}

HitType PacketSu::getHitType()
{
    return static_cast<HitType>(packet[12].toInt());
}

DamageType PacketSu::getDamageType()
{
    return static_cast<DamageType>(packet[13].toInt());
}

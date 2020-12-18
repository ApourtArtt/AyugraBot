#ifndef PACKETLEV_H
#define PACKETLEV_H

#include "srcs/Packets/basepacket.h"

class PacketLev : public BasePacket
{
public:
    PacketLev(QStringList Packet);
    short getLevel();
    long getLevelXP();
    short getLevelJob();
    long getLevelJobXP();
    long getLevelMaxXP();
    long getLevelJobMaxXP();
    int getReputation();
    int getSkillCP();
    long getLevelHeroXP();
    short getLevelHero();
    long getLevelHeroMaxXP();
    // ???
};

#endif // PACKETLEV_H

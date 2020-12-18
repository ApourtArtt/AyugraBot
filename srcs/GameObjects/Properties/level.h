#ifndef LEVEL_H
#define LEVEL_H

#include "srcs/Packets/Server/World/packetlev.h"
#include "srcs/Packets/Server/World/packetclist.h"

class Level
{
public:
    Level();
    void handleLevPacket(PacketLev Packet);
    void handleClistPacket(PacketClist Packet);
    short getLevel() const;
    short getLevelJob() const;
    short getLevelHero() const;
    long getCurrentNormalXP() const;
    long getCurrentJobXP() const;
    long getCurrentHeroXP() const;
    long getMaxNormalXP() const;
    long getMaxJobXP() const;
    long getMaxHeroXP() const;
    double getPercentNormalXP() const;
    double getPercentJobXP() const;
    double getPercentHeroXP() const;

private:
    short level, levelJob, levelHero;
    long xpNormal, xpJob, xpHero;
    long xpNormalMax, xpJobMax, xpHeroMax;
};

#endif // LEVEL_H

#include "level.h"

Level::Level()
{
    level = -1;
    levelJob = -1;
    levelHero = -1;
    xpNormal = -1;
    xpJob = -1;
    xpHero = -1;
    xpNormalMax = -1;
    xpJobMax = -1;
    xpHeroMax = -1;
}


void Level::handleLevPacket(PacketLev Packet)
{
    level = Packet.getLevel();
    levelJob = Packet.getLevelJob();
    levelHero = Packet.getLevelHero();
    xpNormal = Packet.getLevelXP();
    xpJob = Packet.getLevelJobXP();
    xpHero = Packet.getLevelHeroXP();
    xpNormalMax = Packet.getLevelMaxXP();
    xpJobMax = Packet.getLevelJobMaxXP();
    xpHeroMax = Packet.getLevelHeroMaxXP();
}

void Level::handleClistPacket(PacketClist Packet)
{
    level = Packet.getLevel();
    levelJob = Packet.getLevelJob();
    levelHero = Packet.getLevelHero();
}

short Level::getLevel() const
{
    return level;
}

short Level::getLevelJob() const
{
    return levelJob;
}

short Level::getLevelHero() const
{
    return levelHero;
}

long Level::getCurrentNormalXP() const
{
    return xpNormal;
}

long Level::getCurrentJobXP() const
{
    return xpJob;
}

long Level::getCurrentHeroXP() const
{
    return xpHero;
}

long Level::getMaxNormalXP() const
{
    return xpNormalMax;
}

long Level::getMaxJobXP() const
{
    return xpJobMax;
}

long Level::getMaxHeroXP() const
{
    return xpHeroMax;
}

double Level::getPercentNormalXP() const
{
    return static_cast<double>(xpNormal) / static_cast<double>(xpNormalMax) * 100;
}

double Level::getPercentJobXP() const
{
    return static_cast<double>(xpJob) / static_cast<double>(xpJobMax) * 100;
}

double Level::getPercentHeroXP() const
{
    return static_cast<double>(xpHero) / static_cast<double>(xpHeroMax) * 100;
}

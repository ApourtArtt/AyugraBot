#include "statistics.h"

Statistics::Statistics()
{
    currentHP = -1;
    currentMP = -1;
    maxHP = -1;
    maxMP = -1;
}

void Statistics::handleStatPacket(PacketStat Packet)
{
    currentHP = Packet.getCurrentHP();
    currentMP = Packet.getCurrentMP();
    maxHP = Packet.getMaxHP();
    maxMP = Packet.getMaxMP();
}

void Statistics::handlePstatPacket(PacketPst Packet)
{
    currentHP = Packet.getHP();
    currentMP = Packet.getMP();
    maxHP = static_cast<int>(currentHP * static_cast<double>((1 / static_cast<double>(Packet.getHPPercent() / 100))));
    maxMP = static_cast<int>(currentMP * static_cast<double>((1 / static_cast<double>(Packet.getMPPercent() / 100))));
}

int Statistics::getMaxHP() const
{
    return maxHP;
}

int Statistics::getMaxMP() const
{
    return maxMP;
}

int Statistics::getCurrentHP() const
{
    return currentHP;
}

int Statistics::getCurrentMP() const
{
    return currentMP;
}

double Statistics::getPercentHP() const
{
    return static_cast<double>(currentHP) / static_cast<double>(maxHP);
}

double Statistics::getPercentMP() const
{
    return static_cast<double>(currentMP) / static_cast<double>(maxMP);
}

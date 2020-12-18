#ifndef STATISTICS_H
#define STATISTICS_H

#include "srcs/Packets/Server/World/packetstat.h"
#include "srcs/Packets/Server/World/packetpst.h"

class Statistics
{
public:
    Statistics();
    void handleStatPacket(PacketStat Packet);
    void handlePstatPacket(PacketPst Packet);
    int getMaxHP() const;
    int getMaxMP() const;
    int getCurrentHP() const;
    int getCurrentMP() const;
    double getPercentHP() const;
    double getPercentMP() const;

private:
    int currentHP;
    int currentMP;
    int maxHP;
    int maxMP;

};

#endif // STATISTICS_H

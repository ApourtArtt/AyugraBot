#ifndef PACKETSTAT_H
#define PACKETSTAT_H

#include "srcs/Packets/basepacket.h"

class PacketStat : public BasePacket
{
public:
    PacketStat(QStringList Packet);
    int getCurrentHP();
    int getMaxHP();
    int getCurrentMP();
    int getMaxMP();
    // 0 ??
    // Option
    // https://github.com/OpenNos/OpenNos/blob/f67fdcec7d8743e96ecafe42b6326a72f5455bc7/OpenNos.GameObject/Character.cs#L3657
    // http://www.cplusplus.com/forum/general/1590/
    // Don't have the knowledges yet, sadly
};

#endif // PACKETSTAT_H

#ifndef PACKETSR_H
#define PACKETSR_H

#include "srcs/Packets/basepacket.h"

class PacketSr : public BasePacket
{
public:
    PacketSr(QStringList Packet);
    int getEventID();
    int getCastID();
    int getRemainingCooldown();
};

#endif // PACKETSR_H

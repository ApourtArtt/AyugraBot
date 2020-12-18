#ifndef PACKETPSR_H
#define PACKETPSR_H

#include "srcs/Packets/basepacket.h"

class PacketPsr : public BasePacket
{
public:
    PacketPsr(QStringList Packet);
    int getSkillCastID() const;
};

#endif // PACKETPSR_H

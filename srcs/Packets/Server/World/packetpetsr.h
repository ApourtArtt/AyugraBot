#ifndef PACKETPETSR_H
#define PACKETPETSR_H

#include "srcs/Packets/basepacket.h"

class PacketPetsr : public BasePacket
{
public:
    PacketPetsr(QStringList Packet);
    int getSkillCastID();
};

#endif // PACKETPETSR_H

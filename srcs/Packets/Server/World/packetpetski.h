#ifndef PACKETPETSKI_H
#define PACKETPETSKI_H

#include "srcs/Packets/basepacket.h"

class PacketPetski : public BasePacket
{
public:
    PacketPetski(QStringList Packet);
    int getSkillID();
};

#endif // PACKETPETSKI_H

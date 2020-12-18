#ifndef PACKETESF_H
#define PACKETESF_H

#include "srcs/Packets/basepacket.h"

class PacketEsf : public BasePacket
{
public:
    PacketEsf(QStringList Packet);
    int getID();
};

#endif // PACKETESF_H

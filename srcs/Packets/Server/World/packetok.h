#ifndef PACKETOK_H
#define PACKETOK_H

#include "srcs/Packets/basepacket.h"

class PacketOK : public BasePacket
{
public:
    PacketOK(QStringList Packet);
};

#endif // PACKETOK_H

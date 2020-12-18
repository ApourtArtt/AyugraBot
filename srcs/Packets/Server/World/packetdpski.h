#ifndef PACKETDPSKI_H
#define PACKETDPSKI_H

#include "srcs/Packets/basepacket.h"

class PacketDpski : public BasePacket
{
public:
    PacketDpski(QStringList Packet);
};

#endif // PACKETDPSKI_H

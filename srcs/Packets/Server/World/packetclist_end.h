#ifndef PACKETCLIST_END_H
#define PACKETCLIST_END_H

#include "srcs/Packets/basepacket.h"

class PacketClist_end : public BasePacket
{
public:
    PacketClist_end(QStringList Packet);
};

#endif // PACKETCLIST_END_H

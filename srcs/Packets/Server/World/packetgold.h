#ifndef PACKETGOLD_H
#define PACKETGOLD_H

#include "srcs/Packets/basepacket.h"

class PacketGold : public BasePacket
{
public:
    PacketGold(QStringList Packet);
    int getGoldInventory();
    int getGoldBank();
};

#endif // PACKETGOLD_H

#ifndef PACKETIVN_H
#define PACKETIVN_H

#include "srcs/Packets/Server/World/packetinv.h"

class PacketIvn : public BasePacket
{
public:
    PacketIvn(QStringList Packet);
    InventoryType getInventoryType();
    PacketInvSub getInfo();
};

#endif // PACKETIVN_H

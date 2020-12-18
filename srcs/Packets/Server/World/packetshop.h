#ifndef PACKETSHOP_H
#define PACKETSHOP_H

#include "srcs/Enum/entityenum.h"
#include "srcs/Packets/basepacket.h"

class PacketShop : public BasePacket
{
public:
    PacketShop(QStringList Packet);
    EntityType getEntityType();
    int getSellerID();
    bool isShown();
    short getMenuType();
    short getShopType();
    QString getName();
};

#endif // PACKETSHOP_H

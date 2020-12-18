#ifndef SHOP_H
#define SHOP_H

#include "srcs/Packets/Server/World/packetshop.h"

class Shop
{
public:
    Shop();
    void handleShopPacket(PacketShop Packet);
    EntityType getEntityType() const;
    int getSellerID() const;
    bool isShown() const;
    int getMenuType() const;
    int getShopType() const;
    QString getName() const;

private:
    EntityType entityType;
    int sellerID;
    bool shown;
    int menuType;
    int shopType;
    QString name;
};

#endif // SHOP_H

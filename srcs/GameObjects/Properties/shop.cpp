#include "shop.h"

Shop::Shop()
{
    sellerID = -1;
    shown = false;
    menuType = -1;
    shopType = -1;
}

void Shop::handleShopPacket(PacketShop Packet)
{
    entityType = Packet.getEntityType();
    sellerID = Packet.getSellerID();
    shown = Packet.isShown();
    menuType = Packet.getMenuType();
    shopType = Packet.getShopType();
    name = Packet.getName();
}

EntityType Shop::getEntityType() const
{
    return entityType;
}

int Shop::getSellerID() const
{
    return sellerID;
}

bool Shop::isShown() const
{
    return shown;
}

int Shop::getMenuType() const
{
    return menuType;
}

int Shop::getShopType() const
{
    return shopType;
}

QString Shop::getName() const
{
    return name;
}

#include "packetshop.h"

PacketShop::PacketShop(QStringList Packet)
    : BasePacket(Packet)
{

}

EntityType PacketShop::getEntityType()
{
    return static_cast<EntityType>(packet[1].toInt());
}

int PacketShop::getSellerID()
{
    return packet[2].toInt();
}
bool PacketShop::isShown()
{
    return packet[3].toInt();
}

short PacketShop::getMenuType()
{
    return packet[4].toShort();
}

short PacketShop::getShopType()
{
    if(packet.size() < 5)
        return -1;
    return packet[5].toShort();
}

QString PacketShop::getName()
{
    QString name;
    for(int i = 6 ; i < packet.size() ; i++)
        name += " " + packet[i];
    name.remove(0, 1);
    return name;
}

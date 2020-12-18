#include "packetrest.h"
#include <QDebug>

PacketRest::PacketRest(int Quantity, QVector<QPair<EntityType, int>> EntityTypeAndID)
    : BasePacket("rest")
{
    quantity = Quantity == EntityTypeAndID.size() ? Quantity : -1;
    entityTypeAndID = EntityTypeAndID;
    packet.push_back(QString::number(quantity));
    for(int i = 0 ; i < quantity ; i++)
    {
        packet.push_back(QString::number(static_cast<int>(entityTypeAndID[i].first)));
        packet.push_back(QString::number(entityTypeAndID[i].second));
    }
}

bool PacketRest::isSendable()
{
    if(quantity < 1 || quantity > 3)
        return false;
    if(packet.size() != PACKET_SIZE + quantity * 2)
        return false;
    return true;
}

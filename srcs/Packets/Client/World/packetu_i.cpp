#include "packetu_i.h"


PacketU_i::PacketU_i(EntityType entType, int entID, InventoryType invType, short invSlot, int _x, int _y, int _option1, int _option2)
    : BasePacket("u_i")
{ // u_i 1 677027 2 7 0 0
    entityType = entType;
    entityID = entID;
    inventoryType = invType;
    inventorySlot = invSlot;
    x = _x;
    y = _y;
    option1 = _option1;
    option2 = _option2;
    packet.push_back(QString::number(static_cast<int>(entityType)));
    packet.push_back(QString::number(entityID));
    packet.push_back(QString::number(static_cast<int>(inventoryType)));
    packet.push_back(QString::number(inventorySlot));
    packet.push_back(QString::number(x));
    packet.push_back(QString::number(y));
    if(option1 != -1)
        packet.push_back(QString::number(option1));
    if(option2 != -1)
        packet.push_back(QString::number(option2));
}

bool PacketU_i::isSendable()
{
    if(entityID < 0)
        return false;
    if(inventorySlot < 0 || inventorySlot > 119)
        return false;
    if(static_cast<int>(inventoryType) < 0 || static_cast<int>(inventoryType) > 10)
        return false;
    if(static_cast<int>(entityType) < 0 || static_cast<int>(entityType) > 10)
        return false;
    if(x < 0)
        return false;
    if(y < 0)
        return false;
    if(packet.size() < PACKET_SIZE || packet.size() > PACKET_SIZE + OPTIONS)
        return false;
    return true;
}

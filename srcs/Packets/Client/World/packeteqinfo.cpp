#include "packeteqinfo.h"

PacketEqinfo::PacketEqinfo(int invType, int invSlot)
    : BasePacket("eqinfo")
{
    inventoryType = invType;
    inventorySlot = invSlot;
    packet.push_back(QString::number(inventoryType));
    packet.push_back(QString::number(inventorySlot));
}

bool PacketEqinfo::isSendable()
{
    if(inventoryType < 0 || inventoryType > 11)
        return false;
    if(inventorySlot < 0 || inventorySlot > 119)
        return false;
    if(packet.size() != PACKET_SIZE)
        return false;
    return true;
}

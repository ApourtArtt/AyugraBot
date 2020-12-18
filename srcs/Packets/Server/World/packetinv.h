#ifndef PACKETINV_H
#define PACKETINV_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/inventoryenum.h"

class PacketInvSub
{
public:
    PacketInvSub();
    PacketInvSub(QString SubPacket);
    short getSlot();
    int getVnum();
    Rarity getRarity();
    int getQuantity();
    short getUpgrade();
    bool isActivated();
    short getEnhancement();

private:
    short slot;
    int vnum;
    Rarity rarity;
    int quantity;
    short upgrade;
    bool activated;
    short enhancement;
};

class PacketInv : BasePacket
{
public:
    PacketInv(QStringList Packet);
    InventoryType getInventoryType();
    std::vector<short> getAvailableSlot();
    PacketInvSub getInfoSlot(short slot);
};

#endif // PACKETINV_H

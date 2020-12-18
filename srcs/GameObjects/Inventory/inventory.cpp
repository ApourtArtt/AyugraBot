#include "inventory.h"

Inventory::Inventory(QObject *parent)
    : QObject(parent)
{
    inventoryGold = 0;
    bankGold = 0;
}

Inventory::~Inventory()
{
    subInv.clear();
}

void Inventory::treatInvPacket(PacketInv Packet)
{
    SubInventory *newInv = new SubInventory(this);
    connect(newInv, &SubInventory::sendPacket, this, [=](QString packet){emit sendPacket(packet);});
    newInv->treatPacketInv(Packet);
    subInv[Packet.getInventoryType()] = newInv;
}

void Inventory::treatIvnPacket(PacketIvn Packet)
{
    subInv[Packet.getInventoryType()]->treatPacketIvn(Packet);
}

void Inventory::treatGoldPacket(PacketGold Packet)
{
    inventoryGold = Packet.getGoldInventory();
    bankGold = Packet.getGoldBank();
}

SubInventory *Inventory::getSubinventory(InventoryType invT) const
{
    if(invT == InventoryType::ETC_L)
        return subInv[InventoryType::ETC];
    else if(invT == InventoryType::MAIN_L)
        return subInv[InventoryType::MAIN];
    else if(invT == InventoryType::EQUIPMENT_L || invT == InventoryType::ACCESSORIES || invT == InventoryType::UNKNOWN5)
        return subInv[InventoryType::EQUIPMENT];
    return subInv[invT];
}

int Inventory::getInventoryGold() const
{
    return inventoryGold;
}

int Inventory::getBankGold() const
{
    return bankGold;
}

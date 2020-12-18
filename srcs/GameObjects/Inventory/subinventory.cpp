#include "subinventory.h"

SubInventory::SubInventory(QObject *parent)
    : QObject(parent)
{

}

SubInventory::~SubInventory()
{
    items.clear();
}

void SubInventory::treatPacketInv(PacketInv Packet)
{
    invType = Packet.getInventoryType();
    std::vector<short> availableSlot = Packet.getAvailableSlot();
    for(size_t i = 0 ; i < availableSlot.size() ; i++)
    {
        PacketInvSub tmp = Packet.getInfoSlot(availableSlot[i]);
        Item *tmpItem = new Item(tmp.getVnum(), this);
        connect(tmpItem, &Item::sendPacket, this, [=](QString packet){emit sendPacket(packet);});
        items[availableSlot[i]] = tmpItem;
        items[availableSlot[i]]->treatSubInvPacket(tmp);
    }
}

void SubInventory::treatPacketIvn(PacketIvn Packet)
{
    PacketInvSub packet = Packet.getInfo();
    if(packet.getVnum() == -1)
        items.remove(packet.getSlot());
    else
    {
        Item *tmpItem = new Item(packet.getVnum(), this);
        items[packet.getSlot()] = tmpItem;
        items[packet.getSlot()]->treatSubInvPacket(packet);
    }
}

Item *SubInventory::getItem(short slot) const
{
    return items[slot];
}

QMap<short, Item*> SubInventory::getItemList() const
{
    return items;
}

void SubInventory::getItemsInfos(int inventoryType, int inventorySlot)
{
    sendPacket(PacketEqinfo(inventoryType, inventorySlot).getPacket());
}

short SubInventory::getItemSlotFromID(int id)
{
    QList<short> keys = items.keys();
    for(int i = 0 ; i < keys.size() ; i++)
    {
        if(items[keys[i]]->getVnum() == id)
            return items[keys[i]]->getSlot();
    }
    return -1;
}

void SubInventory::moveItem(int quantity, short cellDest, short cellOrigin)
{
    PacketMvi packet(invType, cellOrigin, quantity, cellDest);
    sendPacket(packet.getPacket());
}
#include <QDebug>
void SubInventory::useItem(short slot, EntityType entityType, int entityID)
{
    qDebug() << "InvType in SubInv : " << static_cast<int>(invType);
    if(items.contains(slot))
        useItem(items[slot], entityType, entityID);
}
// TODO : integrate other item properties
void SubInventory::useItem(Item *item, EntityType entityType, int entityID)
{
    if(!item)
        return;
    // TODO : this is not the real condition
    // some items are placed in equip inv but still uses u_i
    // need to know how it is managed in dat files
    // Will still work for 99% of items
    if(invType == InventoryType::EQUIPMENT)
        wearItem(item);
    else
        sendPacket(PacketU_i(entityType, entityID, invType, item->getSlot(), 0, 0).getPacket());
}

void SubInventory::wearItem(short slot)
{
    qDebug() << "WearItem";
    if(items.contains(slot))
        wearItem(items[slot]);
}

void SubInventory::wearItem(Item *item)
{
    qDebug() << "WearItem item";
    if(!item)
        return;
    qDebug() << "WearItem ok";
    PacketWear packet(item->getSlot(), 0);
    sendPacket(packet.getPacket());
}

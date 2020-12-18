#ifndef SUBINVENTORY_H
#define SUBINVENTORY_H

#include <QObject>
#include "srcs/Enum/inventoryenum.h"
#include "srcs/GameObjects/Inventory/item.h"
#include "srcs/Packets/Server/World/packetivn.h"
#include "srcs/Packets/Client/World/packetmvi.h"
#include "srcs/Packets/Client/World/packetwear.h"
#include "srcs/Packets/Client/World/packetu_i.h"
#include "srcs/Packets/Client/World/packeteqinfo.h"

class SubInventory : public QObject
{
    Q_OBJECT
public:
    SubInventory(QObject *parent);
    ~SubInventory();

    void treatPacketInv(PacketInv Packet);
    void treatPacketIvn(PacketIvn Packet);
    Item *getItem(short slot) const;
    QMap<short, Item*> getItemList() const;
    void getItemsInfos(int inventoryType, int inventorySlot);
    short getItemSlotFromID(int id);
    void moveItem(int quantity, short cellDest, short cellOrigin);
    void useItem(short slot, EntityType entityType, int entityID);    // It is usable for basic items (such as potions)
    void useItem(Item *item, EntityType entityType, int entityID);  // DatabaseItem is still missing informations about
    void wearItem(short slot);   // specials one like Miniland bell.
    void wearItem(Item *item); // Also, some items in equipment requires a u_i packet

signals:
    void sendPacket(QString packet);

private:
    InventoryType invType;
    QMap<short, Item*> items;
};

#endif // SUBINVENTORY_H

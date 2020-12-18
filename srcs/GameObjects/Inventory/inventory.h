#ifndef INVENTORY_H
#define INVENTORY_H

#include <QObject>
#include "srcs/GameObjects/Inventory/subinventory.h"
#include "srcs/Packets/Server/World/packetgold.h"

class Inventory : public QObject
{
    Q_OBJECT
public:
    Inventory(QObject *parent);
    ~Inventory();

    void treatInvPacket(PacketInv Packet);
    void treatIvnPacket(PacketIvn Packet);
    void treatGoldPacket(PacketGold Packet);
    SubInventory *getSubinventory(InventoryType invT) const;
    int getInventoryGold() const;
    int getBankGold() const;

signals:
    void sendPacket(QString packet);

private:
    QMap<InventoryType, SubInventory*> subInv;
    int inventoryGold;
    int bankGold;
};

#endif // INVENTORY_H

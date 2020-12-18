#ifndef ITEM_H
#define ITEM_H

#include "srcs/Database/databaseitem.h"
#include "srcs/Enum/inventoryenum.h"
#include "srcs/Packets/Server/World/packetinv.h"

class Item : public QObject, public ItemFromDb
{
    Q_OBJECT
public:
    Item(QObject *parent) : QObject(parent){}
    Item(int Vnum, QObject *parent);
    void treatSubInvPacket(PacketInvSub Packet);
    short getSlot() const;
    short getUpgrade() const;
    Rarity getRarity() const;
    int getQuantity() const;
    bool isActivated() const;
    short getEnhancement() const;

signals:
    void sendPacket(QString packet);

private:
    short slot;
    short upgrade;
    Rarity rarity;
    int quantity;
    bool activated; // Special interaction with some items (equipment vehicle booster for example)
    short enhancement;
};

#endif // ITEM_H

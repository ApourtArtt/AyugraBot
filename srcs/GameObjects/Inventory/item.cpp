#include "item.h"

Item::Item(int Vnum, QObject *parent)
    : QObject(parent)
{
    ItemFromDb::getDataFromVnum(Vnum);
}

void Item::treatSubInvPacket(PacketInvSub Packet)
{
    slot = Packet.getSlot();
    upgrade = Packet.getUpgrade();
    rarity = Packet.getRarity();
    quantity = Packet.getQuantity();
    activated = Packet.isActivated();
    enhancement = Packet.getEnhancement();
}

short Item::getSlot() const
{
    return slot;
}

short Item::getUpgrade() const
{
    return upgrade;
}

Rarity Item::getRarity() const
{
    return rarity;
}

int Item::getQuantity() const
{
    return quantity;
}

bool Item::isActivated() const
{
    return activated;
}

short Item::getEnhancement() const
{
    return enhancement;
}

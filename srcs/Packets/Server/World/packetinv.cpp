#include "packetinv.h"

PacketInvSub::PacketInvSub()
{
    slot = -1;
    vnum = -1;
    quantity = -1;
    upgrade = -1;
    rarity = Rarity::NORMAL;
    activated = false;
    enhancement = -1;
}

PacketInvSub::PacketInvSub(QString SubPacket)
{
    QStringList packet = SubPacket.split(".");
    slot = packet[0].toShort();
    vnum = packet[1].toInt();
    rarity = static_cast<Rarity>(packet[2].toInt());
    quantity = packet[2].toInt();
    if(packet.size() > 3) upgrade = packet[3].toShort();        else upgrade = -1;
    if(packet.size() > 4) activated = packet[4].toShort();      else activated = -1;
    if(packet.size() > 5) enhancement = packet[5].toShort();    else enhancement = -1;
}

short PacketInvSub::getSlot()
{
    return slot;
}

int PacketInvSub::getVnum()
{
    return vnum;
}

Rarity PacketInvSub::getRarity()
{
    return rarity;
}

int PacketInvSub::getQuantity()
{
    return quantity;
}

short PacketInvSub::getUpgrade()
{
    return upgrade;
}

bool PacketInvSub::isActivated()
{
    return activated;
}

short PacketInvSub::getEnhancement()
{
    return enhancement;
}


PacketInv::PacketInv(QStringList Packet)
    : BasePacket(Packet)
{

}

InventoryType PacketInv::getInventoryType()
{
    return static_cast<InventoryType>(packet[1].toInt());
}

std::vector<short> PacketInv::getAvailableSlot()
{
    std::vector<short> availableSlot;
    for(int i = 2 ; i < packet.size() ; i++)
        availableSlot.push_back(packet[i].split(".")[0].toShort());
    return availableSlot;
}

PacketInvSub PacketInv::getInfoSlot(short slot)
{
    for(int i = 2 ; i < packet.size() ; i++)
    {
        if(packet[i].split(".")[0].toInt() == slot)
            return PacketInvSub(packet[i]);
    }
    return PacketInvSub();
}

#include "packetmvi.h"

PacketMvi::PacketMvi(InventoryType _InventoryType, int CellOrigin, int Quantity, int CellDestination)
    : BasePacket("mvi")
{
    inventoryType = _InventoryType;
    cellOrigin = CellOrigin;
    quantity = Quantity;
    cellDestination = CellDestination;
    packet.push_back(QString::number(static_cast<int>(inventoryType)));
    packet.push_back(QString::number(cellOrigin));
    packet.push_back(QString::number(quantity));
    packet.push_back(QString::number(cellDestination));
}

bool PacketMvi::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    if(static_cast<int>(inventoryType) < 0 || static_cast<int>(inventoryType) > 10)
        return false;
    if(cellOrigin < 0 || cellOrigin > 119)
        return false;
    if(cellDestination < 0 || cellDestination > 119)
        return false;
    if(quantity < 0 || quantity > 999)
        return false;
    return true;
}

#ifndef PACKETMVI_H
#define PACKETMVI_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/inventoryenum.h"

class PacketMvi : public BasePacket
{
public:
    PacketMvi(InventoryType _InventoryType, int CellOrigin, int Quantity, int CellDestination);
    virtual bool isSendable() override;

private:
    InventoryType inventoryType;
    int cellOrigin;
    int quantity;
    int cellDestination;
    const int PACKET_SIZE = 5;
};

#endif // PACKETMVI_H

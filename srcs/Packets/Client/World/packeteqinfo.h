#ifndef PACKETEQINFO_H
#define PACKETEQINFO_H

#include "srcs/Packets/basepacket.h"

class PacketEqinfo : public BasePacket
{
public: // Cannot use InventoryType since extra inventory has a strange behaviour
    PacketEqinfo(int invType, int invSlot);
    virtual bool isSendable() override;

private:
    int inventoryType;
    int inventorySlot;
    const int PACKET_SIZE = 3;
};

#endif // PACKETEQINFO_H

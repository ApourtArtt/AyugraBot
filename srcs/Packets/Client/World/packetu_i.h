#ifndef PACKETU_I_H
#define PACKETU_I_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"
#include "srcs/Enum/inventoryenum.h"
class PacketU_i : public BasePacket
{
public:
    PacketU_i(EntityType entType, int entID, InventoryType invType, short invSlot,
              int _x, int _y, int _option1 = -1, int _option2 = -1);
    virtual bool isSendable() override;

    // u_i EntityType EntityID InventoryType InventorySlot x y [option1] [option2]
private:
    EntityType entityType;
    int entityID;
    InventoryType inventoryType;
    short inventorySlot;
    int x;
    int y;
    int option1;
    int option2;
    const int PACKET_SIZE   = 7;
    const int OPTIONS       = 2;
};

#endif // PACKETU_I_H

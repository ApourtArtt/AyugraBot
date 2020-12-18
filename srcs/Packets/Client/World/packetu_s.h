#ifndef PACKETU_S_H
#define PACKETU_S_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"

class PacketU_s : public BasePacket
{
    // u_s [skillCastID] [EntityType] [EntityID] [opt1:PosX] [opt2:PosY]
public:
    PacketU_s(int SkillCastID, EntityType Entitytype, int EntityID, int PosX = -1, int PosY = -1);
    virtual bool isSendable() override;

private:
    int skillCastID;
    EntityType entityType;
    int entityID;
    int posX;
    int posY;
    const int PACKET_SIZE   = 4;
    const int OPTIONS       = 2;
};

#endif // PACKETU_S_H

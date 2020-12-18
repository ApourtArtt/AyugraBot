#ifndef PACKETU_PET_H
#define PACKETU_PET_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"
//u_pet nosmateID entityType entityID castid x y
class PacketU_pet : public BasePacket
{
public:
    PacketU_pet(int NosmateID, EntityType EntityType, int EntityID, int SkillCastID, int X, int Y);
    virtual bool isSendable() override;

private:
    int nosmateID;
    EntityType entityType;
    int entityID;
    int skillCastID;
    int x;
    int y;
    const int PACKET_SIZE = 7;
};

#endif // PACKETU_PET_H

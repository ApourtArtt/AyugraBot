#include "packetu_pet.h"

PacketU_pet::PacketU_pet(int NosmateID, EntityType EntityType, int EntityID, int SkillCastID, int X, int Y)
    : BasePacket("u_pet")
{
    nosmateID = NosmateID;
    entityType = EntityType;
    entityID = EntityID;
    skillCastID = SkillCastID;
    x = X;
    y = Y;
    packet.push_back(QString::number(nosmateID));
    packet.push_back(QString::number(static_cast<int>(entityType)));
    packet.push_back(QString::number(entityID));
    packet.push_back(QString::number(skillCastID));
    packet.push_back(QString::number(x));
    packet.push_back(QString::number(y));
}

bool PacketU_pet::isSendable()
{
    if(nosmateID < 0)
        return false;
    if(entityID < 0)
        return false;
    if(skillCastID < 0)
        return false;
    if(x < 0 || x > 300)
        return false;
    if(y < 0 || y > 300)
        return false;
    return true;
}

#include "packetu_s.h"

PacketU_s::PacketU_s(int SkillCastID, EntityType Entitytype, int EntityID, int PosX, int PosY)
    : BasePacket("u_s")
{
    skillCastID = SkillCastID;
    entityType = Entitytype;
    entityID = EntityID;
    posX = PosX;
    posY = PosY;
    packet.push_back(QString::number(skillCastID));
    packet.push_back(QString::number(static_cast<int>(entityType)));
    packet.push_back(QString::number(entityID));
    if(posX != -1 && posY != -1)
    {
        packet.push_back(QString::number(posX));
        packet.push_back(QString::number(posY));
    }
}

bool PacketU_s::isSendable()
{
    int size = packet.size();
    if(size != PACKET_SIZE && size != PACKET_SIZE + OPTIONS)
        return false;
    if(skillCastID < 0)
        return false;
    if(entityID < 0)
        return false;
    if(size == PACKET_SIZE + OPTIONS)
    {
        if(posX < 0) return false;
        if(posY < 0) return false;
    }
    return true;
}

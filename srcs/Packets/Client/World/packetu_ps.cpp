#include "packetu_ps.h"

PacketU_ps::PacketU_ps(int CasterID, EntityType EntityType, int TargetID, int SkillCastID, int X, int Y)
    : BasePacket("u_ps")
{
    casterID = CasterID;
    entityType = EntityType;
    targetID = TargetID;
    skillCastID = SkillCastID;
    x = X;
    y = Y;
    packet.push_back(QString::number(casterID));
    packet.push_back(QString::number(static_cast<int>(entityType)));
    packet.push_back(QString::number(targetID));
    packet.push_back(QString::number(SkillCastID));
    if(x != -1 && y != -1)
    {
        packet.push_back(QString::number(x));
        packet.push_back(QString::number(y));
    }
}

bool PacketU_ps::isSendable()
{
    if(casterID < 0)
        return false;
    if(targetID < 0)
        return false;
    if(skillCastID < 0)
        return false;
    if(packet.size() != PACKET_SIZE && packet.size() != (PACKET_SIZE + OPTION_SIZE))
        return false;
    return true;
}

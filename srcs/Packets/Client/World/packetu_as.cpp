#include "packetu_as.h"

PacketU_as::PacketU_as(int SkillCastID, int PosX, int PosY)
    : BasePacket("u_as")
{
    skillCastID = SkillCastID;
    posX = PosX;
    posY = PosY;
    packet.push_back(QString::number(skillCastID));
    packet.push_back(QString::number(posX));
    packet.push_back(QString::number(posY));
}

bool PacketU_as::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    if(skillCastID < 0)
        return false;
    if(posX < 0)
        return false;
    if(posY < 0)
        return false;
    return true;
}

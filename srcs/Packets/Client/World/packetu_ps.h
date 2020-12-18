#ifndef PACKETU_PS_H
#define PACKETU_PS_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"

class PacketU_ps : public BasePacket
{
public: // 609445 3 2088 0
    PacketU_ps(int CasterID, EntityType EntityType, int TargetID, int SkillCastID, int X = -1, int Y = -1);
    virtual bool isSendable() override;

private:
    int casterID;
    EntityType entityType;
    int targetID;
    int skillCastID;
    int x;
    int y;
    const int PACKET_SIZE = 5;
    const int OPTION_SIZE = 2;
};

#endif // PACKETU_PS_H

#ifndef PACKETU_AS_H
#define PACKETU_AS_H

#include "srcs/Packets/basepacket.h"

class PacketU_as : public BasePacket
{
    // u_as [skillCastID] [posX] [posY]
public:
    PacketU_as(int SkillCastID, int PosX, int PosY);
    virtual bool isSendable() override;

private:
    int skillCastID;
    int posX;
    int posY;
    const int PACKET_SIZE = 4;
};

#endif // PACKETU_AS_H

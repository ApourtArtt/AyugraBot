#ifndef PACKETC_INFO_H
#define PACKETC_INFO_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/characterenum.h"
#include "srcs/Enum/reputationenum.h"

class PacketC_info : public BasePacket
{
public:
    PacketC_info(QStringList Packet);
    QString getPseudonym();
    int getGroupID();
    int getFamilyID();
    QString getFamilyNameRole();
    int getCharacterID();
    Authority getAuthority();
    Gender getGender();
    HairStyle getHairStyle();
    short getHairColor();
    Class getClass();
    ReputationIcon getReputationIcon();
    short getAdmiration();
    short getMorph();
    bool isInvisible();
    short getFamilyLevel();
    short getSpUpgrade();
    bool isArenaWinner();
};

#endif // PACKETC_INFO_H

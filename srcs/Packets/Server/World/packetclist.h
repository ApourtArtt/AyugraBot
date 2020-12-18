#ifndef PACKETCLIST_H
#define PACKETCLIST_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/characterenum.h"

class PacketClist : public BasePacket
{
public:
    PacketClist(QStringList Packet);
    short getSlot();
    QString getPseudonym();
    // ???
    Gender getSexe();
    HairStyle getHairStyle();
    short getHairColor();
    // ???
    Class getClass();
    short getLevel();
    short getLevelHero();
    QString getWornStuff();
    short getLevelJob();
    short getQuestAct();
    short getQuestChapter();
    QString getPetsSkin();
    // ???
    bool shouldBeRenamed();
};

#endif // PACKETCLIST_H

#ifndef QUEST_H
#define QUEST_H

#include "srcs/Packets/Server/World/packetclist.h"
#include "srcs/Packets/Server/World/packetrsfi.h"

class Quest
{
public:
    Quest();
    void handleClistPacket(PacketClist Packet);
    void handleRsfiPacket(PacketRsfi Packet);
    short getQuestAct() const;
    short getQuestPart() const;
    short getTSDone() const;
    short getTSTotal() const;

private:
    short questAct;
    short questPart;
    short tsDone;
    short tsTotal;
};

#endif // QUEST_H

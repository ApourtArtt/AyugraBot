#include "quest.h"

Quest::Quest()
{
    questAct = -1;
    questPart = -1;
    tsDone = -1;
    tsTotal = -1;
}

void Quest::handleClistPacket(PacketClist Packet)
{
    questAct = Packet.getQuestAct();
    questPart = Packet.getQuestChapter();
}

void Quest::handleRsfiPacket(PacketRsfi Packet)
{
    questAct = Packet.getQuestAct();
    questPart = Packet.getQuestPart();
    tsDone = Packet.getTSDone();
    tsTotal = Packet.getTSTotal();
}

short Quest::getQuestAct() const
{
    return questAct;
}

short Quest::getQuestPart() const
{
    return questPart;
}

short Quest::getTSDone() const
{
    return tsDone;
}

short Quest::getTSTotal() const
{
    return tsTotal;
}

#ifndef PACKETRSFI_H
#define PACKETRSFI_H

#include "srcs/Packets/basepacket.h"

class PacketRsfi : public BasePacket
{
public:
    PacketRsfi(QStringList Packet);
    short getQuestAct();
    short getQuestPart();
    // ??? Packet[3] = Packet[5]
    // ??? Packet[4] = Packet[6]
    short getTSDone();
    short getTSTotal();
};

#endif // PACKETRSFI_H

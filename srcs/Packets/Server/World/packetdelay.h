#ifndef PACKETDELAY_H
#define PACKETDELAY_H

#include "srcs/Packets/basepacket.h"

class PacketDelay : public BasePacket
{
public:
    PacketDelay(QStringList Packet);
    int msToWait() const;
    int getGuriArgument() const;
    QString getPacketAnswer() const;
};

#endif // PACKETDELAY_H

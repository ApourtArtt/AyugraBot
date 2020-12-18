#ifndef PACKETPDELAY_H
#define PACKETPDELAY_H

#include "srcs/Packets/basepacket.h"

class PacketPdelay : public BasePacket
{
public: // pdelay 5000 3 #psl^1
    PacketPdelay(QStringList Packet);
    int msToWait() const;
    int getGuriArgument() const;
    QString getPacketAnswer() const;
};

#endif // PACKETPDELAY_H

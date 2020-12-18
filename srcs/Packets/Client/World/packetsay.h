#ifndef PACKETSAY_H
#define PACKETSAY_H

#include "srcs/Packets/basepacket.h"

class PacketSay : public BasePacket
{
public:
    PacketSay(QString Message);
    virtual bool isSendable() override;

private:
    QString message;
    const int PACKET_SIZE = 2;
};

#endif // PACKETSAY_H

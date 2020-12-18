#ifndef PACKETWREQ_H
#define PACKETWREQ_H

#include "srcs/Packets/basepacket.h"

class PacketWreq : public BasePacket
{
public:
    PacketWreq(bool Enter, bool Record);
    virtual bool isSendable() override;

private:
    bool enter;
    bool record;
    const int PACKET_SIZE = 1;
};

#endif // PACKETWREQ_H

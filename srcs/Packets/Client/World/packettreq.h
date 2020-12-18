#ifndef PACKETTREQ_H
#define PACKETTREQ_H

#include "srcs/Packets/basepacket.h"

class PacketTreq : public BasePacket
{
public:
    PacketTreq(int X, int Y, bool Enter = false, bool Record = false);
    virtual bool isSendable() override;

private:
    int x;
    int y;
    bool enter;
    bool record;
    const int PACKET_SIZE = 3;
};

#endif // PACKETTREQ_H

#ifndef PACKETWEAR_H
#define PACKETWEAR_H

#include "srcs/Packets/basepacket.h"

class PacketWear : public BasePacket
{
public:
    PacketWear(int Slot, short TargetSlot);
    virtual bool isSendable() override;

private:
    int slot;
    short targetSlot;
    const int PACKET_SIZE = 3;
};

#endif // PACKETWEAR_H

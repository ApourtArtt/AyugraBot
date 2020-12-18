#ifndef PACKETSELECT_H
#define PACKETSELECT_H

#include "srcs/Packets/basepacket.h"

class PacketSelect : public BasePacket
{
public:
    PacketSelect(short Slot);
    virtual bool isSendable() override;

private:
    short slot;
    const int PACKET_SIZE = 2;
};

#endif // PACKETSELECT_H

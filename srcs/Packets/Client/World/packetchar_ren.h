#ifndef PACKETCHAR_REN_H
#define PACKETCHAR_REN_H

#include "srcs/Packets/basepacket.h"

class PacketCHAR_REN : public BasePacket
{
public:
    PacketCHAR_REN(short Slot, QString Pseudonym);
    virtual bool isSendable() override;

private:
    short slot;
    QString pseudonym;
    const int PACKET_SIZE = 3;
};

#endif // PACKETCHAR_REN_H

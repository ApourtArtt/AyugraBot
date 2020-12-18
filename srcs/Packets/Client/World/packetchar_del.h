#ifndef PACKETCHAR_DEL_H
#define PACKETCHAR_DEL_H

#include "srcs/Packets/basepacket.h"

class PacketChar_DEL : public BasePacket
{
public:
    PacketChar_DEL(short Slot, QString Username);
    virtual bool isSendable() override;

private:
    short slot;
    QString username;
    const int PACKET_SIZE = 3;
};

#endif // PACKETCHAR_DEL_H

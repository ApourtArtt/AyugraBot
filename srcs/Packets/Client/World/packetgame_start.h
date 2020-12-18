#ifndef PACKETGAME_START_H
#define PACKETGAME_START_H

#include "srcs/Packets/basepacket.h"

class PacketGame_start : public BasePacket
{
public:
    PacketGame_start();
    virtual bool isSendable() override;

private:
    const int PACKET_SIZE = 1;
};

#endif // PACKETGAME_START_H

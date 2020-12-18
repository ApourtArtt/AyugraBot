#ifndef PACKETPULSE_H
#define PACKETPULSE_H

#include "srcs/Packets/basepacket.h"

class PacketPulse : public BasePacket
{
public:
    PacketPulse(int Time, int RandomPart);
    virtual bool isSendable() override;

private:
    int time;
    int randomPart;
    const int PACKET_SIZE = 3;
};

#endif // PACKETPULSE_H

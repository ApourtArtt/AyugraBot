#ifndef PACKETMSLOT_H
#define PACKETMSLOT_H

#include "srcs/Packets/basepacket.h"

class PacketMslot : public BasePacket
{
public:
    PacketMslot(QStringList Packet);
    int getCastID();
    int getKeybindID();
};

#endif // PACKETMSLOT_H

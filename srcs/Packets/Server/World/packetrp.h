#ifndef PACKETRP_H
#define PACKETRP_H

#include "srcs/Packets/basepacket.h"

class PacketRp : public BasePacket
{
public: // rp mapID x y packetToAccept
    PacketRp(QStringList Packet);
    int getMapID() const;
    int getX() const;
    int getY() const;
    QString getPacketToAccept() const;
};

#endif // PACKETRP_H

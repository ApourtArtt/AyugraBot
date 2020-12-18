#ifndef PACKETTP_H
#define PACKETTP_H

#include "srcs/Packets/basepacket.h"
#include "srcs/Enum/entityenum.h"

class PacketTp : public BasePacket
{
public: // tp 1 1075194 115 144 0
    PacketTp(QStringList Packet);
    EntityType getEntityType() const;
    int getEntityID() const;
    int getX() const;
    int getY() const;
    // ??
};

#endif // PACKETTP_H

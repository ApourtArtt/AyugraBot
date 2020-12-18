#ifndef PORTALS_H
#define PORTALS_H

#include "srcs/Packets/Server/World/packetgp.h"

class Portal
{
public:
    Portal(){}
    Portal(PacketGp Packet);
    void handleGpPacket(PacketGp Packet);
    short getX() const;
    short getY() const;
    int getMapID() const;
    PortalType getType() const;
    int getID() const;
    bool isInvisible() const;
    bool isClosed() const;

private:
    short x;
    short y;
    int mapID;
    PortalType type;
    int id;
    bool invisible;
    bool closed;
};

#endif // PORTAL_H

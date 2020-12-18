#include "srcs/GameObjects/Map/portals.h"

Portal::Portal(PacketGp Packet)
{
    handleGpPacket(Packet);
}

void Portal::handleGpPacket(PacketGp Packet)
{
    x = Packet.getX();
    y = Packet.getY();
    mapID = Packet.getMapID();
    type = Packet.getType();
    id = Packet.getID();
    invisible = Packet.isInvisible();
    if(type == PortalType::CLOSED || type == PortalType::EXIT_CLOSED || type == PortalType::TS_END_CLOSED)
        closed = true;
    else
        closed = false;
}

short Portal::getX() const
{
    return x;
}

short Portal::getY() const
{
    return y;
}

int Portal::getMapID() const
{
    return mapID;
}

PortalType Portal::getType() const
{
    return type;
}

int Portal::getID() const
{
    return id;
}

bool Portal::isInvisible() const
{
    return invisible;
}

bool Portal::isClosed() const
{
    return closed;
}

#include "packetnpinfo.h"

PacketNpinfo::PacketNpinfo(short Page)
    : BasePacket("npinfo")
{
    page = Page;
    packet.push_back(QString::number(page));
}

bool PacketNpinfo::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    // How to get number max of page ?
    // Have to retrieve it from sc_p packet but it is dirty to get those values
    //if(page < 0 || slot > 3)
    //    return false;
    return true;
}

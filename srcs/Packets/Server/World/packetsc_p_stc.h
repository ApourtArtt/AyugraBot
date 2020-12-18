#ifndef PACKETSC_P_STC_H
#define PACKETSC_P_STC_H

#include "srcs/Packets/basepacket.h"

class PacketSc_p_stc : BasePacket
{
public:
    PacketSc_p_stc(QStringList Packet);
    short getExtNosmate();
    short getExtPartner();
};

#endif // PACKETSC_P_STC_H

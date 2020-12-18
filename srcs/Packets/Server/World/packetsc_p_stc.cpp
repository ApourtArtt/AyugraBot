#include "packetsc_p_stc.h"

PacketSc_p_stc::PacketSc_p_stc(QStringList Packet)
    : BasePacket(Packet)
{

}

short PacketSc_p_stc::getExtNosmate()
{
    return packet[1].toShort();
}

short PacketSc_p_stc::getExtPartner()
{
    return packet[2].toShort();
}

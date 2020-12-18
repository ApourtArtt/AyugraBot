#include "packetpreq.h"

PacketPreq::PacketPreq()
    : BasePacket("preq")
{

}

bool PacketPreq::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    return true;
}

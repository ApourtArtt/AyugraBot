#include "packetpleave.h"

PacketPleave::PacketPleave()
    : BasePacket("pleave")
{

}

bool PacketPleave::isSendable()
{
    return packet.size() == PACKET_SIZE;
}

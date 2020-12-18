#include "packetf_stash_end.h"

PacketF_stash_end::PacketF_stash_end()
    : BasePacket("f_stash_end")
{

}

bool PacketF_stash_end::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    return true;
}

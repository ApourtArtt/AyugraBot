#include "packetgame_start.h"

PacketGame_start::PacketGame_start()
    : BasePacket("game_start")
{

}

bool PacketGame_start::isSendable()
{
    if(packet.size() != PACKET_SIZE)
        return false;
    return true;
}

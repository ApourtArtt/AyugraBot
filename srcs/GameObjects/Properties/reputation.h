#ifndef REPUTATION_H
#define REPUTATION_H

#include "srcs/Enum/reputationenum.h"
#include "srcs/Packets/Server/World/packetfd.h"
#include "srcs/Packets/Server/World/packetc_info.h"

class Reputation
{
public:
    Reputation();
    void handleFdPacket(PacketFd Packet);
    void handleC_infoPacket(PacketC_info Packet);
    int getReputation() const;
    int getDignity() const;
    ReputationIcon getReputationIcon() const;
    DignityIcon getDignityIcon() const;
    ReputationIcon getDisplayableIcon() const;

private:
    int reputation;
    int dignity;
    ReputationIcon reputationIcon;
    DignityIcon dignityIcon;
};

#endif // REPUTATION_H

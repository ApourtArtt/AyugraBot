#include "reputation.h"

Reputation::Reputation()
{
    reputation = -1;
    dignity = -1;
    reputationIcon = ReputationIcon::BASIC;
    dignityIcon = DignityIcon::BASIC;
}

void Reputation::handleFdPacket(PacketFd Packet)
{
    reputation = Packet.getReputation();
    dignity = Packet.getDignity();
    reputationIcon = Packet.getReputationIcon();
    dignityIcon = Packet.getDignityIcon();
}

void Reputation::handleC_infoPacket(PacketC_info Packet)
{
    reputationIcon = Packet.getReputationIcon();
}

int Reputation::getReputation() const
{
    return reputation;
}

int Reputation::getDignity() const
{
    return dignity;
}

ReputationIcon Reputation::getReputationIcon() const
{
    return reputationIcon;
}

DignityIcon Reputation::getDignityIcon() const
{
    return dignityIcon;
}

ReputationIcon Reputation::getDisplayableIcon() const
{
    if(static_cast<int>(reputationIcon) < 0)
        return reputationIcon;
    if(static_cast<int>(dignityIcon) > 1)
        return static_cast<ReputationIcon>(- static_cast<int>(dignityIcon));
    return reputationIcon;
}

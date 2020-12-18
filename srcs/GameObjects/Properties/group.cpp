#include "group.h"

Group::Group()
{
    pet = nullptr;
    partner = nullptr;
}

Group::~Group()
{
    //if(pet)     delete pet;
    //if(partner) delete partner;
    mates.clear();
}

void Group::handlePinitPacket(PacketPinit packet)
{
    clearGroup();
    groupSize = packet.getGroupSize();
    std::vector<PacketSubPinit> packets = packet.getSubPackets();
    for(size_t i = 0 ; i < packets.size() ; i++)
    {
        PacketSubPinit p = packets[i];
        if(p.getEntityType() == EntityType::PLAYER)
        {
            mates.push_back(new SubEntityGroup(p));
        }
        else if(p.getEntityType() != EntityType::PLAYER && p.isNosmate())
        {
            pet = new SubEntityGroup(p);
        }
        else if(p.getEntityType() != EntityType::PLAYER && p.isPartner())
        {
            partner = new SubEntityGroup(p);
        }
    }
}

bool Group::handleC_modePacket(PacketC_mode packet)
{
    for(int i = 0 ; i < mates.size() ; i++)
    {
        if(mates[i] != nullptr && mates[i]->getEntityID() == packet.getEntityID())
        {
            mates[i]->handleC_modePacket(packet);
            return true;
        }
    }
    return false;
}

short Group::getGroupSize()
{
    return groupSize;
}

SubEntityGroup *Group::getPet()
{
    return pet;
}

SubEntityGroup *Group::getPartner()
{
    return partner;
}

QVector<SubEntityGroup *> Group::getMates()
{
    return mates;
}

void Group::clearGroup()
{
    delete pet;
    delete partner;
    for(int i = 0 ; i < mates.size() ; i++)
        delete mates[i];
    mates.clear();
}


SubEntityGroup::SubEntityGroup(PacketSubPinit packet)
{
    entityType = packet.getEntityType();
    entityID = packet.getEntityID();
    groupPosition = packet.getGroupPosition();
    level = packet.getNormalLevel();
    pseudonym = packet.getPseudonym();
    groupID = packet.getGroupID();
    gender = packet.getGender();
    classChar = packet.getClass();
    morphID = packet.getMorphID();
    levelHero = packet.getHeroLevel();
}

void SubEntityGroup::handleC_modePacket(PacketC_mode packet)
{
    morphID = packet.getMorphID();
}

EntityType SubEntityGroup::getEntityType() const
{
    return entityType;
}

int SubEntityGroup::getEntityID() const
{
    return entityID;
}

short SubEntityGroup::getGroupPosition() const
{
    return groupPosition;
}

short SubEntityGroup::getLevel() const
{
    return level;
}

QString SubEntityGroup::getPseudonym() const
{
    return pseudonym;
}

int SubEntityGroup::getGroupID() const
{
    return groupID;
}

Gender SubEntityGroup::getGender() const
{
    return gender;
}

Class SubEntityGroup::getClass() const
{
    return classChar;
}

int SubEntityGroup::getMorphID() const
{
    return morphID;
}

short SubEntityGroup::getLevelHero() const
{
    return levelHero;
}

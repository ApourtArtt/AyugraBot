#ifndef GROUP_H
#define GROUP_H

#include "srcs/Packets/Server/World/packetpinit.h"
#include "srcs/Packets/Server/World/packetc_mode.h"

class SubEntityGroup
{
public:
    SubEntityGroup(PacketSubPinit packet);
    ~SubEntityGroup() = default;

    void handleC_modePacket(PacketC_mode packet);
    EntityType getEntityType() const;
    int getEntityID() const;
    short getGroupPosition() const;
    short getLevel() const;
    QString getPseudonym() const;
    int getGroupID() const;
    Gender getGender() const;
    Class getClass() const;
    int getMorphID() const;
    short getLevelHero() const;

private:
    EntityType entityType;
    int entityID;
    short groupPosition;
    short level;
    QString pseudonym;
    int groupID;
    Gender gender;
    Class classChar;
    int morphID;
    short levelHero;
};


class Group
{
public:
    Group();
    ~Group();

    void handlePinitPacket(PacketPinit packet);
    bool handleC_modePacket(PacketC_mode packet);
    short getGroupSize();
    SubEntityGroup *getPet();
    SubEntityGroup *getPartner();
    QVector<SubEntityGroup*> getMates();

private:
    void clearGroup();

    short groupSize;
    SubEntityGroup *pet;
    SubEntityGroup *partner;
    QVector<SubEntityGroup*> mates;
};

#endif // GROUP_H

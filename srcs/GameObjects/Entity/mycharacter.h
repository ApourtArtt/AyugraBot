#ifndef MYCHARACTER_H
#define MYCHARACTER_H

#include <memory>
#include <QObject>
#include <QTimer>
#include <QVector>
#include "srcs/Database/databasemap.h"
#include "srcs/Enum/reputationenum.h"
#include "srcs/Packets/Server/World/packetclist.h"
#include "srcs/Packets/Server/World/packetcond.h"
#include "srcs/Packets/Server/World/packetat.h"
#include "srcs/Packets/Client/World/packetu_as.h"
#include "srcs/Packets/Client/World/packetu_s.h"
#include "srcs/Packets/Client/World/packetwalk.h"
#include "srcs/GameObjects/Inventory/inventory.h"
#include "srcs/GameObjects/Properties/level.h"
#include "srcs/GameObjects/Properties/reputation.h"
#include "srcs/GameObjects/Properties/statistics.h"
#include "srcs/GameObjects/Properties/quest.h"
#include "srcs/Utils/Pathfinding/pathfinding.h"
#include "srcs/GameObjects/Properties/skill.h"
#include "srcs/GameObjects/Entity/baseentity.h"
#include "srcs/Packets/Server/World/packetski.h"
#include "srcs/Packets/Server/World/packetcancel.h"
#include "srcs/Packets/Server/World/packetsr.h"
#include "srcs/Packets/Server/World/packetms_c.h"
#include "srcs/Packets/Server/World/packetmslot.h"
#include "srcs/GameObjects/Map/portals.h"
#include "srcs/GameObjects/Map/ts.h"
#include "srcs/Packets/Client/World/packetpreq.h"
#include "srcs/Packets/Client/World/packettreq.h"
#include "srcs/Packets/Client/World/packetwreq.h"
#include "srcs/Packets/Client/World/packetsl.h"
#include "srcs/Packets/Server/World/packetdelay.h"
#include "srcs/Packets/Client/World/packetguri.h"
#include "srcs/GameObjects/Instance/timespaceinstance.h"
#include "srcs/GameObjects/Entity/drop.h"
#include "srcs/Packets/Client/World/packetget.h"
#include "srcs/Packets/Client/World/packetrest.h"

// TODO : Class Family and another class MyFamily deriving from it.
//        The derived class should have the J page into.
// TODO : Add Shop (check if packet = shop before coding it)


enum class CharacterState
{
    RUNNING = 1,
    ATTACKING = 2,
    RESTING = 3,
    WAITING = 4,
    CHANNELING = 5
};

class MyCharacter : public QObject
{
    Q_OBJECT
public:
    MyCharacter(QObject *parent);
    MyCharacter(PacketClist Packet, QObject *parent);
    ~MyCharacter();

    void handleC_infoPacket(PacketC_info Packet);
    void handleAtPacket(PacketAt Packet);
    void handleLevPacket(PacketLev Packet);
    void handleFdPacket(PacketFd Packet);
    void handleStatPacket(PacketStat Packet);
    void handleRsfiPacket(PacketRsfi Packet);
    void handleCondPacket(PacketCond Packet);
    void handleInvPacket(PacketInv Packet);
    void handleIvnPacket(PacketIvn Packet);
    void handleGoldPacket(PacketGold Packet);
    void handleSkiPacket(PacketSki Packet);
    void handleCancelPacket(PacketCancel Packet);
    void handleSrPacket(PacketSr Packet);
    void handleMslotPacket(PacketMslot Packet);
    void handleMs_cPacket(PacketMs_c Packet);
    void handleDelayPacket(PacketDelay Packet);


    Vec2i walk(int posX, int posY, double range = 0, bool wallHack = false);
    void takePortal(Portal portal);
    void goIntoTS(TS ts, bool enter, bool record = false, bool distanceHack = false);
    bool useSkill(Skill *skill, BaseEntity entity, int posX = -1, int posY = -1);
    bool useSkill(Skill *skill, int posX = -1, int posY = -1);
    void toggleSP();
    bool drop(Drop drop, double range = 1.5, bool wallHack = false, bool forceTrying = false);
    void rest(bool sitDown);
    void stopMoving();

    bool isAlive();
    short getSlot() const;
    QString getPseudonym() const;
    Gender getGender() const;
    Authority getAuthority() const;
    int getGroupID() const;
    int getFamilyID() const;
    int getCharacterID() const;
    short getFamilyLevel() const;
    short getMorph() const;
    short getSpUpgrade() const;
    bool isArenaWinner() const;
    bool isInvisible() const;
    HairStyle getHairStyle() const;
    short getHairColor() const;
    Class getClass() const;
    short getSpeed() const;
    bool canAttack() const;
    bool canMove() const;
    const Level getLevelProperties() const;
    const Reputation getReputationProperties() const;
    const Statistics getStatsProperties() const;
    const Quest getQuestProperties() const;
    Inventory *getInventory() const;
    int getX() const;
    int getY() const;
    short getDirection() const;
    QMap<int, Skill*> getSkills() const;
    CharacterState getState() const;
    void setResting(bool Rest);
    PathFinding pf;

    //QString getPetsSkin() const;
    //QString getWornStuff() const;

signals:
    void newSkills(QMap<int, Skill*> Skills);
    void sendPacket(QString packet, bool privilege = false);
    void characterUpdate();
    void inventoryUpdate();
    void onDestination(int x, int y);
    void moved(int x, int y);

private:
    void cancelActionsDelay();
    void cancelWalking();
    QString pseudonym;
    Class characterClass;
    Gender gender;
    Authority authority;
    HairStyle hairStyle;
    short hairColor;
    short slot;
    Reputation reputation;
    Level level;
    Statistics stats;
    Quest quest;
    Inventory *inventory;
    int groupID;
    int familyID;
    int characterID;
    short familyLevel;
    short admiration;
    short morph;
    short spUpgrade;
    bool arenaWinner;
    bool invisible;
    bool rooted;
    bool stunned;
    short direction;

    CharacterState state;

    //PathFinding *pathfinding;
    QVector<QTimer*> actionTimers, walkTimers;
    short speed;
    int x, y;

    QMap<int, Skill*> skills;

    QDateTime lastTimeTriedSitDown;

};

#endif // MYCHARACTER_H

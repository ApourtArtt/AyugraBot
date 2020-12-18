#ifndef MYNOSMATE_H
#define MYNOSMATE_H

#include <QObject>
#include <QTimer>
#include "srcs/GameObjects/Entity/baseentity.h"
#include "srcs/GameObjects/Properties/statistics.h"
#include "srcs/Utils/Pathfinding/pathfinding.h"
#include "srcs/GameObjects/Properties/skill.h"
#include "srcs/Packets/Server/World/packetcond.h"
#include "srcs/Packets/Server/World/packetin.h"
#include "srcs/Packets/Server/World/packetpetsr.h"
#include "srcs/Packets/Server/World/packetpetski.h"
#include "srcs/Packets/Server/World/packetat.h"
#include "srcs/Packets/Client/World/packetsuctl.h"
#include "srcs/Packets/Client/World/packetu_pet.h"
#include "srcs/Packets/Client/World/packetptctl.h"
#include "srcs/Database/databasemap.h"
#include "srcs/Database/databasemonster.h"

enum class NosmateState
{
    RUNNING,
    ATTACKING,
    RESTING,
    WAITING,
    CHANNELING
};

class MyNosmate : public QObject
{
    Q_OBJECT
public:
    MyNosmate(int MapID, QObject *parent);
    void handleAtPacket(PacketAt Packet);
    void handleInPacket(PacketIn23 Packet);
    void handlePetskiPacket(PacketPetski Packet);
    void handlePstPacket(PacketPst Packet);
    void handleCondPacket(PacketCond Packet);
    void handlePetsrPacket(PacketPetsr Packet);

    // suctl 1 1 609445 3 2089
    bool useSkill(Skill *skill, BaseEntity entity);
    bool useSkill(Skill *skill, int x, int y);
    /*
    bool useSkill(Skill *skill, BaseEntity entity, int posX = -1, int posY = -1);
    bool useSkill(Skill *skill, int posX = -1, int posY = -1);*/

    // TODO: Add NoDelay and check on rooted
    Vec2i walk(int posX, int posY, int range, bool wallHack);

    bool isAlive();

    QMap<int, Skill *> getSkills();
    bool canMove() const;
    bool canAttack() const;
    int getNosmateID() const;
    NosmateState getNosmateState() const;
    int getX() const;
    int getY() const;
    int getRange() const;
    int msBetweenTwoAA() const;
    Statistics getStatsProperties() const;

signals:
    void sendPacket(QString packet, bool privilege = false);
    void onDestination(int x, int y);
    void moved(int x, int y);
    void newSkills(QMap<int, Skill*> Skills);

private:
    void cancelActionsDelay();
    void cancelWalking();
    int x;
    int y;

    int mapID;
    int nosmateID;
    bool rooted;
    bool stunned;
    int range;
    int msAuto;
    short speed;
    QString vnum;
    Statistics stats;
    NosmateState state;
    PathFinding pf;
    QMap<int, Skill*> skills;
    QVector<QTimer *> actionTimers, walkTimers;
};

#endif // MYNOSMATE_H

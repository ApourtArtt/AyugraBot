#ifndef MYPARTNER_H
#define MYPARTNER_H

#include <QObject>
#include <QTimer>
#include "srcs/GameObjects/Entity/baseentity.h"
#include "srcs/Utils/Pathfinding/pathfinding.h"
#include "srcs/GameObjects/Properties/skill.h"
#include "srcs/Packets/Server/World/packetat.h"
#include "srcs/Packets/Server/World/packetpdelay.h"
#include "srcs/Packets/Server/World/packetpski.h"
#include "srcs/Packets/Client/World/packetpsl.h"
#include "srcs/Packets/Client/World/packetguri.h"
#include "srcs/Packets/Server/World/packetin.h"
#include "srcs/Packets/Server/World/packetcond.h"
#include "srcs/Packets/Client/World/packetptctl.h"
#include "srcs/Packets/Server/World/packetpsr.h"
#include "srcs/Packets/Server/World/packetpst.h"
#include "srcs/Packets/Client/World/packetsuctl.h"
#include "srcs/Packets/Client/World/packetu_ps.h"
#include "srcs/Packets/Server/World/packetdpski.h"
#include "srcs/GameObjects/Properties/statistics.h"
#include "srcs/Database/databasemap.h"
#include "srcs/Database/databasemonster.h"

enum class PartnerState
{
    RUNNING,
    ATTACKING,
    RESTING,
    WAITING,
    CHANNELING
};

class MyPartner : public QObject
{
    Q_OBJECT
public:
    MyPartner(int MapID, QObject *parent);

    void handleAtPacket(PacketAt Packet);
    void handleInPacket(PacketIn23 Packet);
    void handlePskiPacket(PacketPski Packet);
    void handlePdelayPacket(PacketPdelay Packet);
    void handlePstPacket(PacketPst Packet);
    void handleCondPacket(PacketCond Packet);
    void handlePsrPacket(PacketPsr Packet);
    void handleDpskiPacket(PacketDpski Packet);

    void toggleSP();
    bool useSkill(Skill *skill, BaseEntity entity);
    bool useSkill(Skill *skill, int x, int y);

    // TODO: Add NoDelay and check on rooted
    Vec2i walk(int posX, int posY, int range, bool wallHack);

    bool isAlive();

    QMap<int, Skill *> getSkills();
    bool canMove() const;
    bool canAttack() const;
    int getPartnerID() const;
    PartnerState getPartnerState() const;
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

    int characterID;
    int partnerID;
    int x;
    int y;
    int mapID;
    bool rooted;
    bool stunned;
    int range;
    int msAuto;
    short speed;
    QString vnum;
    Statistics stats;
    PartnerState state;
    PathFinding pf;
    QMap<int, Skill*> skills;
    QVector<QTimer *> actionTimers, walkTimers;
};

#endif // MYPARTNER_H

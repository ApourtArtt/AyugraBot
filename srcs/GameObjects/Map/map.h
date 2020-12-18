#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QTimer>
#include "srcs/Database/databasemap.h"
#include "srcs/GameObjects/Entity/drop.h"
#include "srcs/GameObjects/Entity/monster.h"
#include "srcs/GameObjects/Entity/nosmate.h"
#include "srcs/GameObjects/Entity/npc.h"
#include "srcs/GameObjects/Entity/player.h"
#include "srcs/GameObjects/Map/portals.h"
#include "srcs/GameObjects/Map/ts.h"
#include "srcs/Packets/Server/World/packetat.h"
#include "srcs/Packets/Server/World/packetc_map.h"
#include "srcs/Packets/Server/World/packetdie.h"
#include "srcs/Packets/Server/World/packetgetr.h"
#include "srcs/Packets/Server/World/packetin.h"
#include "srcs/Packets/Server/World/packetmv.h"
#include "srcs/Packets/Server/World/packetout.h"
#include "srcs/Packets/Server/World/packetsu.h"
#include "srcs/Packets/Server/World/packeteff.h"
#include "srcs/Packets/Server/World/packetrestr.h"

class Map : public QObject
{
    Q_OBJECT
public:
    // Packet shop à add
    Map(QObject *parent);
    void handleAtPacket(PacketAt Packet);
    void handleC_mapPacket(PacketC_map Packet);
    void handleWpPacket(PacketWp Packet);
    void handleGpPacket(PacketGp Packet);
    void handleInPacket(BasePacketIn Packet);
    void handleDropPacket(PacketDrop Packet);
    void handleGetPacket(PacketGetR Packet);
    void handleOutPacket(PacketOut Packet);
    void handleDiePacket(PacketDie Packet);
    void handleMvPacket(PacketMv Packet);
    void handleShopPacket(PacketShop Packet);
    void handleSuPacket(PacketSu Packet);
    void handleEffPacket(PacketEff Packet);
    void handleRestPacket(PacketRestR Packet);

    QMap<int, Portal> getPortalList() const;
    QMap<int, TS> getTSList() const;
    QMap<int, Monster> getMonsterList() const;
    QMap<int, Drop> getDropList() const;
    QMap<int, Player> getPlayerList() const;
    QMap<int, NPC> getNPCList() const;
    QMap<int, Nosmate> getNosmateList() const;
    QList<int> getMonsterUniqueVnum();
    int getMapID() const;
    int getMusicID() const;
    int getLastMapID() const;
    QString getMapName() const;
    QString getMapNameId() const;
    WorldMap getWorldMapSide() const;
    MiniMapType getMinimapType() const;
    int getMinimapPoint() const;
    QSize getWorldSize() const;
    QList<int> getMapItemsID() const;
    QMap<int, Monster> getAgroedMonsters();

signals:
    void mapUpdate();
    void mapChanged();
    void mapInOut();
    void newPlayer(Player player);

private:
    int characterID, partnerID, nosmateID;
    QMap<int, Monster> agroedMonsters;
    QMap<int, QTimer*> agroedMonstersTimers;

    int mapID;
    int lastMapID;
    int musicID;
    QMap<int, Drop> drops;
    QMap<int, Portal> portals;
    QMap<int, TS> ts;
    QMap<int, Monster> monsters;
    QMap<int, Player> players;
    QMap<int, NPC> npcs;
    QMap<int, Nosmate> nosmates;
    QList<int> monsterUniqueVnum;
    MapFromDb mapDb;

    const int AGRO_TIMER = 15000; // 15s
};

#endif // MAP_H

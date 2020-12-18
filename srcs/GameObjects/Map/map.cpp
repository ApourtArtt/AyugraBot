#include "map.h"
#include <QDebug>

Map::Map(QObject *parent)
    : QObject(parent)
{
    mapID = -1;
    musicID = -1;
    lastMapID = -1;
    characterID = -1;
    partnerID = -1;
    nosmateID = -1;
}

void Map::handleAtPacket(PacketAt Packet)
{
    characterID = Packet.getCharacterID();
    nosmateID = -1;
    partnerID = -1;
    monsters.clear();
    drops.clear();
    nosmates.clear();
    npcs.clear();
    players.clear();
    ts.clear();
    portals.clear();
    agroedMonsters.clear();
    agroedMonstersTimers.clear();
    monsterUniqueVnum.clear();
    mapID = Packet.getMapID();
    musicID = Packet.getMusicID();
    mapDb = DatabaseMap::getMapProperties(mapID);
    emit mapChanged();
}

void Map::handleC_mapPacket(PacketC_map Packet)
{
    if(!Packet.isGoingTo())
        lastMapID = Packet.getMapID();
}

void Map::handleWpPacket(PacketWp Packet)
{
    if(ts.contains(Packet.getID()))
        ts[Packet.getID()].handleWpPacket(Packet);
    else
        ts.insert(Packet.getID(), TS(Packet));
    emit mapUpdate();
}

void Map::handleGpPacket(PacketGp Packet)
{
    if(portals.contains(Packet.getID()))
        portals[Packet.getID()].handleGpPacket(Packet);
    else
        portals.insert(Packet.getID(), Portal(Packet));
    emit mapUpdate();
}

// Add check if not exist
void Map::handleInPacket(BasePacketIn Packet)
{
    EntityType type = Packet.getEntityType();
    if(type == EntityType::DROP)
        drops.insert(Packet.getID(), Drop(PacketIn9(Packet.getPacketsPart())));
    else if(type == EntityType::PLAYER)
    {
        players.insert(Packet.getID(), Player(PacketIn1(Packet.getPacketsPart())));
        emit newPlayer(players[Packet.getID()]);
    }
    else if(type == EntityType::NOSMATE_NPC)
    {
        PacketIn23 packet(Packet.getPacketsPart());
        if(packet.getOwnerID() == -1)
            npcs.insert(packet.getID(), NPC(packet));
        else
        {
            nosmates.insert(packet.getID(), Nosmate(packet));
            if(packet.getOwnerID() == characterID)
            {
                if(packet.isPartner())
                    partnerID = packet.getID();
                else
                    nosmateID = packet.getID();
            }
        }
    }
    else if(type == EntityType::MONSTER)
    {
        monsters.insert(Packet.getID(), Monster(Packet.getPacketsPart()));
        if(!monsterUniqueVnum.contains(Packet.getName().toInt()))
            monsterUniqueVnum.push_back(Packet.getName().toInt());
    }
    emit mapUpdate();
    emit mapInOut();
}

void Map::handleDropPacket(PacketDrop Packet)
{
    drops.insert(Packet.getID(), Drop(Packet));
    emit mapUpdate();
}

void Map::handleGetPacket(PacketGetR Packet)
{
    drops.remove(Packet.getDropID());
    emit mapUpdate();
}

void Map::handleOutPacket(PacketOut Packet)
{
    EntityType type = Packet.getEntityType();
    if(type == EntityType::DROP)
        drops.remove(Packet.getID());
    else if(type == EntityType::PLAYER)
        players.remove(Packet.getID());
    else if(type == EntityType::NOSMATE_NPC)
    {
        nosmates.remove(Packet.getID());
        npcs.remove(Packet.getID());
    }
    else if(type == EntityType::MONSTER)
    {
        monsters.remove(Packet.getID());
        agroedMonsters.remove(Packet.getID());
        agroedMonstersTimers.remove(Packet.getID());
    }
    emit mapUpdate();
    emit mapInOut();
}

void Map::handleDiePacket(PacketDie Packet)
{
    EntityType type = Packet.getEntityType();
    if(type == EntityType::DROP)
        drops.remove(Packet.getID());
    else if(type == EntityType::PLAYER)
        players.remove(Packet.getID());
    else if(type == EntityType::NOSMATE_NPC)
    {
        nosmates.remove(Packet.getID());
        npcs.remove(Packet.getID());
    }
    else if(type == EntityType::MONSTER)
    {
        monsters.remove(Packet.getID());
        agroedMonsters.remove(Packet.getID());
        agroedMonstersTimers.remove(Packet.getID());
    }
    emit mapUpdate();
}

void Map::handleMvPacket(PacketMv Packet)
{
    EntityType type = Packet.getEntityType();
    if(type == EntityType::DROP && drops.contains(Packet.getID()))
        drops[Packet.getID()].handleMvPacket(Packet);
    else if(type == EntityType::PLAYER && players.contains(Packet.getID()))
        players[Packet.getID()].handleMvPacket(Packet);
    else if(type == EntityType::NOSMATE_NPC)
    {
        if(npcs.contains(Packet.getID()))
            npcs[Packet.getID()].handleMvPacket(Packet);
        else if(nosmates.contains(Packet.getID()))
            nosmates[Packet.getID()].handleMvPacket(Packet);
    }
    else if(type == EntityType::MONSTER && monsters.contains(Packet.getID()))
        monsters[Packet.getID()].handleMvPacket(Packet);
}

void Map::handleShopPacket(PacketShop Packet)
{
    EntityType type = Packet.getEntityType();
    if(type == EntityType::PLAYER && players.contains(Packet.getSellerID()))
        players[Packet.getSellerID()].handleShopPacket(Packet);
    else if(type == EntityType::NOSMATE_NPC && npcs.contains(Packet.getSellerID()))
        npcs[Packet.getSellerID()].handleShopPacket(Packet);
    emit mapUpdate();
}

void Map::handleSuPacket(PacketSu Packet)
{
    EntityType type = Packet.getTargetEntityType();
    if(type == EntityType::PLAYER && (players.contains(Packet.getTargetID()) || Packet.getTargetID() == characterID))
    {
        if(Packet.isTargetStillAlive())
        {
            if(players.contains(Packet.getTargetID()))
                players[Packet.getTargetID()].handleSuPacket(Packet);
            if(Packet.getTargetID() == characterID && monsters.contains(Packet.getLauncherID()))
            {
                if(!agroedMonsters.contains(Packet.getLauncherID()))
                {
                    agroedMonsters.insert(Packet.getLauncherID(), monsters[Packet.getLauncherID()]);
                    QTimer *tmp = new QTimer(this);
                    agroedMonstersTimers.insert(Packet.getLauncherID(), tmp);
                    connect(tmp, &QTimer::timeout, [=]() mutable
                    {
                        agroedMonsters.remove(Packet.getLauncherID());
                        agroedMonstersTimers.remove(Packet.getLauncherID());
                        delete tmp;
                    });
                }
                agroedMonstersTimers[Packet.getLauncherID()]->start(AGRO_TIMER);
            }
        }
        else
            players.remove(Packet.getTargetID());
        // should I removed the mob who killed me on agro list ? idk, need some tests
        // official delete the agro on player, but have 3 agro list
        // I have only one, maybe will do 3 if needed later
    }
    else if(type == EntityType::NOSMATE_NPC)
    {
        if(npcs.contains(Packet.getTargetID()))
        {
            if(Packet.isTargetStillAlive())
                npcs[Packet.getTargetID()].handleSuPacket(Packet);
            else
                npcs.remove(Packet.getTargetID());
        }
        else if(nosmates.contains(Packet.getTargetID()))
        {
            if(Packet.isTargetStillAlive())
            {
                nosmates[Packet.getTargetID()].handleSuPacket(Packet);
                if((Packet.getTargetID() == partnerID || Packet.getTargetID() == nosmateID) && monsters.contains(Packet.getLauncherID()))
                {
                    if(!agroedMonsters.contains(Packet.getLauncherID()))
                    {
                        agroedMonsters.insert(Packet.getLauncherID(), monsters[Packet.getLauncherID()]);
                        QTimer *tmp = new QTimer(this);
                        agroedMonstersTimers.insert(Packet.getLauncherID(), tmp);
                        connect(tmp, &QTimer::timeout, [=]() mutable
                        {
                            agroedMonsters.remove(Packet.getLauncherID());
                            agroedMonstersTimers.remove(Packet.getLauncherID());
                            delete tmp;
                        });
                    }
                    agroedMonstersTimers[Packet.getLauncherID()]->start(AGRO_TIMER);
                }
            }
            else
                nosmates.remove(Packet.getTargetID());
        }
    }
    else if(type == EntityType::MONSTER && monsters.contains(Packet.getTargetID()))
    {
        if(Packet.isTargetStillAlive())
        {
            monsters[Packet.getTargetID()].handleSuPacket(Packet);
            if(Packet.getLauncherID() == characterID || Packet.getLauncherID() == nosmateID || Packet.getLauncherID() == partnerID)
            {
                if(!agroedMonsters.contains(Packet.getTargetID()))
                {
                    agroedMonsters.insert(Packet.getTargetID(), monsters[Packet.getTargetID()]);
                    QTimer *tmp = new QTimer(this);
                    agroedMonstersTimers.insert(Packet.getTargetID(), tmp);
                    connect(tmp, &QTimer::timeout, [=]() mutable
                    {
                        agroedMonsters.remove(Packet.getTargetID());
                        agroedMonstersTimers.remove(Packet.getTargetID());
                        delete tmp;
                    });
                }
                agroedMonstersTimers[Packet.getTargetID()]->start(AGRO_TIMER);
            }
        }
        else
        {
            monsters.remove(Packet.getTargetID());
            agroedMonsters.remove(Packet.getTargetID());
            agroedMonstersTimers.remove(Packet.getTargetID());
        }
    }
    emit mapUpdate();
}

void Map::handleEffPacket(PacketEff Packet)
{
    if(Packet.getEmoteID() == 5000 && Packet.getEntityType() == EntityType::MONSTER)
    {
        if(!agroedMonsters.contains(Packet.getEntityID()))
        {
            agroedMonsters.insert(Packet.getEntityID(), monsters[Packet.getEntityID()]);
            QTimer *tmp = new QTimer(this);
            agroedMonstersTimers.insert(Packet.getEntityID(), tmp);
            connect(tmp, &QTimer::timeout, [=]() mutable
            {
                agroedMonsters.remove(Packet.getEntityID());
                agroedMonstersTimers.remove(Packet.getEntityID());
                delete tmp;
            });
            tmp->start(AGRO_TIMER);
        }
    }
}

void Map::handleRestPacket(PacketRestR Packet)
{
    // There is no use coding it for now
    // This is the packet handling if players/monsters/... are resting or not
}

QMap<int, Portal> Map::getPortalList() const
{
    return portals;
}

QMap<int, TS> Map::getTSList() const
{
    return ts;
}

QMap<int, Monster> Map::getMonsterList() const
{
    return monsters;
}

QMap<int, Drop> Map::getDropList() const
{
    return drops;
}

QMap<int, Player> Map::getPlayerList() const
{
    return players;
}

QMap<int, NPC> Map::getNPCList() const
{
    return npcs;
}

QMap<int, Nosmate> Map::getNosmateList() const
{
    return nosmates;
}

QList<int> Map::getMonsterUniqueVnum()
{
    return monsterUniqueVnum;
}

int Map::getMapID() const
{
    return mapID;
}

int Map::getMusicID() const
{
    return musicID;
}

int Map::getLastMapID() const
{
    return lastMapID;
}

QString Map::getMapName() const
{
    return mapDb.getName();
}

QString Map::getMapNameId() const
{
    return mapDb.getNameId();
}

WorldMap Map::getWorldMapSide() const
{
    return mapDb.getWorldMapSide();
}

MiniMapType Map::getMinimapType() const
{
    return mapDb.getMinimapType();
}

int Map::getMinimapPoint() const
{
    return mapDb.getMinimapPoint();
}

QSize Map::getWorldSize() const
{
    return mapDb.getWorldSize();
}

QList<int> Map::getMapItemsID() const
{
    return DatabaseMap::getMapItemsID(mapID);
}

QMap<int, Monster> Map::getAgroedMonsters()
{
    return agroedMonsters;
}

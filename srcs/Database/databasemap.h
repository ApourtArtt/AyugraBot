#ifndef DATABASEMAP_H
#define DATABASEMAP_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>
#include <QMap>
#include <QImage>
#include "srcs/Enum/mapenum.h"

/*
[MapID] [MapID] [WorldMapSide] [PointWorldMap] [NameID]
DATA [Act : 1=Act5 2=Act6 3=Act7 0=Default]
*/

class MapFromDb
{
public:
    MapFromDb();
    MapFromDb(QStringList data, int Id);
    QString getName() const;
    QString getNameId() const;
    int getID() const;
    WorldMap getWorldMapSide() const;
    MiniMapType getMinimapType() const;
    int getMinimapPoint() const;
    QSize getWorldSize() const;

protected:
    int id;
    WorldMap side;
    int miniMapPoint;
    QString nameID, name;
    MiniMapType minimapType;
};

class DatabaseMap
{
public:
    DatabaseMap();
    static bool loadMap();
    static QStringList getMapObstacle(int id);
    static QSize getWorldSize(int id);
    static QString getMapName(QString nameID);
    static MapFromDb getMapProperties(int id);
    static bool isLoaded();
    static QList<int> getMapItemsID(int mapID);
    static QList<int> getUniqueMapItemsID();

private:
    static bool loadMapDat();
    static bool load_code__MapIDDataTxt();
    static bool loadMapItemID();
    static QMap<int, QList<int>> mapItems;
    static QMap<int, MapFromDb> maps;
    static QMap<QString, QString> mapName;
    static QList<int> uniqueDropableItemsID;
    static bool loaded;
};

#endif // DATABASEMAP_H

#include "databasemap.h"

QMap<int, MapFromDb>    DatabaseMap::maps;
QMap<int, QList<int>>   DatabaseMap::mapItems;
QList<int>              DatabaseMap::uniqueDropableItemsID;
QMap<QString, QString>  DatabaseMap::mapName;
bool                    DatabaseMap::loaded = false;

MapFromDb::MapFromDb()
{

}

MapFromDb::MapFromDb(QStringList data, int Id)
{
    id = Id;
    side = static_cast<WorldMap>(data[2].toInt());
    miniMapPoint = data[3].toInt();
    nameID = data[4];
    name = DatabaseMap::getMapName(nameID);
    minimapType = static_cast<MiniMapType>(data[6].toInt());
}

QString MapFromDb::getName() const
{
    return name;
}

QString MapFromDb::getNameId() const
{
    return nameID;
}

int MapFromDb::getID() const
{
    return id;
}

WorldMap MapFromDb::getWorldMapSide() const
{
    return side;
}

MiniMapType MapFromDb::getMinimapType() const
{
    return minimapType;
}

int MapFromDb::getMinimapPoint() const
{
    return miniMapPoint;
}

QSize MapFromDb::getWorldSize() const
{
    return DatabaseMap::getWorldSize(id);
}



DatabaseMap::DatabaseMap()
{

}

bool DatabaseMap::loadMap()
{
    if(!load_code__MapIDDataTxt())
        return false;
    if(!loadMapDat())
        return false;
    if(!loadMapItemID())
        return false;
    loaded = true;
    return true;
}
#include <QDebug>
QStringList DatabaseMap::getMapObstacle(int id)
{
    QString dir = "data/mappath/";
    QImage image;
    if(!image.load(dir + QString::number(id) + ".png"))
        return {};
    QString predata;
    for(int i = 0 ; i < image.height() ; i = i + 2)
    {
        for(int j = 0 ; j < image.width() ; j = j + 2)
        {
            predata.append(image.pixelColor(j, i) == QColor(255, 255, 255) ? "1" : "0");
        }
        predata.append("\n");
    }
    return predata.split("\n", QString::SkipEmptyParts);
}

QSize DatabaseMap::getWorldSize(int id)
{
    QString dir = "data/mappath/";
    QImage image;
    if(!image.load(dir + QString::number(id) + ".png"))
        return QSize(0, 0);
    return image.size();
}

bool DatabaseMap::loadMapDat()
{
    QString filePath = "MapIDData.dat";
    QString data;
    QFile readFile("data/" + filePath);
    if(!readFile.open(QFile::ReadOnly | QFile::Text))
        return false;
    QTextStream in(&readFile);
    in.setCodec("UTF-8");
    data = in.readAll();
    for(int i = 0 ; i < 4 ; i++)
    {
        data.replace("DATA " + QString::number(i), " DATA " + QString::number(i) + " ");
    }
    QStringList dataSpace = data.split(" ", QString::SkipEmptyParts);
    dataSpace.erase(dataSpace.begin(), dataSpace.begin() + 5); // Remove korean things
    dataSpace[0].remove(0, 5); // Remove korean things
    for(int j = 0 ; j < dataSpace.size() / 7 ; j++)
    {
        QStringList datas;
        for(int i = 0 ; i < 7 ; i++)
            datas << dataSpace[j * 7 + i];
        for(int k = datas[0].toInt() ; k <= datas[1].toInt() ; k++)
            maps.insert(k, MapFromDb(datas, k));
    }
    return true;
}

bool DatabaseMap::load_code__MapIDDataTxt()
{
    QString filePath = "_code_fr_MapIDData.txt";
    QString data;
    QFile readFile("data/" + filePath);
    if(!readFile.open(QFile::ReadOnly | QFile::Text))
        return false;
    QTextStream in(&readFile);
    in.setCodec("UTF-8");
    data = readFile.readAll().replace("zts", "\tzts");
    QStringList datas = data.split("\t", QString::SkipEmptyParts);
    for(int i = 0 ; i < datas.size() - 1; i = i + 2)
        mapName.insert(datas[i], datas[i + 1]);
    return true;
}

bool DatabaseMap::loadMapItemID()
{
    QString filePath = "MapItem.txt";
    QString data;
    QFile readFile("data/" + filePath);
    if(!readFile.open(QFile::ReadOnly | QFile::Text))
        return false;
    data = readFile.readAll();
    QStringList datas = data.split("\n", QString::SkipEmptyParts);
    QList<int> mID, iID;
    for(int i = 0 ; i < datas.size() ; i++)
    {
        if(i % 2 == 0)
        {
            QStringList mIDString = datas[i].split(" ");
            mID.clear();
            for(int j = 0 ; j < mIDString.size() ; j++)
                mID.push_back(mIDString[j].toInt());
        }
        else
        {
            QStringList iIDString = datas[i].split(" ");
            iID.clear();
            for(int j = 0 ; j < iIDString.size() ; j++)
            {
                int id = iIDString[j].toInt();
                iID.push_back(id);
                if(!uniqueDropableItemsID.contains(id))
                    uniqueDropableItemsID.push_back(id);
            }
            for(int j = 0 ; j < mID.size() ; j++)
                mapItems.insert(mID[j], iID);
        }
    }
    return true;
}

QString DatabaseMap::getMapName(QString nameID)
{
    return mapName.value(nameID);
}

MapFromDb DatabaseMap::getMapProperties(int id)
{
    return maps.value(id);
}

bool DatabaseMap::isLoaded()
{
    return loaded;
}

QList<int> DatabaseMap::getMapItemsID(int mapID)
{
    return mapItems[mapID];
}

QList<int> DatabaseMap::getUniqueMapItemsID()
{
    return uniqueDropableItemsID;
}

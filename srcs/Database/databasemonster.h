#ifndef DATABASEMONSTER_H
#define DATABASEMONSTER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>
#include <QMap>

class MonsterFromDb
{
public:
    MonsterFromDb(){}
    MonsterFromDb(int Vnum);
    MonsterFromDb(QStringList index);
    int getVnum() const                       { return vnum; }
    QString getName() const                   { return name; }
    QString getNameZts() const                { return nameZts; }
    QString getImage() const                  { return imageID + ".png"; }
    int getRange() const                      { return range; }
    int getMsBasicAuto() const                { return msAuto; }
    int getLevel() const                      { return level; }
    QList<int> getDropableItemsID() const     { return dropableItemsID; }

protected:
    void getDataFromVnum(int vnum);
    QStringList datas;
    int vnum;
    QString imageID;
    QString nameZts, name;
    int range;
    int msAuto;
    int level;
    QList<int> dropableItemsID;
};

class DatabaseMonster
{
public:
    DatabaseMonster();
    static bool loadMonster();
    static QString getMonsterNameFromID(int id);
    static QString getMonsterImageIDFromID(int id);
    static MonsterFromDb getMonsterProperties(int id);
    static QMap<int, MonsterFromDb> GetMonsters();
    static QString getMonsterDatAtIndex(int id, int index);

private:
    static bool loadMonsterDat();
    static bool load_code__monsterTxt();
    static QString get_code__monsterTxtFromZts(QString zts);
    static QStringList MonsterDat;
    static QStringList _code__monsterTxt;
    static int argByMonster;
    static QMap<int, MonsterFromDb> monsters;
};

#endif // DATABASEMONSTER_H

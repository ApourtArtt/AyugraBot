#include "databasemonster.h"
#include <QDebug>

QStringList                 DatabaseMonster::MonsterDat;
QStringList                 DatabaseMonster::_code__monsterTxt;
int                         DatabaseMonster::argByMonster;
QMap<int, MonsterFromDb>    DatabaseMonster::monsters;

MonsterFromDb::MonsterFromDb(int Vnum)
{
    vnum = Vnum;
    getDataFromVnum(vnum);
}

MonsterFromDb::MonsterFromDb(QStringList index)
{
    datas = index;
    vnum = index[2].toInt();
    nameZts = index[4];
    level = index[6].toInt();
    range = index[56].toInt();
    msAuto = index[57].toInt() * 100;
    name = DatabaseMonster::getMonsterNameFromID(vnum);
    imageID = DatabaseMonster::getMonsterImageIDFromID(vnum);
    for(int i = 226 ; i <= 287 ; i = i + 3)
    {
        int dt = DatabaseMonster::getMonsterDatAtIndex(vnum, i).toInt();
        if(dt == -1)
            break;
        dropableItemsID.push_back(dt);
    }
}

void MonsterFromDb::getDataFromVnum(int Vnum)
{
    vnum = Vnum;
    MonsterFromDb tmp = DatabaseMonster::getMonsterProperties(vnum);
    datas = tmp.datas;
    imageID = tmp.imageID;
    nameZts = tmp.nameZts;
    name = tmp.name;
    level = tmp.level;
    range = tmp.range;
    msAuto = tmp.msAuto;
    dropableItemsID = tmp.dropableItemsID;
}




DatabaseMonster::DatabaseMonster()
{

}

bool DatabaseMonster::loadMonster()
{
    if(!load_code__monsterTxt())
        return false;
    if(!loadMonsterDat())
        return false;
    return true;
}

QString DatabaseMonster::getMonsterNameFromID(int id)
{
    if(id < 0)
        return nullptr;
    QString zts = getMonsterDatAtIndex(id, 4);
    return get_code__monsterTxtFromZts(zts);
}

MonsterFromDb DatabaseMonster::getMonsterProperties(int id)
{
    return monsters[id];
}

QMap<int, MonsterFromDb> DatabaseMonster::GetMonsters()
{
    return monsters;
}

QString DatabaseMonster::getMonsterImageIDFromID(int id)
{
    if(id < 0)
        return nullptr;
    return QString::number(getMonsterDatAtIndex(id, 30).toInt()+8000);
}

bool DatabaseMonster::loadMonsterDat()
{
    QString filePath = "monster.dat";
    QString del = "#========================================================";
    QString data;
    QFile readFile("data/" + filePath);
    if(!readFile.open(QFile::ReadOnly | QFile::Text))
        return false;
    QTextStream in(&readFile);
    in.setCodec("UTF-8");
    data = in.readAll();
    data.replace(del + del, "\t" + del);
    data.replace(del + "~", "\t" + del);
    MonsterDat = data.split("\t", QString::SkipEmptyParts);
    int i2 = 0;
    for(int i = 0 ; i < MonsterDat.size() ; i++)
    {
        if(MonsterDat[i] == del)
        {
            if(argByMonster != i - i2)
            {
                if(argByMonster != 0)
                {
                    return false;
                }
                argByMonster = i - i2;
            }
            i2 = i;
        }
    }
    int j = 0;
    for(int i = 0 ; i < MonsterDat.size() - 1 ; i++)
    {
        QStringList tmp;
        for( ; j < argByMonster * (i+1) ; j++)
        {
            if(j < MonsterDat.size())
            tmp.push_back(MonsterDat[j]);
        }
        if(tmp.size() == argByMonster)
        {
            monsters[tmp[2].toInt()] = MonsterFromDb(tmp);
        }
    }
    readFile.close();
    return true;
}

bool DatabaseMonster::load_code__monsterTxt()
{
    QString filePath = "_code_fr_monster.txt";
    QString data;
    QFile readFile("data/" + filePath);
    if(!readFile.open(QFile::ReadOnly | QFile::Text))
        return false;
    QTextStream in(&readFile);
    in.setCodec("UTF-8");
    data = in.readAll();
    data.replace("zts", "\tzts");
    _code__monsterTxt = data.split("\t");
    if(!_code__monsterTxt.at(0).startsWith("zts"))
        _code__monsterTxt.removeFirst();
    readFile.close();
    return true;
}

/* Monster.dat function parsing
 * 2  : VNUM
 * 4  : Name's identifier (ztsXXXXXe)
 * 6  : Level
 * 30 : Image ID
 * 56 : Range
 * 57 : Time between 2 AA
 * 228 : First item ID
*/

QString DatabaseMonster::getMonsterDatAtIndex(int id, int index)
{
    QString idString = QString::number(id);
    for(int i = 0 ; i < MonsterDat.size() - argByMonster ; i = i + argByMonster)
    {
        if(MonsterDat[i+2] == idString)
        {
            return MonsterDat[i+index];
        }
    }
    return nullptr;
}

/* _code_XX_Item.txt function parsing
 * 0 : Monster name identifier (ztsXXXXXe)
 * 1 : Monster name
*/

QString DatabaseMonster::get_code__monsterTxtFromZts(QString zts)
{
    for(int i = 0 ; i < _code__monsterTxt.size() ; i = i + 2)
        if(_code__monsterTxt[i] == zts)
            return _code__monsterTxt[i+1];
    return nullptr;
}

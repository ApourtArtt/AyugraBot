#include "databaseskill.h"
#include <QDebug>

QStringList            DatabaseSkill::SkillDat;
QStringList            DatabaseSkill::_code__SkillTxt;
QMap<int, SkillFromDb> DatabaseSkill::skills;

SkillFromDb::SkillFromDb(int Id)
{
    loadData(DatabaseSkill::getSkillFromId(Id).getData());
    qDebug() << DatabaseSkill::getSkillFromId(Id).getData();
}

SkillFromDb::SkillFromDb(QStringList data)
{
    loadData(data);
    //qDebug()<< datas[170] << datas[169] << datas.size();

    //qDebug() << "ID : " << id << " - " << desc << descZts;
/* 3  ("VNUM", "1", "NAME", "zts1e",
 * 10 "TYPE", "0:Livre", "CastId", "0", "5:Dash", "0", "0",
 * 14 "COST", "0", "0", "0",
 * 20 "LEVEL", "0", "0", "0", "0", "0",
 * 30 "EFFECT", "IMAGE", "0", "14", "0", "11", "0", "0", "0", "0",
 * 36 "TARGET", "0", "0", "Range", "0", "0",
 * 52 "DATA", "0", "0", "0", "0", "AnimationTime 42", "cooldown * 10", "0", "0", "ManaCost 46", "0", "0", "0", "0", "0", "0",
 * ?? "BASIC", "0", "0", "0", "0", "0", "0",
 * ?? "BASIC", "1", "0", "0", "0", "0", "0",
 * ?? "BASIC", "2", "0", "0", "0", "0", "0",
 * ?? "BASIC", "3", "0", "0", "0", "0", "0",
 * ?? "BASIC", "4", "0", "0", "0", "0", "0",
 * ??? "FCOMBO", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
 * 168 "CELL", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0"
 * 170 "Z_DESC", "0",
 * ZTS here if Z_desc > 0)*/
}

void SkillFromDb::loadData(QStringList data)
{
    datas = data;
    id = data[1].toInt();
    nameZts = data[3];
    name = DatabaseSkill::getSkillTextFromZts(nameZts);
    type = static_cast<SkillType>(data[5].toInt());
    castId = data[6].toInt();
    dash = data[8].toInt() == 5 ? true : false;
    combo = data[14].toInt() == 999 ? true : false;
    imageId = data[22].toInt();
    targetType = static_cast<SkillTarget>(data[32].toInt());
    range = data[34].toInt();
    animationTime = data[42].toInt() * 100;
    cooldown = data[43].toInt() * 100;
    manaCost = data[46].toInt();
    nbLineDesc = datas[170].toInt();
    for(int i = 0 ; i < nbLineDesc ; i++)
    {
        if(171 + i < datas.size())
        {
            descZts.append(datas[171 + i]);
            desc.append(DatabaseSkill::getSkillTextFromZts(descZts[i]));
        }
    }
}

QStringList SkillFromDb::getData() const
{
    return datas;
}

int SkillFromDb::getID() const
{
    return id;
}

QString SkillFromDb::getName() const
{
    return name;
}

QString SkillFromDb::getNameID() const
{
    return nameZts;
}

QString SkillFromDb::getImage() const
{
    return QString::number(imageId) + ".png";
}

int SkillFromDb::getCooldown() const
{
    return cooldown;
}

QStringList SkillFromDb::getDescription() const
{
    return desc;
}

QStringList SkillFromDb::getDescriptionID() const
{
    return descZts;
}

bool SkillFromDb::isDash() const
{
    return dash;
}

bool SkillFromDb::isCombo() const
{
    return combo;
}

int SkillFromDb::getCastID() const
{
    return castId;
}

SkillTarget SkillFromDb::getSkillTarget() const
{
    return targetType;
}

SkillType SkillFromDb::getSkillType() const
{
    return type;
}

int SkillFromDb::getRange() const
{
    return range;
}

int SkillFromDb::getManaCost() const
{
    return manaCost;
}

int SkillFromDb::getAnimationTimeMs() const
{
    return animationTime;
}




DatabaseSkill::DatabaseSkill()
{

}

bool DatabaseSkill::loadSkill()
{
    if(!load_code__SkillTxt())
        return false;
    if(!loadSkillDat())
        return false;
    return true;
}

bool DatabaseSkill::loadSkillDat()
{
    QString filePath = "Skill.dat";
    QString del = "#=========================================================";
    QString data;
    QFile readFile("data/" + filePath);
    if(!readFile.open(QFile::ReadOnly | QFile::Text))
        return false;
    QTextStream in(&readFile);
    in.setCodec("UTF-8");
    data = in.readAll();
    data.replace("\tzts", "\tzt_s");
    data.replace("zts", "\tzts");
    data.replace("zt_s", "zts");
    SkillDat = data.split("\t", QString::SkipEmptyParts);
    QStringList tmp;
    for(int i = 0 ; i < SkillDat.size() - 1 ; i++)
    {
        tmp.push_back(SkillDat[i]);
        if(SkillDat[i].contains(del))
        {
            tmp[tmp.size()-1].remove(del);
            //qDebug() << tmp;
            skills[tmp[1].toInt()] = SkillFromDb(tmp);
            tmp.clear();
        }
    }
    return true;
}

/* _code_XX_Skill.txt function parsing
 * 0 : Name or description identifier (ztsXXXXXe)
 * 1 : Skill name or description
*/

bool DatabaseSkill::load_code__SkillTxt()
{
    QString filePath = "_code_fr_Skill.txt";
    QString data;
    QFile readFile("data/" + filePath);
    if(!readFile.open(QFile::ReadOnly | QFile::Text))
        return false;
    QTextStream in(&readFile);
    in.setCodec("UTF-8");
    data = in.readAll();
    data.replace("zts", "\tzts");
    _code__SkillTxt = data.split("\t");
    if(!_code__SkillTxt.at(0).startsWith("zts"))
        _code__SkillTxt.removeFirst();
    readFile.close();
    return true;
}

QString DatabaseSkill::getSkillTextFromZts(QString zts)
{
    for(int i = 0 ; i < _code__SkillTxt.size() - 1 ; i++)
    {
        if(_code__SkillTxt[i] == zts)
            return _code__SkillTxt[i+1];
    }
    return nullptr;
}

SkillFromDb DatabaseSkill::getSkillFromId(int id)
{
    return skills.value(id);
}

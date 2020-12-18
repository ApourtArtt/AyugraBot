#ifndef DATABASESKILL_H
#define DATABASESKILL_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>
#include <QMap>
#include "srcs/Enum/skillenum.h"

class SkillFromDb
{
public:
    SkillFromDb(){}
    SkillFromDb(int Id);
    SkillFromDb(QStringList data);
    QStringList getData() const;
    int getID() const;
    QString getName() const;
    QString getNameID() const;
    QString getImage() const;
    int getCooldown() const;
    QStringList getDescription() const;
    QStringList getDescriptionID() const;
    bool isDash() const;
    bool isCombo() const;
    int getCastID() const;
    SkillTarget getSkillTarget() const;
    SkillType getSkillType() const;
    int getRange() const;
    int getManaCost() const;
    int getAnimationTimeMs() const;

protected:
    QStringList datas;
    int id;
    int imageId;
    QString nameZts, name;
    QStringList descZts, desc;
    int nbLineDesc;
    int castId;
    SkillTarget targetType;
    bool dash;
    bool combo;
    SkillType type;
    int range;
    int manaCost;
    int animationTime;
    int cooldown;

private:
    void loadData(QStringList data);
};





class DatabaseSkill
{
public:
    DatabaseSkill();
    static bool loadSkill();
    static QString getSkillTextFromZts(QString zts);
    static SkillFromDb getSkillFromId(int id);

private:
    static bool loadSkillDat();
    static bool load_code__SkillTxt();
    static QStringList SkillDat;
    static QStringList _code__SkillTxt;
    static QMap<int, SkillFromDb> skills;
};

#endif // DATABASESKILL_H

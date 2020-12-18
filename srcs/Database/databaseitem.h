#ifndef DATABASEITEM_H
#define DATABASEITEM_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>
#include <QMap>
#include "srcs/Enum/inventoryenum.h"

class ItemFromDb
{
public:
    ItemFromDb(){}
    ItemFromDb(int Vnum);
    ItemFromDb(QStringList index);
    int getVnum() const                         { return vnum; }
    QString getName() const                     { return name; }
    QString getNameZts() const                  { return nameZts; }
    QString getDescription() const              { return desc; }
    QString getDescriptionZts() const           { return descZts; }
    int getLineDesc() const                     { return lineDesc; }
    InventoryType getInventoryPart() const      { return inventoryPart; }
    ItemAttackType getAttackType() const        { return attackType; }
    ClassTypeInDb getClass() const              { return itemClass; }
    NosbazardType getNosbazardCategory() const  { return nosbazardCategory; }
    int getPrice() const                        { return price; }
    QString getImage() const                    { return image + ".png"; }
    bool isSoldable() const                     { return soldable; }
    bool isTradable() const                     { return tradable; }
    bool isDropable() const                     { return dropable; }
    bool isAskingForConfirm() const             { return warningOnUse; }
    short getParameter() const                  { return parameter; }
    bool isPotion()                             { return (inventoryPart == InventoryType::MAIN && nosbazardCategory == NosbazardType::OTHERS) ||
                                                         (inventoryPart == InventoryType::MAIN_L && nosbazardCategory == NosbazardType::OTHERS); }
    bool isSatSnack()                           { return false; } // TODO
    bool isSnack()                              { return (inventoryPart == InventoryType::ETC && nosbazardCategory == NosbazardType::EQUIPMENT) ||
                                                         (inventoryPart == InventoryType::ETC_L && nosbazardCategory == NosbazardType::EQUIPMENT); }
    bool isPotionBuff()                         { return (inventoryPart == InventoryType::MAIN || inventoryPart == InventoryType::MAIN_L)
                                                          && nosbazardCategory == NosbazardType::SP && arg9 == 0 && arg10 == 0 && arg62 == 25; }
    bool isTarot()                              { return (inventoryPart == InventoryType::ACCESSORIES || inventoryPart == InventoryType::EQUIPMENT_L)
                                                          && nosbazardCategory == NosbazardType::ACCESSORIES && arg9 == 4 && arg10 == 11; }
    bool isBenediction()                        { return (inventoryPart == InventoryType::MAIN || inventoryPart == InventoryType::MAIN_L)
                                                          && nosbazardCategory == NosbazardType::SP && warningOnUse;}
    // isTarot isn't right
protected:
    void getDataFromVnum(int vnum);
    QStringList datas;
    int vnum;
    QString image;
    QString nameZts, name;
    QString descZts, desc;
    int lineDesc;
    int price;
    bool soldable;
    bool tradable;
    bool dropable;
    bool warningOnUse;
    short parameter;
    int arg9, arg10, arg62;
    InventoryType inventoryPart;
    ItemAttackType attackType;
    ClassTypeInDb itemClass;
    NosbazardType nosbazardCategory;
};

class DatabaseItem
{
public:
    DatabaseItem();
    static bool loadItem();
    static QString getItemNameFromID(int id);
    static QString getItemDescriptionFromID(int id);
    static int getItemPriceFromID(int id);
    static QString getItemImageIDFromID(int id);
    static ItemFromDb getItemProperties(int id);

private:
    static bool loadItemDat();
    static bool load_code__ItemTxt();
    static QString getItemDatAtIndex(int id, int index);
    static QString get_code__ItemTxtFromZts(QString zts);
    static QStringList ItemDat;
    static QStringList _code__ItemTxt;
    static int argByItem;
    static QMap<int, ItemFromDb> items;
};

#endif // DATABASEITEM_H

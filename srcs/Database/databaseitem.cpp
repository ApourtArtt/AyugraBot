#include "srcs/Database/databaseitem.h"
#include <QTextStream>

QStringList            DatabaseItem::ItemDat;
QStringList            DatabaseItem::_code__ItemTxt;
int                    DatabaseItem::argByItem;
QMap<int, ItemFromDb>  DatabaseItem::items;

ItemFromDb::ItemFromDb(int Vnum)
{
    vnum = Vnum;
    getDataFromVnum(vnum);
}

ItemFromDb::ItemFromDb(QStringList index)
{
    datas = index;
    vnum = index[2].toInt();
    price = index[3].toInt();
    nameZts = index[5];
    name = DatabaseItem::getItemNameFromID(vnum);
    inventoryPart = static_cast<InventoryType>(index[7].toInt());
    nosbazardCategory = static_cast<NosbazardType>(index[8].toInt());
    arg9 = index[9].toInt();
    arg10 = index[10].toInt();
    image = DatabaseItem::getItemImageIDFromID(vnum);
    attackType = static_cast<ItemAttackType>(index[14].toInt());
    itemClass = static_cast<ClassTypeInDb>(index[15].toInt());
    soldable = !index[20].toInt();
    dropable = !index[21].toInt();
    tradable = !index[22].toInt();
    warningOnUse = index[25].toInt();
    parameter = index[29].toShort();
    arg62 = index[62].toInt();
    lineDesc = index[88].toInt();
    descZts = index[89];
    desc = DatabaseItem::getItemDescriptionFromID(vnum);
}

void ItemFromDb::getDataFromVnum(int Vnum)
{
    vnum = Vnum;
    ItemFromDb tmp = DatabaseItem::getItemProperties(vnum);
    datas = tmp.datas;
    image = tmp.image;
    nameZts = tmp.nameZts;
    name = tmp.name;
    descZts = tmp.descZts;
    desc = tmp.desc;
    lineDesc = tmp.lineDesc;
    price = tmp.price;
    soldable = tmp.soldable;
    tradable = tmp.tradable;
    dropable = tmp.dropable;
    parameter = tmp.getParameter();
    inventoryPart = tmp.inventoryPart;
    attackType = tmp.attackType;
    itemClass = tmp.itemClass;
    nosbazardCategory = tmp.nosbazardCategory;
}



DatabaseItem::DatabaseItem()
{

}

bool DatabaseItem::loadItem()
{
    if(!load_code__ItemTxt())
        return false;
    if(!loadItemDat())
        return false;
    return true;
}

bool DatabaseItem::loadItemDat()
{
    QString filePath = "Item.dat";
    QString del = "END#========================================================";
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
    for(int i = 0 ; i < 10 ; i++)
        data.replace(QString::number(i) + "\t" + del, QString::number(i) + "\tzts0e\t" + del);
    ItemDat = data.split("\t");
    int i2 = 0;
    for(int i = 0 ; i < ItemDat.size() ; i++)
    {
        if(ItemDat[i] == del)
        {
            if(argByItem != i - i2)
            {
                if(argByItem != 0)
                    return false;
                argByItem = i - i2;
            }
            i2 = i;
        }
    }
    int j = 0;
    for(int i = 0 ; i < ItemDat.size() - 1 ; i++)
    {
        QStringList tmp;
        for( ; j < argByItem * (i+1) ; j++)
        {
            if(j < ItemDat.size())
            tmp.push_back(ItemDat[j]);
        }
        if(tmp.size() == argByItem)
        {
            items[tmp[2].toInt()] = ItemFromDb(tmp);
        }
    }
    readFile.close();
    return true;
}

bool DatabaseItem::load_code__ItemTxt()
{
    QString filePath = "_code_fr_Item.txt";
    QString data;
    QFile readFile("data/" + filePath);
    if(!readFile.open(QFile::ReadOnly | QFile::Text))
        return false;
    QTextStream in(&readFile);
    in.setCodec("UTF-8");
    data = in.readAll();
    data.replace("zts", "\tzts");
    _code__ItemTxt = data.split("\t");
    if(!_code__ItemTxt.at(0).startsWith("zts"))
        _code__ItemTxt.removeFirst();
    readFile.close();
    return true;
}

ItemFromDb DatabaseItem::getItemProperties(int id)
{
    return items[id];
}

QString DatabaseItem::getItemNameFromID(int id)
{
    if(id <= 0)
        return nullptr;
    QString zts = getItemDatAtIndex(id, 5);
    return get_code__ItemTxtFromZts(zts);
}

QString DatabaseItem::getItemDescriptionFromID(int id)
{
    if(id <= 0)
        return "";
    QString zts = getItemDatAtIndex(id, 89);
    if(zts == "zts0e")
        return nullptr;
    return get_code__ItemTxtFromZts(zts);
}

int DatabaseItem::getItemPriceFromID(int id)
{
    if(id <= 0)
        return -1;
    return getItemDatAtIndex(id, 3).toInt();
}

QString DatabaseItem::getItemImageIDFromID(int id)
{
    if(id <= 0)
        return nullptr;
    return getItemDatAtIndex(id, 11);
}

/* Item.dat function parsing
 * 2  : VNUM
 * 3  : Price
 * 5  : Name's identifier (ztsXXXXXe)
 * 7  : Inventory part
 * 8  : Nosbazard category
 * 14 : Attack type
 * 15 : Class that can equip
 * 20 : Not Soldable ?
 * 21 : Not dropable ?
 * 22 : Not tradable ?
 * 29 : Parameter
 * 88 : Line Description
 * 89 : Description's identifier (ztsXXXXXe)
*/

QString DatabaseItem::getItemDatAtIndex(int id, int index)
{
    QString idString = QString::number(id);
    for(int i = 0 ; i < ItemDat.size() - argByItem ; i = i + argByItem)
    {
        if(ItemDat[i+2] == idString)
            return ItemDat[i+index];
    }
    return nullptr;
}

/* _code_XX_Item.txt function parsing
 * 0 : Name or description identifier (ztsXXXXXe)
 * 1 : Item name or description
*/

QString DatabaseItem::get_code__ItemTxtFromZts(QString zts)
{
    for(int i = 0 ; i < _code__ItemTxt.size() ; i = i + 2)
        if(_code__ItemTxt[i] == zts)
            return _code__ItemTxt[i+1];
    return nullptr;
}

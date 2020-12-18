#ifndef INVENTORYENUM_H
#define INVENTORYENUM_H

enum class Rarity {
    DAMAGED      = -2,
    BAD          = -1,
    NORMAL       = 0,
    USEFULL      = 1,
    GOOD         = 2,
    HIGH_QUALITY = 3,
    EXCELLENT    = 4,
    ANCESTRAL    = 5,
    MYSTERIOUS   = 6,
    LEGENDARY    = 7,
    PHENOMENAL   = 8
};

enum class InventoryType {
    EQUIPMENT   = 0,
    MAIN        = 1,
    ETC         = 2,
    MINILAND    = 3,
    ACCESSORIES = 4,
    UNKNOWN5    = 5,
    SP          = 6,
    COSTUMES    = 7,
    EQUIPMENT_L = 8,
    MAIN_L      = 9,
    ETC_L       = 10
};

enum class ItemAttackType {
    MELEE_DEFAULT   = 0,
    DISTANCE        = 1,
    MAGIC           = 2
};

enum class ClassTypeInDb {
    ANY         = 0,
    ADVENTURER  = 1,
    SWORDSMAN   = 2,
    ARCHER      = 4,
    MAGICIAN    = 8
};

// To rework since NT's data are crap
enum class NosbazardType {
    WEAPON_DEFAULT  = 0,
    ARMOR           = 1,
    EQUIPMENT       = 2, // gants, bottes, masque, chapeau cost/chapeau nosmall, aile (diable, ...), skin arme
    ACCESSORIES     = 3, // Tarot, fée, bijoux
    SP              = 4,
    OTHERS          = 5, // nosmates, boosteur loco, boîte raid, perle familier/loco, boîte sp
    RUNES           = 6
};

/*INDEX 0 0 6 0 32 0 - bow
INDEX 0 1 2 1 280 3 - armor archer
INDEX <inv> <type of item> <class/more type>
0 is weapon, 1 is armor in <type of item>
<class/more type> for weapons:
0 : bâton aventu armureAventu chapeau
1 : épée armureM
2 : gant armureA
3 : chaussures dague armureE
4 : tarot
5 : catapulte / arba
6 : arc
8 : gun
9 : baguette*/

#endif // INVENTORYENUM_H

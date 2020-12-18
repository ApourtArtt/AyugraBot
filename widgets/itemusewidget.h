#ifndef ITEMUSEWIDGET_H
#define ITEMUSEWIDGET_H

#include <QWidget>
#include <QDateTime>
#include "srcs/GameObjects/Entity/mycharacter.h"

namespace Ui {
class ItemUseWidget;
}

enum class ConditionType
{
    HP_FLAT    = 0,
    MP_FLAT    = 1,
    HP_PERCENT = 2,
    MP_PERCENT = 3,
    AFTER_SEC  = 4,
    AFTER_MIN  = 5
};

class ItemCondition
{
public:
    ItemCondition(ConditionType ConditionType, int Condition, QPair<InventoryType, int> itemToUse);
    bool mustBeUsed(Statistics stats);
    void setLastUsage(QDateTime current);
    QPair<InventoryType, int> getItem();

private:
    int conditionValue;
    ConditionType conditionType;
    QDateTime lastUse;
    QPair<InventoryType, int> item;
};

class ItemUseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ItemUseWidget(QWidget *parent = nullptr);
    ~ItemUseWidget();
    void treatInventory(Inventory *_inventory);
    bool shouldContinueOnStop();
    QVector<ItemCondition*> getItemsCondition();

private slots:
    void on_PB_ADD_clicked();
    void on_PB_DELETE_clicked();

private:
    void refresh();
    Ui::ItemUseWidget *ui;
    Inventory *inventory;
    QVector<QPair<InventoryType, int>> items;
    QVector<ItemCondition*> itemsCondition;
};

#endif // ITEMUSEWIDGET_H

#ifndef INVENTORYWIDGET_H
#define INVENTORYWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QMouseEvent>
#include "formbase.h"
#include "srcs/GameObjects/Inventory/inventory.h"
#include "ui_inventorywidget.h"
#include "modules/itemtablewidget.h"

namespace Ui {
class InventoryWidget;
}

class InventoryWidget : public FormBase
{
    Q_OBJECT

public:
    explicit InventoryWidget(QWidget *parent = nullptr);
    ~InventoryWidget();
    void treatInventory(Inventory *inv);

signals:
    bool tryToUseItem(InventoryType inv, short cell);
    bool tryToShowItem(int inv, short cell);

private:
    void displayItem(InventoryType invType, ItemTableWidget *device, Item *item);
    void showSingleItem(ItemTableWidget *table, QTableWidgetItem *itm);
    void useItem(ItemTableWidget *table, QTableWidgetItem *itm);
    void moveItem(ItemTableWidget *table, short source, short dest, int quantity);
    short getSlotFromItem(ItemTableWidget *table, QTableWidgetItem *item);
    InventoryType getInventoryTypeFromWidget(ItemTableWidget *table);
    Ui::InventoryWidget *ui;

    Inventory *inventory;
    QVector<InventoryType> invTypes;
    QVector<ItemTableWidget*> invWidget;

};

#endif // INVENTORYWIDGET_H

#include "inventorywidget.h"
#include <QDebug>

InventoryWidget::InventoryWidget(QWidget *parent) :
    FormBase(parent),
    ui(new Ui::InventoryWidget)
{
    ui->setupUi(this);
    inventory = nullptr;

    connect(ui->TW_EQUIPMENT, &ItemTableWidget::dragAndDrop, this, &InventoryWidget::moveItem);
    connect(ui->TW_MAIN, &ItemTableWidget::dragAndDrop, this, &InventoryWidget::moveItem);
    connect(ui->TW_ETC, &ItemTableWidget::dragAndDrop, this, &InventoryWidget::moveItem);
    connect(ui->TW_MINILAND, &ItemTableWidget::dragAndDrop, this, &InventoryWidget::moveItem);
    connect(ui->TW_SP, &ItemTableWidget::dragAndDrop, this, &InventoryWidget::moveItem);
    connect(ui->TW_COST, &ItemTableWidget::dragAndDrop, this, &InventoryWidget::moveItem);

    connect(ui->TW_EQUIPMENT, &ItemTableWidget::cellDoubleLeftClick, this, &InventoryWidget::useItem);
    connect(ui->TW_MAIN, &ItemTableWidget::cellDoubleLeftClick, this, &InventoryWidget::useItem);
    connect(ui->TW_ETC, &ItemTableWidget::cellDoubleLeftClick, this, &InventoryWidget::useItem);
    connect(ui->TW_MINILAND, &ItemTableWidget::cellDoubleLeftClick, this, &InventoryWidget::useItem);
    connect(ui->TW_SP, &ItemTableWidget::cellDoubleLeftClick, this, &InventoryWidget::useItem);
    connect(ui->TW_COST, &ItemTableWidget::cellDoubleLeftClick, this, &InventoryWidget::useItem);

    connect(ui->TW_EQUIPMENT, &ItemTableWidget::cellRightClick, this, &InventoryWidget::showSingleItem);
    connect(ui->TW_MAIN, &ItemTableWidget::cellRightClick, this, &InventoryWidget::showSingleItem);
    connect(ui->TW_ETC, &ItemTableWidget::cellRightClick, this, &InventoryWidget::showSingleItem);
    connect(ui->TW_MINILAND, &ItemTableWidget::cellRightClick, this, &InventoryWidget::showSingleItem);
    connect(ui->TW_SP, &ItemTableWidget::cellRightClick, this, &InventoryWidget::showSingleItem);
    connect(ui->TW_COST, &ItemTableWidget::cellRightClick, this, &InventoryWidget::showSingleItem);
}

InventoryWidget::~InventoryWidget()
{
    delete ui;
}

void InventoryWidget::treatInventory(Inventory *inv)
{
    inventory = inv;
    ui->L_INVGOLD->setText(QString::number(inv->getInventoryGold()));
    ui->L_BANKGOLD->setText(QString::number(inv->getBankGold()));
    /*std::vector<InventoryType> */invTypes =
    {
        InventoryType::EQUIPMENT,
        InventoryType::MAIN,
        InventoryType::ETC,
        InventoryType::MINILAND,
        InventoryType::SP,
        InventoryType::COSTUMES
    };
    /*std::vector<ItemTableWidget*> */invWidget =
    {
        ui->TW_EQUIPMENT,
        ui->TW_MAIN,
        ui->TW_ETC,
        ui->TW_MINILAND,
        ui->TW_SP,
        ui->TW_COST
    };
    for(int i = 0 ; i < invTypes.size() && i < invWidget.size() ; i++)
    {
        invWidget[i]->clear();
        SubInventory *subInv = inv->getSubinventory(invTypes[i]);
        if(subInv != nullptr)
        {
            QMap<short, Item*> itemList = subInv->getItemList();
            QList<short> keys = itemList.keys();
            for(int j = 0 ; j < itemList.size() ; j++)
            {
                displayItem(invTypes[i], invWidget[i], itemList[keys[j]]);
            }
        }
    }
}

void InventoryWidget::displayItem(InventoryType invType, ItemTableWidget *device, Item *item)
{
    if(device == nullptr)
        return;
    QTableWidgetItem *itm = new QTableWidgetItem();
    if(invType == InventoryType::ETC || invType == InventoryType::MAIN)
        itm->setText("x" + QString::number(item->getQuantity()));
    QPixmap scaled("images/" + item->getImage());
    //scaled.scaled(scaled.size() * 5);
    itm->setIcon(scaled);
    short slot = item->getSlot();
    int nbCol = device->columnCount();
    device->setItem(slot/nbCol, slot%nbCol, itm);
}

void InventoryWidget::showSingleItem(ItemTableWidget *table, QTableWidgetItem *itm)
{
    if(!inventory || !table || !itm)
        return;
    qDebug() << "Show " << getSlotFromItem(table, itm);
    InventoryType invT = getInventoryTypeFromWidget(table);
    int invTint = static_cast<int>(invT);
    if(invT == InventoryType::SP || invT == InventoryType::COSTUMES)
        invTint += 4;
    emit tryToShowItem(invTint, getSlotFromItem(table, itm));
}

void InventoryWidget::useItem(ItemTableWidget *table, QTableWidgetItem *itm)
{
    if(!inventory || !table || !itm)
        return;
    qDebug() << "Use " << getSlotFromItem(table, itm);
    emit tryToUseItem(getInventoryTypeFromWidget(table), getSlotFromItem(table, itm));
}

void InventoryWidget::moveItem(ItemTableWidget *table, short source, short dest, int quantity)
{
    if(!inventory || !table)
        return;
    qDebug() << " - Move " << source << " to " << dest;
    qDebug() << QString::number(static_cast<int>(getInventoryTypeFromWidget(table))) << source << dest << quantity;
    InventoryType it = getInventoryTypeFromWidget(table);
    SubInventory *sub = inventory->getSubinventory(it);
    sub->moveItem(quantity, dest, source);
}

short InventoryWidget::getSlotFromItem(ItemTableWidget *table, QTableWidgetItem *item)
{
    if(!inventory)
        return -1;
    return static_cast<short>(item->column() + item->row() * table->columnCount());
}

InventoryType InventoryWidget::getInventoryTypeFromWidget(ItemTableWidget *table)
{
    for(int i = 0 ; i < invWidget.size() && i < invTypes.size() ; i++)
    {
        if(table == invWidget[i])
            return invTypes[i];
    }
    return InventoryType::UNKNOWN5;
}

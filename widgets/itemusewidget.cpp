#include "itemusewidget.h"
#include "ui_itemusewidget.h"

ItemUseWidget::ItemUseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemUseWidget)
{
    ui->setupUi(this);
    inventory = nullptr;
}

ItemUseWidget::~ItemUseWidget()
{
    delete ui;
}

void ItemUseWidget::treatInventory(Inventory *_inventory)
{
    inventory = _inventory;
    refresh();
}

bool ItemUseWidget::shouldContinueOnStop()
{
    return ui->CB_CONTINUEUSING->isChecked();
}

QVector<ItemCondition *> ItemUseWidget::getItemsCondition()
{
    return itemsCondition;
}

void ItemUseWidget::refresh()
{
    ui->CB_ITEMS->clear();
    items.clear();
    QVector<InventoryType> invTypes =
    {
        InventoryType::EQUIPMENT,
        InventoryType::MAIN,
        InventoryType::ETC,
        InventoryType::EQUIPMENT_L,
        InventoryType::MAIN_L,
        InventoryType::ETC_L
    };
    for(int i = 0 ; i < invTypes.size() ; i++)
    {
        SubInventory *current = inventory->getSubinventory(invTypes[i]);
        if(!current)
            continue;
        QMap<short, Item*> currentItems = current->getItemList();
        QList<short> itemsKeys = currentItems.keys();
        for(int j = 0 ; j < itemsKeys.size() ; j++)
        {
            Item *i = currentItems[itemsKeys[j]];
            if(!i)
                continue;
            //if(i->isPotion() || i->isSnack() || i->isTarot()  || i->isPotionBuff()
            //        || i->isBenediction())
            //{
                int itemID = i->getVnum();
                if(!items.contains({ i->getInventoryPart(), itemID }))
                {
                    ui->CB_ITEMS->addItem(i->getName());
                    items.push_back({ i->getInventoryPart(), i->getVnum() });
                }
            //}
        }
    }
}

void ItemUseWidget::on_PB_ADD_clicked()
{
    for(int i = 0 ; i < items.size() ; i++)
        qDebug() << items[i].second;
    int index = ui->CB_ITEMS->currentIndex();
    qDebug() << index;
    if(index < 0 || index > items.size())
        return;
    if(ui->CB_COND->currentIndex() == -1)
        return;
    if(ui->SB_COND->value() < 0)
        return;
    qDebug() << ui->CB_COND->currentIndex() << ui->SB_COND->value();
    itemsCondition.push_back(new ItemCondition(static_cast<ConditionType>(ui->CB_COND->currentIndex()),
                                               ui->SB_COND->value(), { items[index] }));
    ui->CB_ITEMSADDED->addItem(ui->CB_COND->currentText() + " " + QString::number(ui->SB_COND->value())
                               + " " + ui->CB_ITEMS->currentText());
}

void ItemUseWidget::on_PB_DELETE_clicked()
{
    int index = ui->CB_ITEMSADDED->currentIndex();
    if(index < 0 || index > itemsCondition.size())
        return;
    ui->CB_ITEMSADDED->removeItem(index);
    itemsCondition.erase(itemsCondition.begin() + index);
}



ItemCondition::ItemCondition(ConditionType ConditionType, int ConditionValue, QPair<InventoryType, int> itemToUse)
{
    conditionType = ConditionType;
    conditionValue = ConditionValue;
    item = itemToUse;
    lastUse = QDateTime::currentDateTime().addDays(-1);
    qDebug() << item.second;
}

bool ItemCondition::mustBeUsed(Statistics stats)
{
    switch(conditionType)
    {
    case ConditionType::HP_FLAT:
        if(conditionValue > stats.getMaxHP())
            return false;
        return stats.getCurrentHP() <= conditionValue;
    case ConditionType::MP_FLAT:
        if(conditionValue > stats.getMaxMP())
            return false;
        return stats.getCurrentMP() <= conditionValue;
    case ConditionType::HP_PERCENT:
        return stats.getPercentHP() * 100 <= conditionValue;
    case ConditionType::MP_PERCENT:
         return stats.getPercentMP() * 100 <= conditionValue;
    case ConditionType::AFTER_SEC:
        return QDateTime::currentDateTime() > lastUse.addSecs(conditionValue);
    case ConditionType::AFTER_MIN:
        return QDateTime::currentDateTime() > lastUse.addSecs(conditionValue * 60);
    }
    return false;
}

void ItemCondition::setLastUsage(QDateTime current)
{
    lastUse = current;
}

QPair<InventoryType, int> ItemCondition::getItem()
{
    return item;
}

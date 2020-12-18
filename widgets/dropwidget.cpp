#include "dropwidget.h"
#include "ui_dropwidget.h"

DropWidget::DropWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DropWidget)
{
    ui->setupUi(this);
    map = nullptr;
}

DropWidget::~DropWidget()
{
    delete ui;
}

void DropWidget::mapUpdated(Map *Map)
{
    if(!map)
        map = Map;
    QList<int> keys = map->getMonsterUniqueVnum();
    if(keys != monstersUniqueVnum && ui->CB_MAPDROPONLY->isChecked())
    {
        monstersUniqueVnum = keys;
        refresh();
    }
}

void DropWidget::refresh()
{
    ui->LW_DROPSLIST->clear();
    shownItems.clear();
    if(ui->CB_MAPDROPONLY->isChecked())
    {
        shownItems = map->getMapItemsID();
        for(int i = 0 ; i < monstersUniqueVnum.size() ; i++)
        {
            MonsterFromDb tmp = DatabaseMonster::getMonsterProperties(monstersUniqueVnum[i]);
            QList<int> itemsID = tmp.getDropableItemsID();
            for(int j = 0 ; j < itemsID.size() ; j++)
            {
                if(!shownItems.contains(itemsID[j]))
                    shownItems.push_back(itemsID[j]);
            }
        }
    }
    else
    {
        QMap<int, MonsterFromDb> Monsters = DatabaseMonster::GetMonsters();
        QList<int> keys = Monsters.keys();
        shownItems = DatabaseMap::getUniqueMapItemsID();
        for(int i = 0 ; i < keys.size() ; i++)
        {
            MonsterFromDb tmp = Monsters[keys[i]];
            QList<int> iID = tmp.getDropableItemsID();
            for(int j = 0 ; j < iID.size() ; j++)
            {
                if(!shownItems.contains(iID[j]))
                    shownItems.push_back(iID[j]);
            }
        }
    }
    for(int i = 0 ; i < shownItems.size() ; i++)
        ui->LW_DROPSLIST->addItem(DatabaseItem::getItemNameFromID(shownItems[i]));
}

void DropWidget::on_CB_MAPDROPONLY_stateChanged(int arg1)
{
    refresh();
    emit dropFilter(filteredItems, ui->RB_BL->isChecked() ? DropListType::BLACKLIST : DropListType::WHITELIST);
}

void DropWidget::on_PB_ADD_clicked()
{
    int index = ui->LW_DROPSLIST->currentRow();
    if(index == -1 || index >= shownItems.size())
        return;
    if(filteredItems.contains(shownItems[index]))
        return;
    ui->LW_DROPSFILTEREDLIST->addItem(ui->LW_DROPSLIST->currentItem()->text());
    filteredItems.push_back(shownItems[index]);
    emit dropFilter(filteredItems, ui->RB_BL->isChecked() ? DropListType::BLACKLIST : DropListType::WHITELIST);
}

void DropWidget::on_PB_DELETE_clicked()
{
    int index = ui->LW_DROPSFILTEREDLIST->currentRow();
    if(index == -1 || index >= filteredItems.size())
        return;
    ui->LW_DROPSFILTEREDLIST->takeItem(index);
    filteredItems.erase(filteredItems.begin() + index);
    emit dropFilter(filteredItems, ui->RB_BL->isChecked() ? DropListType::BLACKLIST : DropListType::WHITELIST);
}

void DropWidget::on_RB_BL_clicked()
{
    emit dropFilter(filteredItems, ui->RB_BL->isChecked() ? DropListType::BLACKLIST : DropListType::WHITELIST);
}

void DropWidget::on_RB_WL_clicked()
{
    emit dropFilter(filteredItems, ui->RB_BL->isChecked() ? DropListType::BLACKLIST : DropListType::WHITELIST);
}

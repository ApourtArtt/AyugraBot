#include "monsterwidget.h"
#include "ui_monsterwidget.h"

MonsterWidget::MonsterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonsterWidget)
{
    ui->setupUi(this);
    map = nullptr;
}

MonsterWidget::~MonsterWidget()
{
    delete ui;
}

void MonsterWidget::mapUpdated(Map *Map)
{
    if(!map)
        map = Map;
    QList<int> keys = map->getMonsterUniqueVnum();
    if(keys != monstersUniqueVnum && ui->CB_MAPMONSTERONLY->isChecked())
    {
        monstersUniqueVnum = keys;
        refresh();
    }
}

void MonsterWidget::refresh()
{
    ui->LW_MONSTERSLIST->clear();
    if(ui->CB_MAPMONSTERONLY->isChecked())
    {
        for(int i = 0 ; i < monstersUniqueVnum.size() ; i++)
        {
            MonsterFromDb tmp = DatabaseMonster::getMonsterProperties(monstersUniqueVnum[i]);
            ui->LW_MONSTERSLIST->addItem(tmp.getName() + " " + QString::number(tmp.getVnum()) + " - Lv." + QString::number(tmp.getLevel()));
        }
    }
    else
    {
        QMap<int, MonsterFromDb> Monsters = DatabaseMonster::GetMonsters();
        QList<int> keys = Monsters.keys();
        for(int i = 0 ; i < keys.size() ; i++)
        {
            MonsterFromDb tmp = Monsters[keys[i]];
            ui->LW_MONSTERSLIST->addItem(tmp.getName() + " " + QString::number(tmp.getVnum()) + " - Lv." + QString::number(tmp.getLevel()));
        }
    }
}


void MonsterWidget::on_CB_MAPMONSTERONLY_stateChanged(int arg1)
{
    refresh();
}

void MonsterWidget::on_PB_ADD_clicked()
{
    int index = ui->LW_MONSTERSLIST->currentRow();
    if(index == -1)
        return;
    int id = -1;
    if(ui->CB_MAPMONSTERONLY->isChecked())
    {
        if(index >= monstersUniqueVnum.size())
            return;
        id = monstersUniqueVnum[index];
    }
    else
    {
        QMap<int, MonsterFromDb> Monsters = DatabaseMonster::GetMonsters();
        if(index >= Monsters.size())
            return;
        id = Monsters[Monsters.keys()[index]].getVnum();
    }
    if(monstersIdToFilter.contains(id))
        return;
    ui->LW_MONSTERSFILTEREDLIST->addItem(ui->LW_MONSTERSLIST->currentItem()->text());
    monstersIdToFilter.push_back(id);
    emit monsterFilter(monstersIdToFilter, ui->RB_BL->isChecked() ? MonsterListType::BLACKLIST : MonsterListType::WHITELIST);
}

void MonsterWidget::on_PB_DELETE_clicked()
{
    int index = ui->LW_MONSTERSFILTEREDLIST->currentRow();
    if(index == -1 || index >= monstersIdToFilter.size())
        return;
    monstersIdToFilter.removeAt(index);
    ui->LW_MONSTERSFILTEREDLIST->takeItem(index);
    emit monsterFilter(monstersIdToFilter, ui->RB_BL->isChecked() ? MonsterListType::BLACKLIST : MonsterListType::WHITELIST);
}

void MonsterWidget::on_RB_WL_clicked()
{
    emit monsterFilter(monstersIdToFilter, ui->RB_BL->isChecked() ? MonsterListType::BLACKLIST : MonsterListType::WHITELIST);
}

void MonsterWidget::on_RB_BL_clicked()
{
    emit monsterFilter(monstersIdToFilter, ui->RB_BL->isChecked() ? MonsterListType::BLACKLIST : MonsterListType::WHITELIST);
}

#include "userswidget.h"
#include "ui_userswidget.h"

UsersWidget::UsersWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UsersWidget)
{
    ui->setupUi(this);
    ui->TW_USERS_1->setHorizontalHeaderLabels({ "Pseudonym", "Level" });
    menuUsers = new QMenu(this);
    menuUsers->setTitle("Player pannel");

    selected = false;

    QAction *partyRequest = new QAction("Party request", menuUsers);
    connect(partyRequest, &QAction::triggered, [=]{ emit sendPartyRequest(currentPlayer); });
    menuUsers->addAction(partyRequest);

    QAction *blacklistRequest = new QAction("Blacklist", menuUsers);
    connect(blacklistRequest, &QAction::triggered, [=]{ emit sendBlacklist(currentPlayer); });
    menuUsers->addAction(blacklistRequest);

    QAction *friendRequest = new QAction("Friend request", menuUsers);
    connect(friendRequest, &QAction::triggered, [=]{ emit sendFriendRequest(currentPlayer); });
    menuUsers->addAction(friendRequest);
}

UsersWidget::~UsersWidget()
{
    delete ui;
}

void UsersWidget::setMap(Map *Map)
{
    map = Map;
}

void UsersWidget::inOut()
{
    clear();
    QMap<int, Player> players = map->getPlayerList();
    QList<int> keys = players.keys();
    ui->TW_USERS_1->setRowCount(keys.size());
    bool found = false;
    for(int i = 0 ; i < keys.size() ; i++)
    {
        if(players[i].getAuthority() == Authority::GM)
            ui->TW_USERS_1->setItem(i, 0, new QTableWidgetItem("[GM]" + players[keys[i]].getName()));
        else
            ui->TW_USERS_1->setItem(i, 0, new QTableWidgetItem(players[keys[i]].getName()));
        ui->TW_USERS_1->setItem(i, 1, new QTableWidgetItem(QString::number(players[keys[i]].getLevel()) + "+" + QString::number(players[keys[i]].getLevelHero())));
        qDebug() << selected << players[keys[i]].getID() << currentPlayer.getID();
        if (selected && players[keys[i]].getID() == currentPlayer.getID())
        {
            qDebug() << "InOut: " << i;
            ui->TW_USERS_1->setCurrentCell(i, 0);
            found = true;
        }
    }
    if (!found)
    {
        qDebug() << "Not found";
        ui->TW_USERS_1->setCurrentCell(-1, -1);
        selected = false;
    }
}

void UsersWidget::clear()
{
    ui->TW_USERS_1->clear();
}

void UsersWidget::on_TW_USERS_1_customContextMenuRequested(const QPoint &pos)
{
    QMap<int, Player> players = map->getPlayerList();
    QList<int> keys = players.keys();
    int index = ui->TW_USERS_1->currentRow();
    if(index >= keys.size() || index < 0)
        return;
    currentPlayer = players[keys[index]];
    menuUsers->exec(ui->TW_USERS_1->mapToGlobal(pos));
}

void UsersWidget::on_TW_USERS_1_cellActivated(int row, int column)
{
    QMap<int, Player> players = map->getPlayerList();
    QList<int> keys = players.keys();
    int index = row;
    if(index >= keys.size() || index < 0)
        return;
    selected = true;
    currentPlayer = players[keys[index]];
    emit selectedPlayer(players[keys[index]]);
}

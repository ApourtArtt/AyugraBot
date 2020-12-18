#ifndef MONSTERWIDGET_H
#define MONSTERWIDGET_H

#include <QWidget>
#include "srcs/GameObjects/Map/map.h"
#include "srcs/Database/databasemonster.h"

namespace Ui {
class MonsterWidget;
}

enum class MonsterListType
{
    WHITELIST = 0,
    BLACKLIST = 1
};

class MonsterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MonsterWidget(QWidget *parent = nullptr);
    ~MonsterWidget();
    void mapUpdated(Map *Map);

signals:
    void monsterFilter(QList<int> monstersID, MonsterListType listType);

private slots:
    void on_CB_MAPMONSTERONLY_stateChanged(int arg1);
    void on_PB_ADD_clicked();
    void on_PB_DELETE_clicked();
    void on_RB_WL_clicked();
    void on_RB_BL_clicked();

private:
    void refresh();

    QMap<int, Monster> monsters;
    QList<int> monstersUniqueVnum;
    QList<int> monstersIdToFilter;
    Map *map;
    Ui::MonsterWidget *ui;
};

#endif // MONSTERWIDGET_H

#ifndef DROPWIDGET_H
#define DROPWIDGET_H

#include <QWidget>
#include "srcs/GameObjects/Map/map.h"
#include "srcs/Database/databasemonster.h"
#include "srcs/Database/databaseitem.h"

namespace Ui {
class DropWidget;
}

enum class DropListType
{
    WHITELIST = 0,
    BLACKLIST = 1
};

class DropWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DropWidget(QWidget *parent = nullptr);
    ~DropWidget();
    void mapUpdated(Map *Map);

signals:
    void dropFilter(QList<int> dropID, DropListType listType);

private slots:
    void on_CB_MAPDROPONLY_stateChanged(int arg1);
    void on_PB_ADD_clicked();
    void on_PB_DELETE_clicked();

    void on_RB_BL_clicked();

    void on_RB_WL_clicked();

private:
    void refresh();

    QList<int> monstersUniqueVnum;
    QList<int> shownItems, filteredItems;
    Map *map;
    Ui::DropWidget *ui;
};

/*
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
*/

#endif // DROPWIDGET_H

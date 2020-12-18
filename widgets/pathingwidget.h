#ifndef PATHINGWIDGET_H
#define PATHINGWIDGET_H

#include <QWidget>
#include "srcs/GameObjects/Map/map.h"

enum class PathingType
{
    FREE        = 0,
    CYCLE       = 1,
    TELEPORT    = 2,
    CLOSEST     = 3
};

namespace Ui {
class PathingWidget;
}

class PathingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PathingWidget(QWidget *parent = nullptr);
    ~PathingWidget();
    void setMap(Map *Map);

signals:
    void onPathingChanged(PathingType pathingType, QPair<int, int> arg1 = {}, QVector<QPair<int, int>> arg2 = {});

private slots:
    void on_LE_RADIUSVALUE_textChanged(const QString &arg1);
    void on_RB_RADIUS_clicked();
    void on_RB_CYCLE_clicked();
    void on_RB_TP_clicked();
    void on_RB_FREE_clicked();

private:
    Ui::PathingWidget *ui;
    QPair<int, int> firstPoint;
    QVector<QPair<int, int>> way;
    Map *map;
};

#endif // PATHINGWIDGET_H

#include "pathingwidget.h"
#include "ui_pathingwidget.h"

PathingWidget::PathingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PathingWidget)
{
    ui->setupUi(this);
    firstPoint = {};
}

PathingWidget::~PathingWidget()
{
    delete ui;
}

void PathingWidget::setMap(Map *Map)
{
    map = Map;
    ui->W_MAP->setMap(map);
}

void PathingWidget::on_LE_RADIUSVALUE_textChanged(const QString &arg1)
{
    way.clear();
    way.push_back({ arg1.toInt(), -1 });
    emit onPathingChanged(PathingType::CLOSEST, firstPoint, way);
}

void PathingWidget::on_RB_RADIUS_clicked()
{
    emit onPathingChanged(PathingType::CLOSEST, firstPoint, way);
}

void PathingWidget::on_RB_CYCLE_clicked()
{
    // TODO
}

void PathingWidget::on_RB_TP_clicked()
{
    // TODO
}

void PathingWidget::on_RB_FREE_clicked()
{
    emit onPathingChanged(PathingType::FREE);
}

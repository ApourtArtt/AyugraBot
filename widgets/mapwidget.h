#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QImageReader>
#include <QTimer>
#include <QPainter>
#include <QPen>
#include <QtConcurrent>
#include "srcs/GameObjects/Map/map.h"
#include "srcs/Utils/Pathfinding/pathfinding.h"

namespace Ui {
class MapWidget;
}

enum class MapTypePrinter
{
    MAP_ENTITY_PRINTER  = 0,
    NOTHING             = 1
};

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = nullptr);
    ~MapWidget();
    void setMap(Map *Map);
    void setMapTypePrinter(MapTypePrinter type);
    void mapUpdated();
    void characterMoved(int x, int y);
    void characterTargettedMoved(int x, int y);
    Portal getNearestPortal(QPoint pos);

signals:
    void leftClicked(QPoint pos);
    void rightClicked(QPoint pos);

private:
    void clear(QPoint point);
    void refresh();
    void tick();

    Ui::MapWidget *ui;
    Map *map;
    QPoint characterPos, characterTargettedPos;
    QImage currentMapImage, originalImage;
    QPainter mapPainter;
    QPen tsPen, portalPen, characterPen, characterTargettedPen;
    QMap<int, Portal> currentPortals;
    QMap<int, TS> currentTS;
    QTimer *refresherSingleshot;
    MapTypePrinter mapPrinterType;
};

#endif // MAPWIDGET_H

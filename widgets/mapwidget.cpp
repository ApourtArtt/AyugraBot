#include "mapwidget.h"
#include "ui_mapwidget.h"
#include <QDebug>

MapWidget::MapWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MapWidget)
{
    ui->setupUi(this);
    mapPrinterType = MapTypePrinter::MAP_ENTITY_PRINTER;

    characterPos = {-1, -1};
    characterTargettedPos = {-1, -1};

    portalPen.setColor(Qt::red);
    portalPen.setWidth(12);

    tsPen.setColor(Qt::blue);
    tsPen.setWidth(10);

    characterPen.setColor(Qt::green);
    characterPen.setWidth(8);

    characterTargettedPen.setColor(Qt::darkGreen);
    characterTargettedPen.setWidth(5);

    refresherSingleshot = new QTimer(this);
    refresherSingleshot->setSingleShot(true);
    refresherSingleshot->setInterval(200);

    connect(refresherSingleshot, &QTimer::timeout, this, [=]
    {
        refresh();
    });

    connect(ui->L_MAP, &ClickableLabel::leftClicked, [=](QPoint pos)
    {
        pos = pos/2;
        emit leftClicked(pos);
    });

    connect(ui->L_MAP, &ClickableLabel::rightClicked, [=](QPoint pos)
    {
        pos = pos/2;
        emit rightClicked(pos);
    });
}

MapWidget::~MapWidget()
{
    delete ui;
}

void MapWidget::setMap(Map *Map)
{
    clear({0, 0});
    currentPortals.clear();
    currentTS.clear();
    map = Map;
    QImageReader reader(QApplication::applicationDirPath() + "/data/mappath/" + QString::number(map->getMapID()) + ".png");
    reader.setAutoTransform(true);
    currentMapImage = reader.read();
    originalImage = currentMapImage;
    ui->L_MAP->setPixmap(QPixmap::fromImage(currentMapImage));
    ui->L_MAP->setMaximumSize(currentMapImage.size());
    ui->L_MAP->setMinimumSize(currentMapImage.size());
    ui->L_MAP->setScaledContents(true);
    adjustSize();
}

void MapWidget::setMapTypePrinter(MapTypePrinter type)
{
    mapPrinterType = type;
}

void MapWidget::mapUpdated()
{
    if(currentPortals.size() != map->getPortalList().size() || currentTS.size() != map->getTSList().size())
    {
        currentPortals = map->getPortalList();
        currentTS = map->getTSList();
        tick();
    }
}

void MapWidget::characterMoved(int x, int y)
{
    if(characterPos != QPoint(-1, -1))
        clear(characterPos);
    characterPos = QPoint(x*2, y*2);
    refresh();
}

void MapWidget::characterTargettedMoved(int x, int y)
{
    if (x == -1 && y == -1)
    {
        characterTargettedPos = {-1, -1};
        clear(characterTargettedPos);
        refresh();
        return;
    }
    if(characterTargettedPos != QPoint(-1, -1))
        clear(characterTargettedPos);
    characterTargettedPos = QPoint(x*2, y*2);
    refresh();
}

Portal MapWidget::getNearestPortal(QPoint pos)
{
    int tsID = -1;
    double currentDist = -1;
    QList<int> keys = currentPortals.keys();
    for(int i = 0 ; i < keys.size() ; i++)
    {
        QPoint current = { currentPortals[keys[i]].getX(), currentPortals[keys[i]].getY() };
        double dist = PathFinding::distance({ pos.x(), pos.y() }, { current.x(), current.y() });
        if((currentDist < 0 || dist < currentDist))
        {
            tsID = currentPortals[keys[i]].getID();
            currentDist = dist;
        }
    }
    return currentPortals[tsID];
}

void MapWidget::clear(QPoint point)
{
    Q_UNUSED(point)
    currentMapImage = originalImage;
}

void MapWidget::refresh()
{
    QList<int> portalKeys = map->getPortalList().keys();
    QList<int> tsKeys = map->getTSList().keys();
    if(!mapPainter.begin(&currentMapImage))
        return;
    mapPainter.setPen(portalPen);
    for(int i = 0 ; i < portalKeys.size() ; i++)
    {
        QPoint point = { currentPortals[portalKeys[i]].getX() * 2, currentPortals[portalKeys[i]].getY() * 2 };
        mapPainter.drawEllipse(point, 6, 6);
    }
    mapPainter.setPen(tsPen);
    for(int i = 0 ; i < tsKeys.size() ; i++)
    {
        QPoint point = { currentTS[tsKeys[i]].getX() * 2, currentTS[tsKeys[i]].getY() * 2 };
        mapPainter.drawEllipse(point, 5, 5);
    }
    qDebug() << characterPos;
    mapPainter.setPen(characterPen);
    mapPainter.drawEllipse(characterPos, 4, 4);
    if (characterTargettedPos != QPoint(-1, -1))
    {
        mapPainter.setPen(characterTargettedPen);
        mapPainter.drawEllipse(characterTargettedPos, 4, 4);
    }
    mapPainter.end();
    ui->L_MAP->setPixmap(QPixmap::fromImage(currentMapImage));
}

void MapWidget::tick()
{
    refresherSingleshot->start();
}

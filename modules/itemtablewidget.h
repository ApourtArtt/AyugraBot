#ifndef ITEMTABLEWIDGET_H
#define ITEMTABLEWIDGET_H

#include <QObject>
#include <QTableWidget>
#include <QMouseEvent>

/* Lot of things are missing and a rework on this class is needed :
 * - You can't stack items.
 * - You can't move a custom quantity of your item : all or nothing.
 * - Needs to grey forbidden cell (bag, special inv, ...)
 *   and give them a special value to handle it properly
*/

class ItemTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    ItemTableWidget(QWidget *parent);
    void moveItem(int cellSource, int cellDest);
    void modifyItem(QTableWidgetItem *item);

signals:
    void cellRightClick(ItemTableWidget *table, QTableWidgetItem *item);
    // void cellLeftClick(ItemTableWidget *item); // Not needed
    void cellDoubleLeftClick(ItemTableWidget *table, QTableWidgetItem *item);
    void dragAndDrop(ItemTableWidget *table, short cellSource, short cellDest, int quantity);

private slots:
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    QPair<int, int> posDragingItem;
};

#endif // ITEMTABLEWIDGET_H

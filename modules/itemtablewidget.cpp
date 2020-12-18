#include "itemtablewidget.h"

ItemTableWidget::ItemTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    posDragingItem.first = -1;
    posDragingItem.second = -1;
    setFocusPolicy(Qt::NoFocus);
    QPalette* palette = new QPalette();
    palette->setColor(QPalette::Highlight, Qt::transparent);
    setPalette(*palette);
}

void ItemTableWidget::mousePressEvent(QMouseEvent *e)
{
    QTableWidgetItem *itm = itemAt(mapFromGlobal(QCursor::pos()));
    if (e->button() == Qt::RightButton && itm)
        emit cellRightClick(this, itm);
    else if(e->button() == Qt::LeftButton && itm)
    {
        // emit cellLeftClick(itm); // Not needed
        posDragingItem.first = itm->row();
        posDragingItem.second = itm->column();
    }
    else
        QTableWidget::mousePressEvent(e);
}

void ItemTableWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    QTableWidgetItem *itm = itemAt(mapFromGlobal(QCursor::pos()));
    if (e->button() == Qt::LeftButton && itm)
        emit cellDoubleLeftClick(this, itm);
    else
        QTableWidget::mousePressEvent(e);
}

void ItemTableWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton && posDragingItem.first != -1 && posDragingItem.second != -1
            && currentColumn() >= 0 && currentRow() >= 0)
    {
        if(currentColumn() != posDragingItem.second || currentRow() != posDragingItem.first)
        {
            QTableWidgetItem *itemToRead = item(currentRow(), currentColumn());
            int quantity = 1;
            if(itemToRead != nullptr)
                if(!itemToRead->text().isEmpty())
                    quantity = itemToRead->text().remove(0, 1).toInt();
            emit dragAndDrop(this, static_cast<short>(posDragingItem.second + posDragingItem.first * columnCount())
                             , static_cast<short>(currentColumn() + currentRow() * columnCount()), quantity);
        }
    }
    posDragingItem.first = -1;
    posDragingItem.second = -1;
}

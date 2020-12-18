#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget *parent)
    : QLabel(parent)
{

}

void ClickableLabel::mousePressEvent(QMouseEvent *e)
{
    Qt::MouseButton bt = e->button();
    if(bt == Qt::LeftButton)
        emit leftClicked(e->pos());
    else if(bt == Qt::RightButton)
        emit rightClicked(e->pos());
}

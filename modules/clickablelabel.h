#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QMouseEvent>
#include <QLabel>

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    ClickableLabel(QWidget *parent = nullptr);

signals:
    void rightClicked(QPoint pos);
    void leftClicked(QPoint pos);

private:
    void mousePressEvent(QMouseEvent *e);
};

#endif // CLICKABLELABEL_H

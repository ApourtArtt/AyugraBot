#ifndef FORMBASE_H
#define FORMBASE_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QPushButton>

class FormBase : public QWidget
{
    Q_OBJECT

public:
    explicit FormBase(QWidget *parent = nullptr);
    ~FormBase();
    void ownSubWindow(QMdiSubWindow *sub);
    void close();
    void show();

private:
    QMdiSubWindow *subWindow;
};

#endif // FORMBASE_H

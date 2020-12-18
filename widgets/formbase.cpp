#include "formbase.h"

FormBase::FormBase(QWidget *parent) :
    QWidget(parent)
{
    subWindow = nullptr;
}

FormBase::~FormBase()
{

}

void FormBase::close()
{
    if(subWindow)
        subWindow->close();
}

void FormBase::show()
{
    if(subWindow)
        subWindow->show();
}

void FormBase::ownSubWindow(QMdiSubWindow *sub)
{
    subWindow = sub;
}

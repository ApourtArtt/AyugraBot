#include "drop.h"

bool Drop::isPublic() const
{
    // return ownerID == -1 || QDateTime::currentDateTime() > timeDrop.addSecs(DROP_TIMER);
    if(ownerID == -1)
        return true;
    if(QDateTime::currentDateTime() > timeDrop.addSecs(DROP_TIMER))
        return true;
    return false;
}

int Drop::getQuantity() const
{
    return quantity;
}

bool Drop::isQuest() const
{
    return isQuestItem;
}

int Drop::getOwnerID() const
{
    return ownerID;
}

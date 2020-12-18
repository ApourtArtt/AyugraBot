#ifndef DROP_H
#define DROP_H

#include "srcs/GameObjects/Entity/baseentity.h"
#include "srcs/Packets/Server/World/packetin.h"
#include "srcs/Packets/Server/World/packetdrop.h"
#include <QDateTime>

const int DROP_TIMER = 30;

class Drop : public BaseEntity
{
public:
    Drop(){ ownerID = 0; }
    template<typename T>
    Drop(T Packet)
        : BaseEntity(Packet)
    {
        quantity = Packet.getQuantity();
        isQuestItem = Packet.isQuest();
        ownerID = Packet.getOwnerID();
        timeDrop = QDateTime::currentDateTime();
    }
    bool isPublic() const;
    int getQuantity() const;
    bool isQuest() const;
    int getOwnerID() const;

private:
    int quantity;
    bool isQuestItem;
    int ownerID;
    QDateTime timeDrop;
};

#endif // DROP_H

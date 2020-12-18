#ifndef CHATINSTANCE_H
#define CHATINSTANCE_H

#include <QObject>
#include <QColor>
#include "srcs/Packets/Server/World/packetsayi2.h"
#include "srcs/Packets/Server/World/packetsayt.h"
#include "srcs/Packets/Server/World/packetspk.h"
#include "srcs/Packets/Server/World/packetsayr.h"
#include "srcs/Packets/Client/World/packetsay.h"

const QMap<ChatType, QColor> ChatTypeToColor =
{
    { ChatType::GENERAL_1,              QColor(255, 255, 255) },
    { ChatType::NOT_SHOWN_IN_CHAT,      QColor(255, 255, 255) },
    { ChatType::NOSMATE_1,              QColor(201, 157, 159) },
    { ChatType::PARTY,                  QColor(178, 243, 4)   },
    { ChatType::NOSMATE_2,              QColor(201, 157, 159) },
    { ChatType::WHISPER_PLAYER,         QColor(247, 124, 4)   },
    { ChatType::FAMILLY,                QColor(83, 192, 255)  },
    { ChatType::TS,                     QColor(254, 255, 171) },
    { ChatType::WHISPER_TO_GM,          QColor(247, 124, 4)   },
    { ChatType::WHISPER_FROM_GM,        QColor(247, 124, 4)   },
    { ChatType::SYSTEM_YELLOW,          QColor(254, 217, 12)  },
    { ChatType::SYSTEM_RED,             QColor(245, 92, 107)  },
    { ChatType::SYSTEM_GREEN,           QColor(14, 249, 2)    },
    { ChatType::SYSTEM_GREY,            QColor(226, 194, 255) },
    { ChatType::MESSAGE_SPEAKER,        QColor(226, 194, 255) },
    { ChatType::WHISPER_GM_PURPLE,      QColor(191, 108, 255) },
    { ChatType::WHISPER_PLAYER_2,       QColor(255, 127, 80)  },
    { ChatType::MESSAGE_SPEAKER_ITEM,   QColor(232, 146, 249) },
    { ChatType::MESSAGE_FROM_NOSCITY,   QColor(226, 194, 255) },
    { ChatType::MESSAGE_FROM_CYLLOAN,   QColor(226, 194, 255) }
};

class Message : public QObject
{
public:
    Message(QObject *parent);
    void setAuthor(EntityType _EntityType, int EntityID, QString Pseudonym);
    void setMessage(QString Message);
    void setProperty(ChatType _ChatType, short Channel = -1);
    QString getPseudonym() const;
    QString getMessage() const;
    QColor getColor() const;
    ChatType getChatType() const;

private:
    EntityType entityType;
    int entityID;
    QString pseudonym;
    QString message;
    ChatType chatType;
    short channel;
};


class ChatInstance : public QObject
{
    Q_OBJECT
public:
    ChatInstance(QObject *parent);
    ~ChatInstance();

    void handleSayi2Packet(PacketSayi2 Packet);
    void handleSaytPacket(PacketSayt Packet);
    void handleSpkPacket(PacketSpk Packet);
    void handleSayRPacket(PacketSayR Packet, QString pseudonym);
    QVector<Message*> getPendingMessages();
    void flush();
    void sendRawMessage(QString message);
    void sendFamillyMessage(QString message);
    void sendPartyMessage(QString message);
    void sendWhisperMessage(QString pseudonym, QString message);

signals:
    void messageReceived();
    void sendPacket(QString packet, bool privilege = false);

private:
    QVector<Message*> messages;
};

#endif // CHATINSTANCE_H

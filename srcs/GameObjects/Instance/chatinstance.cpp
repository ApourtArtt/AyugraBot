#include "chatinstance.h"
#include <QDebug>

ChatInstance::ChatInstance(QObject *parent)
    : QObject(parent)
{

}

ChatInstance::~ChatInstance()
{
    messages.clear();
}

void ChatInstance::handleSayi2Packet(PacketSayi2 Packet)
{
    Message *message = new Message(this);
    message->setAuthor(Packet.getEntityType(), Packet.getEntityID(), Packet.getPseudonym());
    message->setMessage(Packet.getMessage());
    message->setProperty(Packet.getChatType(), Packet.getChannel());
    messages.push_back(message);
    emit messageReceived();
}

void ChatInstance::handleSaytPacket(PacketSayt Packet)
{
    Message *message = new Message(this);
    message->setAuthor(Packet.getEntityType(), Packet.getEntityID(), Packet.getPseudonym());
    message->setMessage(Packet.getMessage());
    message->setProperty(Packet.getChatType());
    messages.push_back(message);
    emit messageReceived();
}

void ChatInstance::handleSpkPacket(PacketSpk Packet)
{
    Message *message = new Message(this);
    message->setAuthor(Packet.getEntityType(), Packet.getEntityID(), Packet.getPseudonym());
    message->setMessage(Packet.getMessage());
    message->setProperty(Packet.getChatType());
    messages.push_back(message);
    emit messageReceived();
}

void ChatInstance::handleSayRPacket(PacketSayR Packet, QString pseudonym)
{
    Message *message = new Message(this);
    message->setAuthor(Packet.getEntityType(), Packet.getEntityID(), pseudonym);
    message->setMessage(Packet.getMessage());
    message->setProperty(Packet.getChatType());
    messages.push_back(message);
    emit messageReceived();
}

QVector<Message *> ChatInstance::getPendingMessages()
{
    return messages;
}

void ChatInstance::flush()
{
    for(int i = 0 ; i < messages.size() ; i++)
        delete messages[i];
    messages.clear();
}

void ChatInstance::sendRawMessage(QString message)
{
    if(message.startsWith(":"))
        sendFamillyMessage(message);
    else if(message.startsWith(";"))
        sendPartyMessage(message);
    else if(message.startsWith("/"))
    {
        QString pseudonym = message.split(" ")[0];
        pseudonym.remove(0, 1);
        sendWhisperMessage(pseudonym, message.remove(0, message.indexOf(" ") + 1));
    }
    else
        sendPacket(PacketSay(message).getPacket());
}

void ChatInstance::sendFamillyMessage(QString message)
{
    sendPacket(message, true);
}

void ChatInstance::sendPartyMessage(QString message)
{
    sendPacket(message, true);
}

void ChatInstance::sendWhisperMessage(QString pseudonym, QString message)
{
    sendPacket("/" + pseudonym + " " + message, true);
}



Message::Message(QObject *parent)
    : QObject(parent)
{

}

void Message::setAuthor(EntityType _EntityType, int EntityID, QString Pseudonym)
{
    entityType = _EntityType;
    entityID = EntityID;
    pseudonym = Pseudonym;
}

void Message::setMessage(QString Message)
{
    message = Message;
}

void Message::setProperty(ChatType _ChatType, short Channel)
{
    chatType = _ChatType;
    channel = Channel;
}

QString Message::getPseudonym() const
{
    return pseudonym;
}

QString Message::getMessage() const
{
    return message;
}

QColor Message::getColor() const
{
    return ChatTypeToColor.value(chatType);
}

ChatType Message::getChatType() const
{
    return chatType;
}

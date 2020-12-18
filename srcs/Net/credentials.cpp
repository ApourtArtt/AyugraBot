#include "srcs/Net/credentials.h"

const QString Credentials::POSSIBLE_CHARACTER = "abcdef0123456789";

Credentials::Credentials(QString Username, QString Password, ConnectionType Connection, Lang Language, QString Gfuid, QObject *parent)
    : QObject(parent)
{
    username = Username;
    password = Password;
    connectionType = Connection;
    lang = Language;
    if(isGFUIDValid(gfuid))
        gfuid = Gfuid;
    else
        gfuid = generateGFUID();
}

Credentials::~Credentials()
{
    availableCharacters.clear();
}

QString Credentials::getUsername() const
{
    return username;
}

QString Credentials::getUsedUsername() const
{
    if(connectionType == ConnectionType::GFL)
        return langToIdString.key(lang) + "_" + username + " GF " + QString::number(langToIdLang.value(lang));
    return username;
}

QString Credentials::getPassword() const
{
    return password;
}

QString Credentials::getUsedPassword() const
{
    if(connectionType == ConnectionType::GFL)
        return "thisisgfmode";
    return password;
}

QString Credentials::getGFUID() const
{
    return gfuid;
}
ConnectionType Credentials::getConnectionType() const
{
    return connectionType;
}

bool Credentials::isValid() const
{
    return (username != nullptr &&
            password != nullptr &&
            connectionType != ConnectionType::NONE)
            ? true : false;
}

QString Credentials::generateGFUID()
{
    const int randomStringLength = 36;
    QString randomString;
    for(int i = 0; i < randomStringLength; i++)
    {
        int index = qrand() % POSSIBLE_CHARACTER.length();
        QChar nextChar = POSSIBLE_CHARACTER.at(index);
        if(i == 14)
            nextChar = '4';
        if(i == 8 || i == 13 || i == 18 || i == 23)
            nextChar = '-';
        randomString.append(nextChar);
    }
    return randomString;
};

bool Credentials::isGFUIDValid(QString Gfuid)
{
   if(Gfuid.size() != 36)
        return false;
   for(int i = 0 ; i < Gfuid.size() ; i++)
   {
       switch(i)
       {
       case 8: case 13: case 18: case 23:
           if(Gfuid.at(i) != '-')
               return false;
           break;
       case 14:
           if(Gfuid.at(i) != '4')
               return false;
           break;
       default:
           if(!POSSIBLE_CHARACTER.contains(Gfuid.at(i)))
               return false;
           break;
       }
   }
   return true;
}

QVector<MyCharacter *> Credentials::getAvailableCharacters() const
{
    return availableCharacters;
}

void Credentials::newCharacter(PacketClist Packet)
{
    availableCharacters.push_back(new MyCharacter(Packet, this));
}

void Credentials::emptyCharacterList()
{
    availableCharacters.clear();
}

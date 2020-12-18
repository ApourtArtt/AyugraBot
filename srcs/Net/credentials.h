#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <vector>
#include "srcs/GameObjects/Entity/mycharacter.h"

enum class Lang
{
    EN,
    DE,
    FR,
    IT,
    PL,
    ES,
    CZ,
    RU,
    TR
};

const QMap <Lang, int> langToIdLang
{
    { Lang::EN, 0 },
    { Lang::DE, 1 },
    { Lang::FR, 2 },
    { Lang::IT, 3 },
    { Lang::PL, 4 },
    { Lang::ES, 5 },
    { Lang::CZ, 6 },
    { Lang::RU, 7 },
    { Lang::TR, 8 }
};

const QMap <QString, Lang> langToIdString
{
    { "EN", Lang::EN },
    { "DE", Lang::DE },
    { "FR", Lang::FR },
    { "IT", Lang::IT },
    { "PL", Lang::PL },
    { "ES", Lang::ES },
    { "CZ", Lang::CZ },
    { "RU", Lang::RU },
    { "TR", Lang::TR }
};

enum class ConnectionType {
    NORMAL,
    GFL,
    NONE
};

class Credentials : public QObject
{
    Q_OBJECT
public:
    Credentials(QString Username, QString Password, ConnectionType Connection, Lang Language, QString Gfuid = "", QObject *parent = nullptr);
    ~Credentials();

    QString getUsername() const;
    QString getUsedUsername() const;
    QString getUsedPassword() const;
    QString getPassword() const;
    QString getGFUID() const;
    ConnectionType getConnectionType() const;
    bool isValid() const;
    static QString generateGFUID();
    static bool isGFUIDValid(QString Gfuid);
    QVector<MyCharacter*> getAvailableCharacters() const;
    void newCharacter(PacketClist Packet);
    void emptyCharacterList();

private:
    QString username;
    QString password;
    QString gfuid;
    Lang lang;
    ConnectionType connectionType;
    static const QString POSSIBLE_CHARACTER;
    QVector<MyCharacter*> availableCharacters;
};

#endif // CONNECTION_H

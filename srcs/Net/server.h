#ifndef SERVER_H
#define SERVER_H

#include <QString>
#include <QMap>
#include <vector>
#include "srcs/Packets/Server/Login/packetnstest.h"
#include "srcs/Packets/Server/Login/packetfailc.h"

struct address {
    QString ip;
    unsigned short port;
} typedef address;

struct serverIdentity {
    address add;
    QString name;
    short population;
    short server;
    short channel;
} typedef serverIdentity;

enum class ServerType {
    LOGIN,
    GAME,
    NONE
};

const QMap<QString, QString> RegionLocale
{
    { "EN", "en_EN" },
    { "DE", "de_DE" },
    { "FR", "fr_FR" },
    { "IT", "it_IT" },
    { "PL", "pl_PL" },
    { "ES", "es_ES" },
    { "CZ", "cz_CZ" },
    { "RU", "ru_RU" },
    { "TR", "tr_TR" }
};

const QMap<QString, unsigned short> RegionPort
{
    { "EN", 4000 },
    { "DE", 4001 },
    { "FR", 4002 },
    { "IT", 4003 },
    { "PL", 4004 },
    { "ES", 4005 },
    { "CZ", 4006 },
    { "RU", 4007 },
    { "TR", 4008 }
};

class Server : public QObject
{
    Q_OBJECT
public:
    Server(QString LoginIp, unsigned short LoginPort, short Server = -1, short Channel = -1, QObject *parent = nullptr);
    Server(QString LoginIp, QString country, short Server = -1, short Channel = -1, QObject *parent = nullptr);
    const QString getIP() const;
    unsigned short getPort() const;
    short getServer() const;
    short getChannel() const;
    void setIP(QString Ip);
    void setPort(unsigned short Port);
    void setServer(short Server);
    void setChannel(short Channel);
    QString getLocale() const;
    int getEncryptionKey() const;
    ServerType getServerType() const;
    void setServerType(ServerType server);
    bool isValid() const;
    QVector<serverIdentity> handleServerPacket(PacketNsTeST Packet);
    QVector<serverIdentity> getAvailableServers() const;
    bool isReadyForWorld() const;
    FailcType getError(PacketFailc Packet) const;

private:
    ServerType serverType;
    short server, channel;
    unsigned short port;
    QString locale;
    QString ip;
    int encryptionKey;
    bool ready;
    QVector<serverIdentity> servsIdentity;
};

#endif // SERVER_H

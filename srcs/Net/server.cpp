#include "server.h"

Server::Server(QString LoginIp, unsigned short LoginPort, short Server, short Channel, QObject *parent)
    : QObject(parent)
{
    ip = LoginIp;
    port = LoginPort;
    server = Server;
    channel = Channel;
    serverType = ServerType::NONE;
    ready = false;
    encryptionKey = -1;
    locale = RegionPort.key(port);
}

Server::Server(QString LoginIp, QString country, short Server, short Channel, QObject *parent)
    : QObject(parent)
{
    ip = LoginIp;
    port = RegionPort.value(country);
    server = Server;
    channel = Channel;
    serverType = ServerType::NONE;
    ready = false;
    encryptionKey = -1;
    locale = country;
}

const QString Server::getIP() const
{
    return ip;
}

unsigned short Server::getPort() const
{
    return port;
}

short Server::getServer() const
{
    return server;
}

short Server::getChannel() const
{
    return channel;
}

QString Server::getLocale() const
{
    return locale;
}

ServerType Server::getServerType() const
{
    return serverType;
}

int Server::getEncryptionKey() const
{
    return encryptionKey;
}

FailcType Server::getError(PacketFailc Packet) const
{
    return Packet.getErrorType();
}

void Server::setServerType(ServerType server)
{
    serverType = server;
}

void Server::setIP(QString Ip)
{
    ip = Ip;
}

void Server::setPort(unsigned short Port)
{
    port = Port;
}

void Server::setServer(short Server)
{
    server = Server;
}

void Server::setChannel(short Channel)
{
    channel = Channel;
}

bool Server::isValid() const
{
    return (ip != nullptr && port != 0) ? true : false;
}

bool Server::isReadyForWorld() const
{
    return (ready && channel > 0 && server > 0 && ip != nullptr && port != 0 && locale != nullptr) ? true : false;
}

QVector<serverIdentity> Server::handleServerPacket(PacketNsTeST Packet)
{
    encryptionKey = Packet.getEncryptionKey();
    QVector<serverIdentity> servIdentity;
    QStringList serverList = Packet.getServerLines();
    for(int i = 0 ; i < serverList.size() ; i++)
    {
        serverIdentity servIdentityTmp;
        address addressTmp;
        servIdentityTmp.name = Packet.getName(serverList[i]);
        servIdentityTmp.population = Packet.getPopulation(serverList[i]);
        servIdentityTmp.server = Packet.getServer(serverList[i]);
        servIdentityTmp.channel = Packet.getChannel(serverList[i]);
        addressTmp.ip = Packet.getIP(serverList[i]);
        addressTmp.port = Packet.getPort(serverList[i]);
        servIdentityTmp.add = addressTmp;
        servIdentity.push_back(servIdentityTmp);
    }
    if(server > 0 && channel > 0)
    {
        std::pair<QString, unsigned short> pair;
        pair = Packet.getServerInfo(serverList, server, channel);
        ip = pair.first;
        port = pair.second;
    }
    servsIdentity = servIdentity;
    ready = true;
    return servIdentity;
}

QVector<serverIdentity> Server::getAvailableServers() const
{
    return servsIdentity;
}

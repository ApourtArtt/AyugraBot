#include "network.h"

Network::Network(QObject *parent)
    : QObject(parent)
{
    mCrypto = nullptr;
    socket = new QTcpSocket(this);
    pulse = new QTimer(this);
    pulseRuntime = 0;
    pid = -1;
    encryptionKey = -1;
    connect(socket, &QTcpSocket::readyRead, this, [this]
    {
        QStringList packets = decrypt(socket->readAll());
        foreach (QString packet, packets)
            emit sig_recievedPacket(packet.replace("\n","").split(" "));
    });
    connect(socket, &QTcpSocket::connected, this, [this]
    {
        emit sig_connected();
    });
    connect(socket, &QTcpSocket::disconnected, this, [this]
    {
        emit sig_disconnected();
    });
    connect(pulse, &QTimer::timeout, this, [this]
    {
        pulseRuntime++;
        send(PacketPulse(pulseRuntime*60, (qrand() % 32 == 1) ? 1 : 0).getPacket());
    });
}

Network::~Network()
{
    pulse->stop();
    socket->close();
    delete pulse;
    delete mCrypto;
    delete socket;
    delete server;
}

void Network::configureCryptography(const QString &xHash, const QString &hash, const QString &version)
{
    if(mCrypto != nullptr)
        delete mCrypto;
    mCrypto = new Cryptography(xHash, hash, version, this);
}

bool Network::connectToLS(Server *serv)
{
    if(socket->isOpen())
        socket->disconnectFromHost();
    if(!mCrypto->isConfigured() || !serv->isValid() || serv->getServerType() != ServerType::NONE)
        return false;
    server = serv;
    socket->connectToHost(server->getIP(), server->getPort());
    return true;
}

void Network::connectWithCredentials(Credentials *creds)
{
    if(creds->getConnectionType() == ConnectionType::GFL)
        mCrypto->setGFLAccount(true);
    if(server->getServerType() == ServerType::LOGIN)
    {
        qDebug() << creds->getUsername();
        socket->write(mCrypto->createLoginPacket(creds->getUsername(), creds->getPassword(), creds->getGFUID(), server->getLocale()));
    }
    else if(server->getServerType() == ServerType::GAME)
    {
        QString temp = QString::number(getPid()) + " " + QString::number(encryptionKey);
        QByteArray temp2 = mCrypto->encryptGamePacket(temp, encryptionKey, true);
        socket->write(temp2);
        QTimer::singleShot(1000, this, [this, creds]
        {
            qDebug() << creds->getUsedUsername();
            send(creds->getUsedUsername(), true);
            send(creds->getUsedPassword(), true);
        });
    }
}

void Network::connectToGS(int key, QString ip, unsigned short port)
{
    if(server->getServerType() == ServerType::LOGIN)
    {
        socket->disconnectFromHost();
        encryptionKey = key;
        QTimer::singleShot(1000, [this, ip, port]
        {
            server->setServerType(ServerType::GAME);
            socket->connectToHost(ip, port);
        });
    }
}

void Network::disconnectFromServer()
{
    pulse->stop();
    socket->disconnectFromHost();
}

void Network::startPulsing()
{
    pulse->start(60000);
}

int Network::getPid()
{
    if(pid == -1)
        pid = qrand() % 65534;
    if(pid == 65534)
        pid = -1;
    pid++;
    return pid;
}

QStringList Network::decrypt(QByteArray msg)
{
    if(server->getServerType() == ServerType::LOGIN)
    {
        QString temp;
        temp = mCrypto->decryptLoginPacket(msg, static_cast<std::size_t>(msg.length()));
        return {temp};
    }
    return mCrypto->decryptGamePacket(msg, static_cast<std::size_t>(msg.length()));
}

QByteArray Network::encrypt(QString packet)
{
    if (server->getServerType() == ServerType::GAME)
        return mCrypto->encryptGamePacket(packet, encryptionKey, false);
    return {};
}

bool Network::send(QString packet, bool privilege)
{
    if(!privilege)
    {
        if(packet == "")                                 return false;
        if(server->getServerType() == ServerType::NONE)  return false;
        if(encryptionKey == -1)                          return false;
        if(!PacketProperties::isSendable(packet))        return false;
        if(PacketProperties::getPacketRole(packet) == PacketRole::LOGIN
        && server->getServerType() != ServerType::LOGIN) return false;
        if(PacketProperties::getPacketRole(packet) == PacketRole::WORLD
        && server->getServerType() != ServerType::GAME)  return false;
    }
    emit sig_sentPacket(packet);
    //qInfo() << "Sent: " << packet;
    QByteArray msg = encrypt(QString::number(getPid()) + " " + packet);
    socket->write(msg);
    return true;
}

#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include "srcs/Net/cryptography.h"
#include "srcs/Net/credentials.h"
#include "srcs/Net/server.h"
#include "srcs/Packets/Client/World/packetpulse.h"

class Network : public QObject
{
    Q_OBJECT
public:
    Network(QObject *parent);
    ~Network();

    bool send(QString packet, bool privilege = false);
    void configureCryptography(const QString &xHash, const QString &hash, const QString &version);
    bool isConfigured(){return mCrypto->isConfigured();}
    bool connectToLS(Server *serv);
    void connectWithCredentials(Credentials *creds);
    void connectToGS(int key, QString ip, unsigned short port);
    void disconnectFromServer();
    void startPulsing();

signals:
    void sig_connected();
    void sig_disconnected();
    void sig_recievedPacket(QStringList packet);
    void sig_sentPacket(QString packet);

private:
    QStringList decrypt(QByteArray msg);
    QByteArray encrypt(QString packet);
    int getPid();

    Cryptography *mCrypto;
    QTcpSocket *socket;
    QTimer *pulse;
    Server *server;

    int pulseRuntime;
    int pid, encryptionKey;
};

#endif // NETWORK_H

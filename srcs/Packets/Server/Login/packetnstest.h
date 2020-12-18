#ifndef PACKETNSTEST_H
#define PACKETNSTEST_H

#include "srcs/Packets/basepacket.h"
#include <QRegularExpression>

class PacketNsTeST : public BasePacket
{
public:
    PacketNsTeST(QStringList Packet);
    QString getUsername();
    bool hasGFFlag();
    int getEncryptionKey();
    QStringList getServerLines();

    static std::pair<QString, unsigned short> getServerInfo(QStringList serverList, short server, short channel);
    static bool isServerLine(QString line);
    static QString getIP(QString line);
    static unsigned short getPort(QString line);
    static short getPopulation(QString line);
    static short getServer(QString line);
    static short getChannel(QString line);
    static QString getName(QString line);
};

#endif // PACKETNSTEST_H

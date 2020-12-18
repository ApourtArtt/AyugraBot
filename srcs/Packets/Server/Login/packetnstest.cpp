#include "packetnstest.h"

PacketNsTeST::PacketNsTeST(QStringList Packet)
    : BasePacket(Packet)
{

}

QString PacketNsTeST::getUsername()
{
    return packet[3];
}

int PacketNsTeST::getEncryptionKey()
{
    return hasGFFlag() ? packet[5].toInt() : packet[2].toInt();
}

bool PacketNsTeST::hasGFFlag()
{
    return !isServerLine(packet[3]);
}

QStringList PacketNsTeST::getServerLines()
{
    QStringList serverList;
    for(int i = 0 ; i < packet.size() ; i++)
    {
        if(isServerLine(packet[i]))
            serverList.push_back(packet[i]);
    }
    return serverList;
}

bool PacketNsTeST::isServerLine(QString line)
{
    QRegularExpression re("^\\d+.\\d+.\\d+.\\d+."
                          ":\\d+"
                          ":\\d+"
                          ":\\d+"
                          ".\\d+"
                          ".+$");
    QRegularExpressionMatch match = re.match(line);
    return match.hasMatch();
}

std::pair<QString, unsigned short> PacketNsTeST::getServerInfo(QStringList serverList, short server, short channel)
{
    std::pair<QString, unsigned short> pair;
    QString ip("");
    unsigned short port = 0;
    QRegularExpression re("^\\d+.\\d+.\\d+.\\d+."
                          ":\\d+"
                          ":\\d+"
                          ":" + QString::number(server) +
                          "." + QString::number(channel) +
                          ".+$");
    QRegularExpressionMatch match;
    QString rightLine = "";
    for(int i = 0 ; i < serverList.size() && rightLine == "" ; i++)
    {
        match = re.match(serverList[i]);
        if(match.hasMatch())
            rightLine = serverList[i];
    }
    if(rightLine != "")
    {
        ip = getIP(rightLine);
        port = getPort(rightLine);
    }
    pair.first = ip;
    pair.second = port;
    return pair;
}

QString PacketNsTeST::getIP(QString line)
{
    QRegularExpression re("^(\\d+.\\d+.\\d+.\\d+.)"
                          ":(\\d+)"
                          ":(\\d+)"
                          ":(\\d+)"
                          ".(\\d+)"
                          ".(.+)$");
    QRegularExpressionMatch match = re.match(line);
    return match.captured(1);
}

unsigned short PacketNsTeST::getPort(QString line)
{
    QRegularExpression re("^(\\d+.\\d+.\\d+.\\d+.)"
                          ":(\\d+)"
                          ":(\\d+)"
                          ":(\\d+)"
                          ".(\\d+)"
                          ".(.+)$");
    QRegularExpressionMatch match = re.match(line);
    return match.captured(2).toUShort();
}

short PacketNsTeST::getPopulation(QString line)
{
    QRegularExpression re("^(\\d+.\\d+.\\d+.\\d+.)"
                          ":(\\d+)"
                          ":(\\d+)"
                          ":(\\d+)"
                          ".(\\d+)"
                          ".(.+)$");
    QRegularExpressionMatch match = re.match(line);
    return match.captured(3).toShort();
}

short PacketNsTeST::getServer(QString line)
{
    QRegularExpression re("^(\\d+.\\d+.\\d+.\\d+.)"
                          ":(\\d+)"
                          ":(\\d+)"
                          ":(\\d+)"
                          ".(\\d+)"
                          ".(.+)$");
    QRegularExpressionMatch match = re.match(line);
    return match.captured(4).toShort();
}

short PacketNsTeST::getChannel(QString line)
{
    QRegularExpression re("^(\\d+.\\d+.\\d+.\\d+.)"
                          ":(\\d+)"
                          ":(\\d+)"
                          ":(\\d+)"
                          ".(\\d+)"
                          ".(.+)$");
    QRegularExpressionMatch match = re.match(line);
    return match.captured(5).toShort();
}

QString PacketNsTeST::getName(QString line)
{
    QRegularExpression re("^(\\d+.\\d+.\\d+.\\d+.)"
                          ":(\\d+)"
                          ":(\\d+)"
                          ":(\\d+)"
                          ".(\\d+)"
                          ".(.+)$");
    QRegularExpressionMatch match = re.match(line);
    return match.captured(6);
}

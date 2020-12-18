#ifndef BASEPACKET_H
#define BASEPACKET_H

#include <QStringList>
#include <QMap>
#include "srcs/Packets/packetidentification.h"

/* About packets :
 * Need to const functions
 * Need to const packets objects
*/

class PacketProperties
{
public:
    PacketProperties(QString Packet)
    {
        if(PacketToHeader.contains(Packet))
            header = PacketToHeader.value(Packet);
        if(PacketToRole.contains(Packet))
            role = PacketToRole.value(Packet);
        if(PacketToType.contains(Packet))
            type = PacketToType.value(Packet);
    }

    PacketProperties(QStringList Packet)
    {
        if(PacketToHeader.contains(Packet[0]))
            header = PacketToHeader.value(Packet[0]);
        if(PacketToRole.contains(Packet[0]))
            role = PacketToRole.value(Packet[0]);
        if(PacketToType.contains(Packet[0]))
            type = PacketToType.value(Packet[0]);
    }

    static bool exist(QString header)
    {
        return PacketToHeader.contains(header);
    }

    static bool isSendable(QString packet)
    {
        QString header = packet.mid(0, packet.indexOf(' '));
        if(!exist(header))
            return false;
        if(PacketToType.contains(header))
        {
            if(PacketToType.value(header) == PacketType::CLIENT
            || PacketToType.value(header) == PacketType::BOTH)
                return true;
            else
                return false;
        }
        return false;
    }

    static PacketType getPacketType(QString packet)
    {
        QString header = packet.mid(0, packet.indexOf(' '));
        if(PacketToType.value(header) == PacketType::SERVER)
            return PacketType::SERVER;
        return PacketType::CLIENT;
    }

    static PacketRole getPacketRole(QString packet)
    {
        return PacketToRole.value(packet.mid(0, packet.indexOf(' ')));
    }

    PacketIdentifier getHeader()
    {
        return header;
    }

    PacketRole getRole()
    {
        return role;
    }

    PacketType getType()
    {
        return type;
    }

private:
    PacketIdentifier header;
    PacketRole role;
    PacketType type;
};

class BasePacket
{
public:
    BasePacket(QString Packet)
        : properties(Packet)
    {
        packet = QStringList({Packet});
    }

    BasePacket(QStringList Packet)
        : properties(Packet)
    {
        packet = Packet;
    }

    QString getPacket()
    {
        PacketType type = properties.getType();
        if(type == PacketType::CLIENT || type == PacketType::BOTH)
            return isSendable() ? packet.join(" ") : "";
        return packet.join(" ");
    }

    QString getPacketToDisplay()
    {
        return packet.join(" ");
    }

    QStringList getPacketsPart()
    {
        return packet;
    }

    PacketType getPacketType()
    {
        return properties.getType();
    }

    PacketIdentifier getPacketIdentifier()
    {
        return properties.getHeader();
    }

    PacketRole getPacketRole()
    {
        return properties.getRole();
    }

    virtual bool isSendable()
    {
        return sendable;
    }

protected:
    QStringList packet;
    PacketProperties properties;
    bool sendable;
};

#endif // BASEPACKET_H

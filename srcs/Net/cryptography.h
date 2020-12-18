#ifndef Cryptography_H
#define Cryptography_H

#include <QObject>
#include <sstream>
#include <QCryptographicHash>
#include <windows.h>
#include "srcs/Net/codegenerator.h"

class Cryptography : public QObject
{
    Q_OBJECT
public:
    explicit Cryptography(QString xHash, QString hash, QString version, QObject *parent = nullptr);
    QByteArray encryptGamePacket(const QString& buf, int session, bool is_session_packet = 0) const;
    std::vector<unsigned char> encryptLoginPacket(const QString& buf) const;
    QString decryptLoginPacket(const QByteArray& ba, std::size_t len) const;
    QStringList decryptGamePacket(const QByteArray& inp, std::size_t len);
    QString createLoginHash(const QString& user) const;
    QString createLoginVersion(void) const;
    int randomNumber(int min, int max) const;
    QString Sha512(const QString plainText) const;
    QByteArray createLoginPacket(const QString &username, const QString &password, const QString &gfuid, const QString &locale);
    void randomize() const;

    void setClientXhash(const QString &value);
    QString getClientXHash() const;
    void setClienthash(const QString &value);
    QString getClientHash() const;
    void setGFuid(const QString &value);
    QString getGFuid() const;
    void setVersion(const QString &value);
    QString getVersion() const;
    QString getLoginPacket() const;
    void setGFLAccount(bool value);
    bool isConfigured() const{return configured;}

    static QString getMd5FileHash(const QString &filename);
    static QString getVersionFile(const QString &filename);

private:

    QString clientXhash;
    QString clienthash;
    QString version;
    QString loginPacket;
    bool isGFLAccount;
    void completeGamePacketEncrypt(std::vector<unsigned char>& buf, int session, bool is_session_packet = 0) const;
    std::string last_current_packet;
    std::vector<unsigned char> last_buf;
    QString pwEncrypt(QString pw) const;
    bool configured;
};

#endif // Cryptography_H

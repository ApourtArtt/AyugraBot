#include "cryptography.h"

Cryptography::Cryptography(QString xHash, QString hash, QString versionA, QObject *parent)
    : QObject(parent)
{
    clientXhash = xHash;
    clienthash = hash;
    version = versionA;
    isGFLAccount = false;
    configured = true;
    loginPacket = "";
}

QString Cryptography::getMd5FileHash(const QString &filename)
{
    QFile f(filename);
    if (f.open(QFile::ReadOnly)) {
        QCryptographicHash hash(QCryptographicHash::Md5);
        if (hash.addData(&f)) {
            return hash.result().toHex();
        }
    }
    return "";
}

QString Cryptography::getVersionFile(const QString &filename)
{
    DWORD dwHandle;
    DWORD dwLen = GetFileVersionInfoSize(filename.toStdWString().c_str(), &dwHandle);
    LPVOID lpData = new BYTE[dwLen];
    GetFileVersionInfo(filename.toStdWString().c_str(), dwHandle, dwLen, lpData);
    VS_FIXEDFILEINFO *lpBuffer = nullptr;
    UINT uLen;
    VerQueryValue(lpData, QString("\\").toStdWString().c_str(), (LPVOID*)&lpBuffer, &uLen);
    return
    QString::number(( lpBuffer->dwFileVersionMS >> 16 ) & 0xffff ) + "." +
    QString::number( ( lpBuffer->dwFileVersionMS) & 0xffff ) + "." +
    QString::number( ( lpBuffer->dwFileVersionLS >> 16 ) & 0xffff ) + "." +
    QString::number( ( lpBuffer->dwFileVersionLS) & 0xffff );
}

QString Cryptography::getClientXHash() const
{
    return clientXhash;
}

QString Cryptography::getClientHash() const
{
    return clienthash;
}

QString Cryptography::getVersion() const
{
    return version;
}

QString Cryptography::decryptLoginPacket(const QByteArray& ba, std::size_t len) const
{
    std::vector<unsigned char> buf(ba.begin(), ba.end());
    std::string temp;
    QString output;
    std::transform(buf.begin(), buf.begin() + static_cast<long long>(len), std::back_inserter(temp),
        [](unsigned char c)
    {
        return c - 0xF;
    }
    );

    output = QString::fromLatin1(QByteArray(temp.c_str(), static_cast<int>(temp.length())));
    return output;
}

QString Cryptography::pwEncrypt(QString pw) const
{
        std::string password = pw.toStdString();
        const unsigned char secondtable[] = { 0x2E, 0x2A, 0x17, 0x4F, 0x20, 0x24, 0x47, 0x11, 0x5B, 0x37, 0x53,
                                          0x43, 0x15, 0x34, 0x45, 0x25, 0x4B, 0x1D, 0x2F, 0x58, 0x2B, 0x32, 0x63 };

        std::string hex, temp;
        std::stringstream ss;

        int pos = randomNumber(0, 23);
        char low, high;

        for(unsigned int i = 0; i < password.size(); i++)
                ss << std::uppercase << std::hex << static_cast<int>(password[i]);

        temp += ss.str();
        ss.str("");

        ss << std::uppercase << std::hex << static_cast<int>(secondtable[randomNumber(0, 23)]);

        for(unsigned int i = 0; i < temp.size(); i += 2)
        {
                high = secondtable[pos] & 0xF;
                low = (secondtable[pos] & 0xF0) >> 4;

                ss << std::uppercase << std::hex << static_cast<int>(low);
                ss << std::uppercase << temp[i];
                ss << std::uppercase << std::hex << static_cast<int>(high);
                ss << std::uppercase << temp[i + 1];

                pos == 22 ? pos = 0 : pos++;
        }

        return QString::fromStdString(ss.str());
}

std::vector<unsigned char> Cryptography::encryptLoginPacket(const QString& buf) const
{
    std::string sbuf = buf.toStdString();

    std::vector<unsigned char> output;
    std::transform(sbuf.begin(), sbuf.end(), std::back_inserter(output),
        [](char c)
    {
        return (c ^ 0xC3) + 0xF;
    }
    );
    output.push_back(216);
    return output;
}

QString Cryptography::getLoginPacket() const
{
    return loginPacket;
}

void Cryptography::setGFLAccount(bool value)
{
    isGFLAccount = value;
}

QByteArray Cryptography::createLoginPacket(const QString& username, const QString& password, const QString& gfuid, const QString &locale)
{
    QByteArray output;
    std::vector<unsigned char> temp;
    CodeGenerator codeGen(username, password, locale, gfuid, this);
    QString code = codeGen.getCode();
    QString loginhash = Cryptography::createLoginHash(username);
    QString passwordhash = Cryptography::Sha512(password);
    QString version = Cryptography::createLoginVersion();
    QString beginn = "NoS0577 " + code;
    loginPacket = beginn + "  " + gfuid + " 002ADCCF " + QString::number(langToId.value(locale)) + "" + version + " 0 " + loginhash;
    qDebug() << loginPacket;
    temp = Cryptography::encryptLoginPacket(loginPacket);
    for (auto &var : temp)
    {
        output.append(static_cast<char>(var));
    }
    return output;
}

QString Cryptography::createLoginHash(const QString& user) const
{
    QString output;
    QString login_string_to_hash = clientXhash.toUpper();
    login_string_to_hash += clienthash.toUpper();
    if(!isGFLAccount)
        login_string_to_hash += user;
    QByteArray textTemp = login_string_to_hash.toUtf8();
    output = QString(QCryptographicHash::hash((textTemp),QCryptographicHash::Md5).toHex());
    return output.toUpper();
}

QString Cryptography::createLoginVersion(void) const
{
    std::stringstream output;
    output //<< "00" << std::uppercase << std::hex << int(randomNumber(0,126))
        //<< std::uppercase << std::hex << int(randomNumber(0,126))
        //<< std::uppercase << std::hex << int(randomNumber(0,126))
        << '\v' << version.toStdString();
    return QString::fromStdString(output.str());
}

int Cryptography::randomNumber(int min, int max) const
{
    if (min > max)
    {
        int Temp = min;
        min = max;
        max = Temp;
    }
    return ((rand()%(max-min+1))+min);
}


QString Cryptography::Sha512(const QString plainText) const
{
    QString output;
    QByteArray textTemp = plainText.toUtf8();
    output = QString(QCryptographicHash::hash((textTemp),QCryptographicHash::Sha512).toHex());
    return output.toUpper();
}

QStringList Cryptography::decryptGamePacket(const QByteArray& inp, std::size_t len)
{
    std::vector<unsigned char> buf(inp.begin(), inp.end());
    buf.insert(buf.begin(), last_buf.begin(), last_buf.end());
    last_buf.clear();
    len = buf.size();
    std::vector<std::string> output;
    QStringList normOutput;
    std::string current_packet;
    static const char keys[] = {' ','-','.','0','1','2','3','4','5','6','7','8','9','n'};
    std::size_t index = 0;
    unsigned char currentByte = 0, length = 0, first = 0, second = 0;
    while (index < len)
    {
        currentByte = buf[index];
        ++index;
        if (currentByte == 0xFF)
        {
            output.push_back(current_packet);
            current_packet = "";
            continue;
        }

        length = currentByte & 0x7F;
        if (currentByte & 0x80)
        {
            while (length)
            {
                if (index <= len)
                {
                    currentByte = buf[index];
                    ++index;
                    first = static_cast<unsigned char>(keys[signed(((currentByte & 0xF0u) >> 4) - 1)]);
                    if (first != 0x6E)
                        current_packet += static_cast<char>(first);
                    if (length <= 1)
                        break;

                    second = static_cast<unsigned char>(keys[(currentByte & 0xF) - 1]);
                    if (second != 0x6E)
                        current_packet += static_cast<char>(second);
                    length -= 2;
                }
                else
                {
                    --length;
                }
            }
        }
        else
        {
            while (length)
            {
                if (index <= len)
                {
                    current_packet += static_cast<char>(buf[index] ^ 0xFF);
                    ++index;
                }

                --length;
            }
        }
    }
    if(current_packet.length()>0){
        last_buf = buf;
    }
    else
    {
        for(unsigned int i = 0; i < output.size();i++)
            normOutput.append(QString::fromLatin1(QByteArray(output[i].c_str(), static_cast<int>(output[i].length()))));
        return normOutput;
    }
    return {};
}

QByteArray Cryptography::encryptGamePacket(const QString& inp, int session, bool is_session_packet) const
{
    std::string buf = inp.toLatin1().toStdString();
    std::size_t packet_length = buf.size();
    std::string packet_mask;
    std::transform(buf.begin(), buf.end(), std::back_inserter(packet_mask),
        [](char c)
    {
        Q_UNUSED(c)
        return '0';
    }
    );

    std::vector<unsigned char> output;
    std::size_t sequences = 0, sequence_counter = 0;
    std::size_t last_position = 0, current_position = 0, length = 0;
    unsigned char current_byte = 0;
    while (current_position <= packet_length)
    {
        last_position = current_position;
        while (current_position < packet_length && packet_mask[current_position] == '0')
            ++current_position;

        if (current_position)
        {
            length = (current_position - last_position);
            sequences = (length / 0x7E);
            for (std::size_t i = 0; i < length; ++i, ++last_position)
            {
                if (i == (sequence_counter * 0x7E))
                {
                    if (!sequences)
                    {
                        output.push_back(static_cast<unsigned char>(length - i));
                    }
                    else
                    {
                        output.push_back(0x7E);
                        --sequences;
                        ++sequence_counter;
                    }
                }

                output.push_back(static_cast<unsigned char>(buf[last_position] ^ 0xFF));
            }
        }

        if (current_position >= packet_length)
            break;

        last_position = current_position;
        while (current_position < packet_length && packet_mask[current_position] == '1')
            ++current_position;

        if (current_position)
        {
            length = (current_position - last_position);
            sequences = (length / 0x7E);
            for (std::size_t i = 0; i < length; ++i, ++last_position)
            {
                if (i == (sequence_counter * 0x7E))
                {
                    if (!sequences)
                    {
                        output.push_back(static_cast<unsigned char>((length - i)) | 0x80);
                    }
                    else
                    {
                        output.push_back(0x7E | 0x80);
                        --sequences;
                        ++sequence_counter;
                    }
                }

                current_byte = static_cast<unsigned char>(buf[last_position]);
                switch (current_byte)
                {
                case 0x20:
                    current_byte = 1;
                    break;
                case 0x2D:
                    current_byte = 2;
                    break;
                case 0x2E:
                    current_byte = 3;
                    break;
                case 0xFF:
                    current_byte = 0xE;
                    break;
                default:
                    current_byte -= 0x2C;
                    break;
                }

                if (current_byte != 0x00)
                {
                    if (i % 2 == 0)
                    {
                        output.push_back(static_cast<unsigned char>(current_byte << 4));
                    }
                    else
                    {
                        output.back() |= current_byte;
                    }
                }
            }
        }
    }

    output.push_back(0xFF);
    completeGamePacketEncrypt(output, session, is_session_packet);
    QByteArray temp;
    for (auto &var : output)
    {
        temp.append(static_cast<char>(var));
    }
    return temp;
}

void Cryptography::completeGamePacketEncrypt(std::vector<unsigned char>& buf, int session, bool is_session_packet) const
{
    unsigned char session_number = (((session >> 6) & 0xFF) & 0x80000003);

    unsigned char session_key = (session & 0xFF);

    if (is_session_packet)
        session_number = static_cast<unsigned char>(-1);

    switch (session_number)
    {
    case 0:
        for (std::size_t i = 0; i < buf.size(); ++i)
            buf[i] = (buf[i] + (session_key + 0x40));
        break;

    case 1:
        for (std::size_t i = 0; i < buf.size(); ++i)
            buf[i] = (buf[i] - (session_key + 0x40));
        break;

    case 2:
        for (std::size_t i = 0; i < buf.size(); ++i)
            buf[i] = ((buf[i] ^ 0xC3) + (session_key + 0x40));
        break;

    case 3:
        for (std::size_t i = 0; i < buf.size(); ++i)
            buf[i] = ((buf[i] ^ 0xC3) - (session_key + 0x40));
        break;

    default:
        for (std::size_t i = 0; i < buf.size(); ++i)
            buf[i] = buf[i] + 0x0F;
        break;
    }
}

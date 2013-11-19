#ifndef RC6_H
#define RC6_H

#include <QString>
#include <string.h>

#include <QDebug>

#include <QFile>

#include "block.h"
#include "roundkey.h"

class RC6
{
private:
    int w, r, l;
    std::string key;

    RoundKey *round_key;
    Block block;

    int ReadBlock(QDataStream &in);
    void WriteBlock(QDataStream& out);

    void EncryptionBlock();
    void DecryptionBlock();

    quint64 mod(quint64 number);

public:
    RC6();
    RC6(int _w, int _r, int _l, QString _key);

    void Encryption();
    void Decryption();
};

#endif // RC6_H

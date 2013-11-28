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

    int ReadBlock(Block &block_for_read, QDataStream &in, int count = 4);
    void WriteBlock(Block block_for_write, QDataStream &out, int count = 4);

    Block EncryptionBlock(Block block_for_en);
    Block DecryptionBlock(Block block_for_de);

    quint64 mod(quint64 number);

public:
    RC6();
    RC6(int _w, int _r, int _l, QString _key);

    void Encryption_mode_1(QString in_stirng, QString out_string);
    void Encryption_mode_2(QString in_stirng, QString out_string, std::string InitVector);
    void Encryption_mode_3(QString in_stirng, QString out_string, std::string InitVector, int shift);
    void Encryption_mode_4(QString in_stirng, QString out_string, std::string InitVector, int shift);

    void Decryption_mode_1(QString in_stirng, QString out_string);
    void Decryption_mode_2(QString in_stirng, QString out_string, std::string InitVector);
    void Decryption_mode_3(QString in_stirng, QString out_string, std::string InitVector, int shift);
    void Decryption_mode_4(QString in_stirng, QString out_string, std::string InitVector, int shift);
};

#endif // RC6_H

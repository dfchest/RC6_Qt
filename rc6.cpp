#include "rc6.h"

RC6::RC6()
{
    key = "0123456789012345";

    w = 32;
    r = 20;
    l = 16;

    round_key = new RoundKey(w, r, l, key);
}

RC6::RC6(int _w, int _r, int _l, QString _key)
{
    key = _key.toStdString();

    w = _w;
    r = _r;
    l = _l;

    round_key = new RoundKey(w, r, l, key);
}

void RC6::Encryption_mode_1(QString in_stirng, QString out_string)
{
    QFile* f1 = new QFile(in_stirng);
    f1->open(QIODevice::ReadOnly);
    QDataStream in(f1);

    QFile* f2 = new QFile(out_string);
    f2->open(QIODevice::WriteOnly);
    QDataStream out(f2);

    round_key->Initialization(key);

    while( ReadBlock(block, in) )
        WriteBlock( EncryptionBlock(block), out );

    f1->close();
    f2->close();
}

void RC6::Encryption_mode_2(QString in_stirng, QString out_string, std::string InitVector)
{
    QFile* f1 = new QFile(in_stirng);
    f1->open(QIODevice::ReadOnly);
    QDataStream in(f1);

    QFile* f2 = new QFile(out_string);
    f2->open(QIODevice::WriteOnly);
    QDataStream out(f2);

    round_key->Initialization(key);

    Block tmp = Block(InitVector);

    while( ReadBlock(block, in) )
    {
        block = block xor tmp;

        block = EncryptionBlock(block);

        WriteBlock( block, out);

        tmp = block;
    }

    f1->close();
    f2->close();
}

void RC6::Encryption_mode_3(QString in_stirng, QString out_string, std::string InitVector, int shift)
{
    QFile* f1 = new QFile(in_stirng);
    f1->open(QIODevice::ReadOnly);
    QDataStream in(f1);

    QFile* f2 = new QFile(out_string);
    f2->open(QIODevice::WriteOnly);
    QDataStream out(f2);

    round_key->Initialization(key);

    Block tmp = Block(InitVector);
    Block tmp_En;

    while( ReadBlock(block, in, shift) )
    {
        tmp_En = EncryptionBlock(tmp);

        block = block xor tmp_En;

        WriteBlock(block, out, shift);

        tmp.ShiftLeft(shift);

        for(int i = 0; i < shift; i++)
            tmp[4-shift+i] = block[i];
    }

    f1->close();
    f2->close();
}

void RC6::Encryption_mode_4(QString in_stirng, QString out_string, std::string InitVector, int shift)
{
    QFile* f1 = new QFile(in_stirng);
    f1->open(QIODevice::ReadOnly);
    QDataStream in(f1);

    QFile* f2 = new QFile(out_string);
    f2->open(QIODevice::WriteOnly);
    QDataStream out(f2);

    round_key->Initialization(key);

    Block tmp = Block(InitVector);
    Block tmp_En;

    while( ReadBlock(block, in, shift) )
    {
        tmp_En = EncryptionBlock(tmp);

        block = block xor tmp_En;

        WriteBlock(block, out, shift);

        tmp.ShiftLeft(shift);

        for(int i = 0; i < shift; i++)
            tmp[4-shift+i] = tmp_En[i];
    }

    f1->close();
    f2->close();
}

void RC6::Decryption_mode_1(QString in_stirng, QString out_string)
{
    QFile* f1 = new QFile(in_stirng);
    f1->open(QIODevice::ReadOnly);
    QDataStream in(f1);

    QFile* f2 = new QFile(out_string);
    f2->open(QIODevice::WriteOnly);
    QDataStream out(f2);

    round_key->Initialization(key);

    while( ReadBlock(block, in) )
        WriteBlock(DecryptionBlock(block), out);

    f1->close();
    f2->close();
}

void RC6::Decryption_mode_2(QString in_stirng, QString out_string, std::string InitVector)
{
    QFile* f1 = new QFile(in_stirng);
    f1->open(QIODevice::ReadOnly);
    QDataStream in(f1);

    QFile* f2 = new QFile(out_string);
    f2->open(QIODevice::WriteOnly);
    QDataStream out(f2);

    round_key->Initialization(key);

    Block tmp_En = Block(InitVector);
    Block tmp;

    while( ReadBlock(block, in) )
    {
        tmp = block;

        block = DecryptionBlock(block);

        block = block xor tmp_En;

        WriteBlock(block, out);

        tmp_En = tmp;
    }

    f1->close();
    f2->close();
}

void RC6::Decryption_mode_3(QString in_stirng, QString out_string, std::string InitVector, int shift)
{
    QFile* f1 = new QFile(in_stirng);
    f1->open(QIODevice::ReadOnly);
    QDataStream in(f1);

    QFile* f2 = new QFile(out_string);
    f2->open(QIODevice::WriteOnly);
    QDataStream out(f2);

    round_key->Initialization(key);

    Block tmp = Block(InitVector);
    Block tmp_in, tmp_En;

    while( ReadBlock(block, in, shift) )
    {
        tmp_En = EncryptionBlock(tmp);

        tmp_in = block;

        block = block xor tmp_En;

        WriteBlock(block, out, shift);

        tmp.ShiftLeft(shift);

        for(int i = 0; i < shift; i++)
            tmp[4-shift+i] = tmp_in[i];
    }

    f1->close();
    f2->close();
}

void RC6::Decryption_mode_4(QString in_stirng, QString out_string, std::string InitVector, int shift)
{
    QFile* f1 = new QFile(in_stirng);
    f1->open(QIODevice::ReadOnly);
    QDataStream in(f1);

    QFile* f2 = new QFile(out_string);
    f2->open(QIODevice::WriteOnly);
    QDataStream out(f2);

    round_key->Initialization(key);

    Block tmp = Block(InitVector);
    Block tmp_En;

    while( ReadBlock(block, in, shift) )
    {
        tmp_En = EncryptionBlock(tmp);

        block = block xor tmp_En;

        WriteBlock(block, out, shift);

        tmp.ShiftLeft(shift);

        for(int i = 0; i < shift; i++)
            tmp[4-shift+i] = tmp_En[i];
    }

    f1->close();
    f2->close();
}

Block RC6::EncryptionBlock(Block block_for_en)
{
    Block tmp = block_for_en;

    quint64  t, u, logw = qLn(w)/qLn(2);

    round_key->Advanced();

    tmp[1] = mod(tmp[1] + (*round_key)[0]);
    tmp[3] = mod(tmp[3] + (*round_key)[1]);

    for( int i = 1; i < r+1; i++ )
    {
        t = BCS::Shift(mod( tmp[1] * ( 2 * tmp[1] + 1 ) ), w, logw, toLeft);
        u = BCS::Shift(mod( tmp[3] * ( 2 * tmp[3] + 1 ) ), w, logw, toLeft);

        tmp[0] = mod(BCS::Shift(tmp[0] xor t, w, u, toLeft) + (*round_key)[2*i]);
        tmp[2] = mod(BCS::Shift(tmp[2] xor u, w, t, toLeft) + (*round_key)[2*i + 1]);

        tmp.ShiftLeft();
    }

    tmp[0] = mod(tmp[0] + (*round_key)[2*r + 2]);
    tmp[2] = mod(tmp[2] + (*round_key)[2*r + 3]);

    return tmp;
}

Block RC6::DecryptionBlock(Block block_for_de)
{
    Block tmp = block_for_de;

    quint64  t, u, logw = qLn(w)/qLn(2);

    round_key->Advanced();

    tmp[2] = mod(tmp[2] - (*round_key)[2*r +3]);
    tmp[0] = mod(tmp[0] - (*round_key)[2*r +2]);

    for( int i = r; i > 0; i-- )
    {
        tmp.ShiftRight();

        t = BCS::Shift(mod(tmp[1] * ( 2 * tmp[1] + 1 ) ), w, logw, toLeft);
        u = BCS::Shift(mod(tmp[3] * ( 2 * tmp[3] + 1 ) ), w, logw, toLeft);

        tmp[0] = BCS::Shift(mod(tmp[0] - (*round_key)[2*i]), w, u, toRight) xor t;
        tmp[2] = BCS::Shift(mod(tmp[2] - (*round_key)[2*i + 1]), w, t, toRight) xor u;
    }

    tmp[3] = mod(tmp[3] - (*round_key)[1]);
    tmp[1] = mod(tmp[1] - (*round_key)[0]);

    return tmp;
}

int RC6::ReadBlock(Block &block_for_read, QDataStream &in, int count)
{
    block_for_read.set(0, 0, 0, 0);

    if( in.status() == QDataStream::ReadPastEnd ) return 0;

    quint8 byte;
    bool f = false;

    int i, j;

    for( i = 0; i < count; i++ )
    {
        for( j = 0; j < w/8; j++)
        {
            block_for_read[i] = block_for_read[i] << 8;

            if( ! ( in.status() == QDataStream::ReadPastEnd) )
                in >> byte;

            if( ! ( in.status() == QDataStream::ReadPastEnd) )
            {
                block_for_read[i] |= byte;
                f = true;
            }
        }

        if( in.status() == QDataStream::ReadPastEnd )
            if(f)
                return 1;
            else
                return 0;
    }

    if(f)
        return 1;
    else
        return 0;
}

void RC6::WriteBlock(Block block_for_write, QDataStream &out, int count)
{
    for( int i = 0; i < count; i++ )
        switch (w)
        {
            case 16 :
                out << (quint16)block_for_write[i];
                break;

            case 32 :
                out << (quint32)block_for_write[i];
                break;

            case 64 : default :
                out << (quint64)block_for_write[i];
                break;
        }
}


quint64 RC6::mod(quint64 number)
{
    if( w == 64)
        return (quint64)number;

    quint64 pow = qPow(2, w);

    return number % pow;
}

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

void RC6::Encryption()
{
    QFile* f1 = new QFile("C:\\QtProject\\in.txt");
    f1->open(QIODevice::ReadOnly);
    QDataStream in(f1);

    QFile* f2 = new QFile("C:\\QtProject\\out.txt");
    f2->open(QIODevice::WriteOnly);
    QDataStream out(f2);

    while( ReadBlock(in) )
    {
        WriteBlock(out);
    }

    f1->close();
    f2->close();
}

int RC6::ReadBlock(QDataStream &in)
{
    block.set(0, 0, 0, 0);

    if( in.status() == QDataStream::ReadPastEnd ) return 0;

    quint8 byte;

    int i, j;

    for( i = 0; i < 4; i++ )
    {
        for( j = 0; j < w/8; j++)
        {
            block[i] = block[i] << 8;

            if( ! ( in.status() == QDataStream::ReadPastEnd) )
                in >> byte;

            if( ! ( in.status() == QDataStream::ReadPastEnd) )
                block[i] |= byte;
        }

        if( in.status() == QDataStream::ReadPastEnd )
            return 1;
    }
    return 1;
}

void RC6::WriteBlock(QDataStream &out)
{
    for( int i = 0; i < 4; i++ )
        switch (w)
        {
            case 16 :
                out << (quint16)block[i];
                break;

            case 32 :
                out << (quint32)block[i];
                break;

            case 64 : default :
                out << (quint64)block[i];
                break;
        }
}

void RC6::EncryptionBlock()
{
    quint64  t, u;

    block[1] = (block[1] + (*round_key)[0]) % (quint64)qPow(2, w);
    block[3] = (block[3] + (*round_key)[1]) % (quint64)qPow(2, w);

    for( int i = 1; i < r+1; i++ )
    {
        t = BCS::Shift(block[1] * ( 2 * block[1] + 1 ), w, w);
        u = BCS::Shift(block[3] * ( 2 * block[3] + 1 ), w, w);

    }
}

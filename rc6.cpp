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
    f1->open(QIODevice::ReadOnly | QIODevice::Unbuffered);
    QDataStream in(f1);

    while( ReadBlock(in) )
    {
        qDebug() << block[0] << block[1] << block[2] << block[3];
    }
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
            byte = 0;
            block[i] = block[i] << 8;

            if( ! ( in.status() == QDataStream::ReadPastEnd) )
            {
                in >> byte;
                block[i] |= byte;
            }
        }

        if( in.status() == QDataStream::ReadPastEnd )
            return 1;
    }
    return 1;
}

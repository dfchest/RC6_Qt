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
    QFile* f1 = new QFile("D:\\in.txt");
    f1->open(QIODevice::ReadOnly);
    QDataStream in(f1);

    quint16 t;

    in >> t;
    block[0] = t;

    in >> t;
    block[1] = t;

    in >> t;
    block[2] = t;

    in >> t;
    qDebug() << in.status();
    block[3] = t;

    qDebug() << block[0] << block[1] << block[2] << block[3];
}

int RC6::ReadBlock(QDataStream &in)
{
    if( in.status() == QDataStream::ReadPastEnd ) return 0;


}

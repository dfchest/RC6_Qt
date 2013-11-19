#ifndef ROUNDKEY_H
#define ROUNDKEY_H

#include <QDebug>

#include <QTypeInfo>
#include <QVector>
#include <QString>
#include <string.h>

#include <qmath.h>

#include "bcs.h"

#define P16 0xb7e1
#define P32 0xb7e15163
#define P64 0xb7e151638aed2a6b

#define Q16 0x9e37
#define Q32 0x9e3779b9
#define Q64 0x9e3779b97f4a7c15

class RoundKey
{
private:
    std::string key;
    QVector<quint64> AdvancedKey;

    quint64 a, b;

    int w, r, l;

    quint64 ReadWordFromKey(int j);
    void WriteWordToKey(int j);

public:
    RoundKey();
    RoundKey(int _w, int _r, int _l, std::string _key);

    void Advanced();
    void Initialization(std::string _key);

    quint64 & operator [] (int n) { return AdvancedKey[n]; }
};

#endif // ROUNDKEY_H

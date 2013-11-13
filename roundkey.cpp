#include "roundkey.h"

RoundKey::RoundKey()
{
    key = "0123456789012345";

    w = 32;
    r = 20;
    l = 16;

    AdvancedKey.append(P32);

    for (int i = 1; i < 44; i++)
        AdvancedKey.append(AdvancedKey[i - 1] + Q32);

    a = b = 0;

    qDebug() << AdvancedKey;
}

RoundKey::RoundKey(int _w, int _r, int _l, std::string _key)
{
    key = _key;

    w = _w;
    r = _r;
    l = _l;

    switch (w)
    {
        case 16 :
            AdvancedKey.append(P16);
            for (int i = 1; i < 2 * r + 4; i++)
                AdvancedKey.append(AdvancedKey[i - 1] + Q16);

            break;

        case 32 :
            AdvancedKey.append(P32);
            for (int i = 1; i < 2 * r + 4; i++)
                AdvancedKey.append(AdvancedKey[i - 1] + Q32);

            break;

        case 64 : default :
            AdvancedKey.append(P64);
            for (int i = 1; i < 2 * r + 4; i++)
                AdvancedKey.append(AdvancedKey[i - 1] + Q64);

            break;
    }

    a = b = 0;

    qDebug() << AdvancedKey;
}

void RoundKey::Advanced()
{
    int tau = 8 * l / w;
    int k = qMax(2 * r + 4, tau);

    int i = 0, j = 0;

    for (int m = 0; m < k; m++)
    {
        AdvancedKey[i] = BCS::Shift((AdvancedKey[i] + a + b), w, -3);

        a = AdvancedKey[i];

        b = BCS::Shift(ReadWordFromKey(j) + a + b, w, a + b);

        WriteWordToKey(j);

        i = (i+1)%(2*r+4);
        j = (j+1)%tau;
    }

    qDebug() << AdvancedKey;
}


quint64 RoundKey::ReadWordFromKey(int j)
{
    quint64 k = 0;

    for(int i = 0; i < w/8; i++ )
    {
        k = k << 8;
        k = k | key[j+i];
    }

    return k;
}

void RoundKey::WriteWordToKey(int j)
{
    quint64 _b = b;

    for(int i = w/8 - 1; i >= 0; i-- )
    {
        key[j+i] = (uint8_t)_b;
        _b = _b >> 8;
    }
}

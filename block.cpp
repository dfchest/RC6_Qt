#include "block.h"

Block::Block()
{
    words.append(0);
    words.append(0);
    words.append(0);
    words.append(0);
}

Block::Block(quint64 a, quint64 b, quint64 c, quint64 d)
{
    words.append(a);
    words.append(b);
    words.append(c);
    words.append(d);
}

Block::Block(std::string InitVector)
{
    int l = InitVector.length() / 4;

    for(int i = 0; i < 4; i++)
    {
        quint64 k = 0;

        for(int j = 0; j < l; j++)
        {
            k = k << 8;
            k = k | InitVector[l*i+j];
        }

        words.append(k);
    }
}

void Block::ShiftLeft(int count)
{
    for(int i = 0; i < count; i++)
        words.move(0, 3);
}

void Block::ShiftRight(int count)
{
    for(int i = 0; i < count; i++)
        words.move(3, 0);
}

void Block::set(quint64 a, quint64 b, quint64 c, quint64 d)
{
    words[0] = a;
    words[1] = b;
    words[2] = c;
    words[3] = d;
}

Block Block::operator xor (Block r)
{
    return Block(words[0] xor r[0],
                 words[1] xor r[1],
                 words[2] xor r[2],
                 words[3] xor r[3]);
}

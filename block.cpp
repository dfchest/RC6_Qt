#include "block.h"

Block::Block()
{
    words.append(0);
    words.append(0);
    words.append(0);
    words.append(0);
}

Block::Block(int a, int b, int c, int d)
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
            k = k | InitVector[i+j];
        }

        words.append(k);
    }
}

void Block::ShiftLeft()
{
    words.move(0, 3);
}

void Block::ShiftRight()
{
    words.move(3, 0);
}

void Block::set(int a, int b, int c, int d)
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

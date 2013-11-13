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

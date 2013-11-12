#include "fourwords.h"

FourWords::FourWords()
{
    words.append(0);
    words.append(0);
    words.append(0);
    words.append(0);
}

FourWords::FourWords(int a, int b, int c, int d)
{
    words.append(a);
    words.append(b);
    words.append(c);
    words.append(d);
}

void FourWords::ShiftLeft()
{
    words.move(0, 3);
}

void FourWords::ShiftRight()
{
    words.move(3, 0);
}

void FourWords::set(int a, int b, int c, int d)
{
    words[0] = a;
    words[1] = b;
    words[2] = c;
    words[3] = d;
}

#ifndef FOURWORDS_H
#define FOURWORDS_H

#include <QList>

class Block
{
private:
    QList<quint64> words;

public:
    Block();
    Block(quint64 a, quint64 b, quint64 c, quint64 d);
    Block(std::string InitVector);

    void ShiftLeft(int count = 1);
    void ShiftRight(int count = 1);

    void set(quint64 a, quint64 b, quint64 c, quint64 d);

    quint64 & operator [] (int n) { return words[n%4]; }
    Block operator xor (Block r);
};

#endif // FOURWORDS_H

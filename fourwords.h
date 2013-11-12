#ifndef FOURWORDS_H
#define FOURWORDS_H

#include <QTypeInfo>

class FourWords
{
private:
    QList<quint64> words;

public:
    FourWords();
    FourWords(int a, int b, int c, int d);

    void ShiftLeft();
    void ShiftRight();

    void set(int a, int b, int c, int d);

    quint64 & operator [] (int n) { return words[n%4]; }
};

#endif // FOURWORDS_H

#ifndef BCS_H
#define BCS_H

#include <QTypeInfo>

#include <QDebug>

enum Mode { toLeft, toRight };

class BCS
{
public:
    static quint64 Shift(quint64 number, int w, quint64 shift, Mode mode);
};

#endif // BCS_H

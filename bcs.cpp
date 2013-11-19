#include "bcs.h"

quint64 BCS::Shift(quint64 number, int w, quint64 shift, Mode mode)
{
    if (shift == 0)
        return number;

    if (mode == toLeft)
        switch (w)
        {
            case 16 :
            {
                shift %= 16;
                quint16 num = (quint16)number;
                return (quint16)(num << shift | num >> 16-shift);
                break;
            }

            case 32 :
            {
                shift %= 32;
                quint32 num = (quint32)number;
                return (quint32)(num << shift | num >> 32-shift);
                break;
            }

            case 64 : default :
            {
                shift %= 64;
                return (number << shift | number >> 64-shift);
                break;
            }
        }
    else
        switch (w)
        {
            case 16 :
            {
                shift %= 16;
                quint16 num = (quint16)number;
                return (quint16)(num >> shift | num << 16-shift);
                break;
            }

            case 32 :
            {
                shift %= 32;
                quint32 num = (quint32)number;
                return (quint32)(num >> shift | num << 32-shift);
                break;
            }

            case 64 : default :
            {
                shift %= 64;
                return (number >> shift | number << 64-shift);
                break;
            }
        }
}

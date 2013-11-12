#include "bcs.h"

quint64 BCS::Shift(quint64 number, int w, quint64 shift)
{
    if (shift == 0)
        return number;

    quint64 sh = shift;

    if (shift < 0)
    {
        sh = -sh;
        switch (w)
        {
            case 16 :
            {
                sh %= 16;
                quint16 num = (quint16)number;
                return (quint64)(quint16)(num << sh | ((num >> (16 - sh)) & ((1 << sh) - 1)));
                break;
            }

            case 32 :
            {
                sh %= 32;
                quint32 num = (quint32)number;
                return (quint64)(quint32)(num << sh | ((num >> (32 - sh)) & ((1 << sh) - 1)));
                break;
            }

            case 64 : default :
            {
                sh %= 64;
                return (number << sh | ((number >> (64 - sh)) & (quint64)((1 << sh) - 1)));
                break;
            }
        }
    }
    else
    {
        switch (w)
        {
            case 16 :
            {
                sh %= 16;
                quint16 num = (quint16)number;
                return (quint64)(quint16)(num >> sh | ((num << (16 - sh)) & ((1 >> sh) - 1)));
                break;
            }

            case 32 :
            {
                sh %= 32;
                quint32 num = (quint32)number;
                return (quint64)(quint32)(num >> sh | ((num << (32 - sh)) & ((1 >> sh) - 1)));
                break;
            }

            case 64 : default :
            {
                sh %= 64;
                return (number >> sh | ((number << (64 - sh)) & (quint64)((1 >> sh) - 1)));
                break;
            }
        }
    }
}

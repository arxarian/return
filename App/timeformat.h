#ifndef TIMEFORMAT_H
#define TIMEFORMAT_H

#include <QtCore>

class TimeFormat
{
public:
    static QString GetMinsAndSeconds(qint64 nTime_ms)
    {
        qint64 nTime_s = nTime_ms / 1000;
        qint32 nMins = nTime_s / 60;
        qint32 nSeconds = nTime_s % 60;;
        return QString("%1:%2").arg(nMins).arg(nSeconds, 2, 10, QChar('0'));
    }
    static QString GetMins(qint64 nTime_ms)
    {
        return QString("%1").arg(nTime_ms / (1000 * 60));
    }
};

#endif // TIMEFORMAT_H

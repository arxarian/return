#ifndef USERTIMESETTINGS_H
#define USERTIMESETTINGS_H

#include <QtCore>

class UserTimeSettings
{
    static qint32 m_nWorkTime_s;
    static qint32 m_nRestTime_s;
    static qint32 m_nWarningTime_s;
    static quint32 m_nToleranceTime_s;

public:
    static qint32 WorkTime_s();
    static void SetWorkTime_s(const qint32 &WorkTime_s);

    static qint32 RestTime_s();
    static void SetRestTime_s(const qint32 &nRestTime_s);

    static qint32 WarningTime_s();
    static void SetWarningTime_s(const qint32 &nWarningTime_s);

    static quint32 ToleranceTime_s();
    static void SetToleranceTime_s(const quint32 &nToleranceTime_s);
};

#endif // USERTIMESETTINGS_H

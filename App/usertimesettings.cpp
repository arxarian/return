#include "usertimesettings.h"

qint32 UserTimeSettings::m_nWorkTime_s = 25 * 60;
qint32 UserTimeSettings::m_nRestTime_s = 5 * 60;
qint32 UserTimeSettings::m_nWarningTime_s = 2 * 60;
quint32 UserTimeSettings::m_nToleranceTime_s = 3;

qint32 UserTimeSettings::RestTime_s()
{
    return m_nRestTime_s;
}

void UserTimeSettings::SetRestTime_s(const qint32 &nRestTime_s)
{
    m_nRestTime_s = nRestTime_s;
}

qint32 UserTimeSettings::WarningTime_s()
{
    return m_nWarningTime_s;
}

void UserTimeSettings::SetWarningTime_s(const qint32 &nWarningTime_s)
{
    m_nWarningTime_s = nWarningTime_s;
}

quint32 UserTimeSettings::ToleranceTime_s()
{
    return m_nToleranceTime_s;
}

void UserTimeSettings::SetToleranceTime_s(const quint32 &nToleranceTime_s)
{
    m_nToleranceTime_s = nToleranceTime_s;
}

qint32 UserTimeSettings::WorkTime_s()
{
    return m_nWorkTime_s;
}

void UserTimeSettings::SetWorkTime_s(const qint32 &nWorkTime_s)
{
    m_nWorkTime_s = nWorkTime_s;
}

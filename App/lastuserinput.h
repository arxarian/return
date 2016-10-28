#ifndef LASTUSERINPUT_H
#define LASTUSERINPUT_H

#include <QtCore>

#include "windows.h"
#include "winbase.h"
#include <mmsystem.h>

#include "usertimesettings.h"

class LastUserInput
{
    const static qint32 m_nCooldown_ms = 1000;

    static qint64 m_nPseudoLastUserInput_ms;
    static qint64 m_nPseudoStartLastUserInput_ms;

    static qint64 m_nLastConfirmedUserInput_ms;

    static qint64 m_nStartUserActiveTime_ms;
    static qint64 m_nUserActiveTime_ms;
    static qint64 m_nUserIdleTime_ms;

    static qint64 m_nPassedTolerance_ms;

public:
    static bool UpdateLastUserInput();

    static qint64 UserActiveTime_ms();
    static qint64 UserIdleTime_ms();
    static qint32 PassedTolerance_ms();
};

#endif // LASTUSERINPUT_H

#ifndef LASTUSERINPUT_H
#define LASTUSERINPUT_H

#include <QtCore>

#include "windows.h"
#include "winbase.h"
#include <mmsystem.h>

#include "usertimesettings.h"

class LastUserInput
{
    static qint64 m_nPseudoLastUserInput_ms;
    static qint64 m_nPseudoStartLastUserInput_ms;

    static qint64 m_nStartUserActiveTime_ms;
    static qint64 m_nUserActiveTime_ms;
    static qint64 m_nUserIdleTime_ms;

public:
    static bool UpdateLastUserInput();

    static qint64 UserActiveTime_ms();
    static qint64 UserIdleTime_ms();
};

#endif // LASTUSERINPUT_H

#include "lastuserinput.h"

qint64 LastUserInput::m_nPseudoLastUserInput_ms = 0;
qint64 LastUserInput::m_nPseudoStartLastUserInput_ms = 0;

qint64 LastUserInput::m_nStartUserActiveTime_ms = -1;
qint64 LastUserInput::m_nUserActiveTime_ms = 0;
qint64 LastUserInput::m_nUserIdleTime_ms = 0;

qint64 LastUserInput::m_nPassedTolerance_ms = -1;

qint64 LastUserInput::UserActiveTime_ms()
{
    return m_nUserActiveTime_ms;
}

qint64 LastUserInput::UserIdleTime_ms()
{
    return m_nUserIdleTime_ms;
}

qint32 LastUserInput::PassedTolerance_ms()
{
    return m_nPassedTolerance_ms;
}

bool LastUserInput::UpdateLastUserInput()
{
    LASTINPUTINFO lastInputInfo;
    lastInputInfo.cbSize = sizeof(lastInputInfo);

    if(GetLastInputInfo(&lastInputInfo))
    {
        quint32 nTickCount = GetTickCount();

        if(m_nStartUserActiveTime_ms < 0)
        {
            m_nStartUserActiveTime_ms = nTickCount; // NOTE - accurate solution is "m_nStartUserActiveTime_ms = lastInputInfo.dwTime;" but this holds active time from counting up
        }

        m_nUserIdleTime_ms = nTickCount - lastInputInfo.dwTime;//m_nPseudoLastUserInput_ms;
        m_nUserActiveTime_ms = nTickCount - m_nStartUserActiveTime_ms;

        // if the user is idle for too long, reset counter
        if(60 * m_nUserIdleTime_ms / 1000 >= UserTimeSettings::RestTime_s())
        {
            m_nStartUserActiveTime_ms = -1;
        }

        return true;
    }
    return false;
}

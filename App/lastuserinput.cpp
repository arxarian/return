#include "lastuserinput.h"

qint64 LastUserInput::m_nPseudoLastUserInput_ms = 0;
qint64 LastUserInput::m_nPseudoStartLastUserInput_ms = 0;

qint64 LastUserInput::m_nStartUserActiveTime_ms = -1;
qint64 LastUserInput::m_nUserActiveTime_ms = 0;
qint64 LastUserInput::m_nUserIdleTime_ms = 0;

qint64 LastUserInput::UserActiveTime_ms()
{
    return m_nUserActiveTime_ms;
}

qint64 LastUserInput::UserIdleTime_ms()
{
    return m_nUserIdleTime_ms;
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
            m_nStartUserActiveTime_ms = nTickCount;
        }

        if(UserTimeSettings::ToleranceTime_s() > 0 && m_nUserIdleTime_ms / 1000 > UserTimeSettings::ToleranceTime_s())
        {
            if((nTickCount - lastInputInfo.dwTime) / 1000 < UserTimeSettings::ToleranceTime_s() && m_nPseudoStartLastUserInput_ms == -1)
            {
                m_nPseudoStartLastUserInput_ms = lastInputInfo.dwTime;
            }
            else if((nTickCount - lastInputInfo.dwTime) / 1000 < UserTimeSettings::ToleranceTime_s() && (nTickCount - m_nPseudoStartLastUserInput_ms) / 1000 > UserTimeSettings::ToleranceTime_s())
            {
                m_nPseudoLastUserInput_ms = lastInputInfo.dwTime;
            }
            else if((nTickCount - lastInputInfo.dwTime) / 1000 > UserTimeSettings::ToleranceTime_s())
            {
                m_nPseudoStartLastUserInput_ms = -1;
            }
        }
        else
        {
            m_nPseudoLastUserInput_ms = lastInputInfo.dwTime;
        }

        m_nUserIdleTime_ms = nTickCount - m_nPseudoLastUserInput_ms;
        m_nUserActiveTime_ms = nTickCount - m_nStartUserActiveTime_ms;

        // if the user is idle for too long, reset counter
        if(m_nUserIdleTime_ms / 1000 > UserTimeSettings::RestTime_s())
        {
            m_nStartUserActiveTime_ms = -1;
        }
        return true;
    }
    return false;
}

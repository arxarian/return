#include "userinputwatcher.h"

qint64 UserInputWatcher::UserActiveTime_ms()
{
    return m_nUserActiveTime_ms;
}

qint64 UserInputWatcher::UserIdleTime_ms()
{
    return m_nUserIdleTime_ms;
}

qint32 UserInputWatcher::PassedTolerance_ms()
{
    return m_nPassedTolerance_ms;
}

UserInputWatcher::UserInputWatcher(SystemInterface* pSystemInput)
{
    m_pSystemInterface.reset(pSystemInput);
}

UserInputWatcher::~UserInputWatcher()
{
    m_pSystemInterface.clear();
}

bool UserInputWatcher::UpdateLastUserInput()
{
    qint64 nLastInputTime_ms = 0;

    if(m_pSystemInterface->LastUserInputTime_ms(nLastInputTime_ms))
    {
        quint32 nTickCount = m_pSystemInterface->SystemTime_ms();

        if(m_nStartUserActiveTime_ms < 0)
        {
            m_nStartUserActiveTime_ms = nTickCount; // NOTE - accurate solution is "m_nStartUserActiveTime_ms = lastInputInfo.dwTime;" but this holds active time from counting up
        }

        if(m_nPseudoLastUserInput_ms < 0)
        {
            m_nPseudoLastUserInput_ms = nLastInputTime_ms;
            // qDebug() << "m_nPseudoLastUserInput_ms init";
        }

        if(nTickCount - nLastInputTime_ms < m_nCooldown_ms)
        {
            if(m_nLastConfirmedUserInput_ms != nLastInputTime_ms)
            {
                m_nLastConfirmedUserInput_ms = nLastInputTime_ms;
                if(m_nPseudoStartLastUserInput_ms < 0)
                {
                    m_nPseudoStartLastUserInput_ms = nLastInputTime_ms;
                    // qDebug() << "m_nPseudoStartLastUserInput_ms init";
                }
                m_nPassedTolerance_ms = nTickCount - m_nPseudoStartLastUserInput_ms;
                // qDebug() << "passed tolerance " << m_nPassedTolerance_ms;
            }
        }
        else
        {
            m_nPseudoStartLastUserInput_ms = -1;
            m_nPassedTolerance_ms = 0;              // NOTE - update passed tolerance in this iteration (it's redundant)
            // qDebug() << "reset";
        }

        if(m_nPassedTolerance_ms > UserTimeSettings::ToleranceTime_s() * 1000)
        {
            m_nPseudoLastUserInput_ms = nLastInputTime_ms;
            // qDebug() << "tolerance exceeded";
        }
        m_nUserIdleTime_ms = nTickCount - m_nPseudoLastUserInput_ms;
        m_nUserActiveTime_ms = nTickCount - m_nStartUserActiveTime_ms;

        // if the user is idle for too long, reset counter
        if(m_nUserIdleTime_ms >= UserTimeSettings::RestTime_s() * 1000)
        {
            m_nStartUserActiveTime_ms = -1;
            emit NewWorkPeriod();
            // qDebug() << "reseting idle time";
        }

        return true;
    }
    return false;
}

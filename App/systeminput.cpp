#include "systeminput.h"

bool SystemInput::LastUserInputTime_ms(qint64 &nLastUserInput_ms)
{
    m_oLastInputInfo.cbSize = sizeof(m_oLastInputInfo);

    bool bReturn = GetLastInputInfo(&m_oLastInputInfo);

    nLastUserInput_ms = m_oLastInputInfo.dwTime;

    return bReturn;
}

qint64 SystemInput::SystemTime_ms()
{
    return GetTickCount();
}

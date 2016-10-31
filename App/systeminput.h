#ifndef SYSTEMINPUT_H
#define SYSTEMINPUT_H

#include <QtCore>

#include "windows.h"
#include "winbase.h"
#include <mmsystem.h>

class SystemInterface
{
public:
    virtual ~SystemInterface() {}
    virtual bool LastUserInputTime_ms(qint64 &nLastUserInput_ms) = 0;
    virtual qint64 SystemTime_ms() = 0;
};

class SystemInput : public SystemInterface
{
    LASTINPUTINFO m_oLastInputInfo;

    // SystemInterface interface
public:
    ~SystemInput() {}
    bool LastUserInputTime_ms(qint64 &nLastUserInput_ms) override;
    qint64 SystemTime_ms() override;
};

#endif // SYSTEMINPUT_H

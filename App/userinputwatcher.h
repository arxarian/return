#ifndef LASTUSERINPUT_H
#define LASTUSERINPUT_H

#include <QtCore>
#include <QObject>
#include <QSharedPointer>

#include "usertimesettings.h"
#include "singleton.h"
#include "systeminput.h"

class UserInputWatcher : public QObject, public Singleton<UserInputWatcher>
{
    Q_OBJECT

    const quint32 m_nCooldown_ms = 1000;

    bool m_bBreakTaken = false;

    qint64 m_nPseudoLastUserInput_ms = -1;
    qint64 m_nPseudoStartLastUserInput_ms = -1;

    qint64 m_nLastConfirmedUserInput_ms = 0;

    qint64 m_nStartUserActiveTime_ms = -1;
    qint64 m_nUserActiveTime_ms =0;
    qint64 m_nUserIdleTime_ms = 0;
    qint32 m_nExtraWorkTime_ms = 0;

    qint64 m_nPassedTolerance_ms = -1;

    QSharedPointer<SystemInterface> m_pSystemInterface;

public:
    UserInputWatcher(SystemInterface *pSystemInput);
    ~UserInputWatcher();

    bool UpdateLastUserInput();

    qint64 UserActiveTime_ms();
    qint64 UserIdleTime_ms();
    qint32 PassedTolerance_ms();

signals:
    void NewWorkPeriod(void);
};

#endif // LASTUSERINPUT_H

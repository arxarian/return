#include "widget.h"

void Widget::CreateTrayIcon() // TODO - mnoho věcí tato funkce dělá
{
    m_pQuitAction = new QAction(tr("&Quit"), this);
    connect(m_pQuitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(m_pQuitAction);

    m_pTrayIcon = new QSystemTrayIcon(this);
    m_pTrayIcon->setContextMenu(trayIconMenu);
}

void Widget::SetTrayIcon(QString strIcon)
{
    if(strIcon != m_strSetTrayIcon)
    {
        QIcon icon(strIcon);
        m_pTrayIcon->setIcon(icon);
//    setWindowIcon(icon);  // set app icon
        m_pTrayIcon->setVisible(true);

        m_strSetTrayIcon = strIcon;
    }
}

void Widget::LoadValues()
{
    m_pAppSettings = new QSettings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    qDebug() << QCoreApplication::organizationName() << QCoreApplication::applicationName();

    m_nWorkTime_s = m_pAppSettings->value("work_time", m_nWorkTime_s).toInt();
    m_nRestTime_s = m_pAppSettings->value("rest_time", m_nRestTime_s).toInt();
    m_nToleranceTime_s = m_pAppSettings->value("tolerance_time", m_nToleranceTime_s).toInt();
}

void Widget::CreateLayout()
{
    QVBoxLayout* pTimeLayout = new QVBoxLayout;

    // work spin box
    QHBoxLayout* pWorkLayout = new QHBoxLayout;
    QLabel* pWorkLabel = new QLabel(tr("Work time [mins]"));
    QSpinBox* pSpinWorkTime_s = new QSpinBox(this); // TODO - má tu být this? Nemá tu být některý child?
    pSpinWorkTime_s->setValue(m_nWorkTime_s / 60);
    pSpinWorkTime_s->setMaximum(999);
    connect(pSpinWorkTime_s, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](const int &nNewValue) {
        m_nWorkTime_s = nNewValue * 60;
        m_pAppSettings->setValue("work_time", m_nWorkTime_s);
    });
    pWorkLayout->addWidget(pWorkLabel);
    pWorkLayout->addWidget(pSpinWorkTime_s);

    // rest spin box
    QHBoxLayout* pRestLayout = new QHBoxLayout;
    QLabel* pRestLabel = new QLabel(tr("Rest time [mins]"));
    QSpinBox* pSpinRestTime_s = new QSpinBox(this);
    pSpinRestTime_s->setValue(m_nRestTime_s / 60);
    pSpinRestTime_s->setMaximum(999);
    connect(pSpinRestTime_s, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](const int &nNewValue) {
       m_nRestTime_s = nNewValue * 60;
       m_pAppSettings->setValue("rest_time", m_nRestTime_s);
    });
    pRestLayout->addWidget(pRestLabel);
    pRestLayout->addWidget(pSpinRestTime_s);

    // tolerance spin box
    QHBoxLayout* pToleranceLayout = new QHBoxLayout;
    QLabel* pToleranceLabel = new QLabel(tr("Tolerance time [s]"));
    QSpinBox* pSpinToleranceTime_s = new QSpinBox(this);
    pSpinToleranceTime_s->setValue(m_nToleranceTime_s);
    pSpinToleranceTime_s->setMaximum(999);
    connect(pSpinToleranceTime_s, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](const int &nNewValue) {
       m_nToleranceTime_s = nNewValue;
       m_pAppSettings->setValue("tolerance_time", m_nToleranceTime_s);
    });
    pToleranceLayout->addWidget(pToleranceLabel);
    pToleranceLayout->addWidget(pSpinToleranceTime_s);

    // add all to vertical layout
    pTimeLayout->addLayout(pWorkLayout);
    pTimeLayout->addLayout(pRestLayout);
    pTimeLayout->addLayout(pToleranceLayout);

    // add label with info
    m_pLabel = new QLabel;

    QVBoxLayout* pMainLayout = new QVBoxLayout;
    pMainLayout->addLayout(pTimeLayout);
    pMainLayout->addWidget(m_pLabel);
    this->setLayout(pMainLayout);
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    CreateTrayIcon();
    SetTrayIcon(":/go_icon.png");

    LoadValues();
    CreateLayout();

    if(QSystemTrayIcon::isSystemTrayAvailable())
    {
        qDebug() << "tray is avaible";
    }

    connect(m_pTrayIcon, &QSystemTrayIcon::activated, [=](QSystemTrayIcon::ActivationReason eReason) {
        qDebug() << eReason;
        switch (eReason) {
        case QSystemTrayIcon::DoubleClick:
        case QSystemTrayIcon::Trigger:
            this->setWindowState(this->windowState() & ~Qt::WindowMinimized);
            this->show();
            this->activateWindow();
            break;
        default:
            break;
        }
    });

    connect(&m_oBeepTimer, &QTimer::timeout, [=]() {
        if(m_nUserActiveTime_ms / 1000 < m_nWorkTime_s &&  m_nUserActiveTime_ms / 1000 > (m_nWorkTime_s - m_nWarningTime_s))
        {
            SetTrayIcon(":/ready_icon.png");
        }
        if(m_nUserActiveTime_ms / 1000 > m_nWorkTime_s)
        {
            if(m_nUserIdleTime_ms < 500)
            {
                QApplication::beep();
            }
            SetTrayIcon(":/stop_icon.png");
        }
    });

    connect(&m_oTimer, &QTimer::timeout, [=]() {

        LASTINPUTINFO lastInputInfo;
        lastInputInfo.cbSize = sizeof(lastInputInfo);
        if(GetLastInputInfo(&lastInputInfo))
        {
            quint32 nTickCount = GetTickCount();

            if(m_nStartUserActiveTime_ms < 0)
            {
                m_nStartUserActiveTime_ms = nTickCount;
                SetTrayIcon(":/go_icon.png");
            }

            if(m_nUserActiveTime_ms / 1000 > m_nWorkTime_s)
            {
                if(m_nToleranceTime_s > 0 && m_nUserIdleTime_ms / 1000 > m_nToleranceTime_s)
                {
                    if((nTickCount - lastInputInfo.dwTime) / 1000 < m_nToleranceTime_s && m_nPseudoStartLastUserInput_ms == -1)
                    {
                        m_nPseudoStartLastUserInput_ms = lastInputInfo.dwTime;
                    }
                    else if((nTickCount - lastInputInfo.dwTime) / 1000 < m_nToleranceTime_s && (nTickCount - m_nPseudoStartLastUserInput_ms) / 1000 > m_nToleranceTime_s)
                    {
                        m_nPseudoLastUserInput_ms = lastInputInfo.dwTime;
                    }
                    else if((nTickCount - lastInputInfo.dwTime) / 1000 > m_nToleranceTime_s)
                    {
                        m_nPseudoStartLastUserInput_ms = -1;
                    }
                }
                else
                {
                    m_nPseudoLastUserInput_ms = lastInputInfo.dwTime;
                }
            }
            else
            {
                m_nPseudoLastUserInput_ms = lastInputInfo.dwTime;
            }

            m_nUserIdleTime_ms = nTickCount - m_nPseudoLastUserInput_ms;
            m_nUserActiveTime_ms = nTickCount - m_nStartUserActiveTime_ms;

            // if the user is idle for too long, reset counter
            if(m_nUserIdleTime_ms / 1000 > m_nRestTime_s)
            {
//                PlaySound(TEXT("SystemStart"), NULL, SND_ALIAS);
                m_nStartUserActiveTime_ms = -1;
            }


            m_pLabel->setText(QString("The last user input time\t%1\nCurrent time\t\t%2\nUser idle time\t\t%3\nUser active time\t\t%4")
                              .arg(lastInputInfo.dwTime).arg(nTickCount).arg(QDateTime::fromTime_t(m_nUserIdleTime_ms / 1000).toUTC().toString("mm:ss")).arg(QDateTime::fromTime_t(m_nUserActiveTime_ms / 1000).toUTC().toString("mm:ss")));

            m_pTrayIcon->setToolTip(QString(tr("Work time is %1 mins"))
                                    .arg(QDateTime::fromTime_t(m_nUserActiveTime_ms / 1000).toUTC().toString("m")));
//                                    .arg(QDateTime::fromTime_t((m_nWarningTime_s - m_nUserActiveTime_ms) < 0 ? 0 : (m_nWarningTime_s - m_nUserActiveTime_ms) / 1000).toUTC().toString("mm:ss")));
        }
        else
        {
             m_pLabel->setText("last-input-info error");
        }
    });

    m_oTimer.start(100);
    m_oBeepTimer.start(1100);
}

Widget::~Widget()
{

}

void Widget::closeEvent(QCloseEvent *event)
{
    if(m_pTrayIcon->isVisible())
    {
        hide();
        event->ignore();
    }
}

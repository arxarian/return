#include "widget.h"

void Widget::CreateTrayIcon()
{
    QMenu* pTrayIconMenu = new QMenu(this);
    pTrayIconMenu->addAction(m_pOpenAction);
    pTrayIconMenu->addSeparator();
    pTrayIconMenu->addAction(m_pPostponeAction);
    pTrayIconMenu->addSeparator();
    pTrayIconMenu->addAction(m_pQuitAction);

    if(m_pTrayIcon)
    {
        m_pTrayIcon->setContextMenu(pTrayIconMenu);
    }
}

void Widget::SetTrayIcon(QString strIcon)
{
    if(strIcon != m_strSetTrayIcon && m_pTrayIcon)
    {
        QIcon icon(strIcon);
        m_pTrayIcon->setIcon(icon);
        m_pTrayIcon->setVisible(true);

        m_strSetTrayIcon = strIcon;
    }
}

void Widget::LoadValues()
{
    m_pAppSettings = new QSettings(QCoreApplication::organizationName(), QCoreApplication::applicationName(), this);
    qDebug() << QCoreApplication::organizationName() << QCoreApplication::applicationName();

    UserTimeSettings::SetWorkTime_s(m_pAppSettings->value("work_time", UserTimeSettings::WorkTime_s()).toInt());
    UserTimeSettings::SetRestTime_s(m_pAppSettings->value("rest_time", UserTimeSettings::RestTime_s()).toInt());
    UserTimeSettings::SetToleranceTime_s(m_pAppSettings->value("tolerance_time", UserTimeSettings::ToleranceTime_s()).toInt());
}

void Widget::CreateLayout()
{
    QVBoxLayout* pTimeLayout = new QVBoxLayout;

    // work spin box
    QHBoxLayout* pWorkLayout = new QHBoxLayout;
    QLabel* pWorkLabel = new QLabel(tr("Work time [mins]"));
    QSpinBox* pSpinWorkTime_s = new QSpinBox(this); // TODO - má tu být this? Nemá tu být některý child?
    pSpinWorkTime_s->setValue(UserTimeSettings::WorkTime_s() / 60);
    pSpinWorkTime_s->setMaximum(999);
    connect(pSpinWorkTime_s, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](const int &nNewValue) {
        UserTimeSettings::SetWorkTime_s(nNewValue * 60);
        m_pAppSettings->setValue("work_time", UserTimeSettings::WorkTime_s());
    });
    pWorkLayout->addWidget(pWorkLabel);
    pWorkLayout->addWidget(pSpinWorkTime_s);

    // rest spin box
    QHBoxLayout* pRestLayout = new QHBoxLayout;
    QLabel* pRestLabel = new QLabel(tr("Rest time [mins]"));
    QSpinBox* pSpinRestTime_s = new QSpinBox(this);
    pSpinRestTime_s->setValue(UserTimeSettings::RestTime_s() / 60);
    pSpinRestTime_s->setMaximum(999);
    connect(pSpinRestTime_s, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](const int &nNewValue) {
       UserTimeSettings::SetRestTime_s(nNewValue * 60);
       m_pAppSettings->setValue("rest_time", UserTimeSettings::RestTime_s());
    });
    pRestLayout->addWidget(pRestLabel);
    pRestLayout->addWidget(pSpinRestTime_s);

    // tolerance spin box
    QHBoxLayout* pToleranceLayout = new QHBoxLayout;
    QLabel* pToleranceLabel = new QLabel(tr("Tolerance time [s]"));
    QSpinBox* pSpinToleranceTime_s = new QSpinBox(this);
    pSpinToleranceTime_s->setValue(UserTimeSettings::ToleranceTime_s());
    pSpinToleranceTime_s->setMaximum(999);
    connect(pSpinToleranceTime_s, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](const int &nNewValue) {
       UserTimeSettings::SetToleranceTime_s(nNewValue);
       m_pAppSettings->setValue("tolerance_time", UserTimeSettings::ToleranceTime_s());

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

    m_pPassedToleranceBar = new QProgressBar(this);
    m_pPassedToleranceBar->setMaximum(0);
    m_pPassedToleranceBar->setMaximum(UserTimeSettings::ToleranceTime_s() * 1000);
    m_pPassedToleranceBar->setTextVisible(false);

    pMainLayout->addWidget(m_pPassedToleranceBar);
    pMainLayout->addWidget(m_pLabel);
    this->setLayout(pMainLayout);
}

void Widget::CreateActions()
{
    m_pOpenAction = new QAction(tr("&Open"), this);
    connect(m_pOpenAction, &QAction::triggered, this, &Widget::OpenWindow);

    m_pPostponeAction = new QAction(tr("&Add 5 mins"), this);
    connect(m_pPostponeAction, &QAction::triggered, this, &Widget::PostponeTheBreak);

    m_pQuitAction = new QAction(tr("Really &quit"), this);
    connect(m_pQuitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void Widget::OpenWindow()
{
    this->setWindowState(this->windowState() & ~Qt::WindowMinimized);
    this->show();
    this->activateWindow();
}

void Widget::PostponeTheBreak()
{
    if(!m_bBreakTaken)
    {
        m_bBreakTaken = true;
        m_nExtraWorkTime_ms = UserTimeSettings::ExtraWorkTime_s() * 1000;
    }
}

void Widget::SetIconByTime()
{
    int nWorkTime_ms = UserTimeSettings::WorkTime_s() * 1000 + m_nExtraWorkTime_ms;
    if(m_pLastUserInput->UserActiveTime_ms() > nWorkTime_ms)
    {
        SetTrayIcon(":/stop_icon.png");
    }
    else if(m_pLastUserInput->UserActiveTime_ms() < nWorkTime_ms &&  m_pLastUserInput->UserActiveTime_ms() > (nWorkTime_ms - UserTimeSettings::WarningTime_s()) * 1000)
    {
        SetTrayIcon(":/ready_icon.png");
    }
    else if(m_pLastUserInput->UserIdleTime_ms() > UserTimeSettings::RestTime_s())
    {
        SetTrayIcon(":/go_icon.png");
    }
}

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    m_pLastUserInput = new UserInputWatcher(new SystemInput());

    m_pTrayIcon = new QSystemTrayIcon(this);

    CreateActions();
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
            OpenWindow();
            break;
        default:
            break;
        }
    });

    connect(&m_oBeepTimer, &QTimer::timeout, [=]() {
        int nWorkTime_ms = UserTimeSettings::WorkTime_s() * 1000 + m_nExtraWorkTime_ms;
        if(m_pLastUserInput->UserActiveTime_ms() > nWorkTime_ms && m_pLastUserInput->PassedTolerance_ms() > 0)
        {
            QApplication::beep();
        }
    });

    connect(&m_oTimer, &QTimer::timeout, [=]() {

        SetIconByTime();
        m_pLastUserInput->UpdateLastUserInput();

        m_pPassedToleranceBar->setValue(m_pLastUserInput->PassedTolerance_ms() > m_pPassedToleranceBar->maximum() ? m_pPassedToleranceBar->maximum() : m_pLastUserInput->PassedTolerance_ms());

        m_pLabel->setText(QString("User idle time\t\t%1\nUser active time\t\t%2")
                          .arg(QDateTime::fromTime_t(m_pLastUserInput->UserIdleTime_ms() / 1000).toUTC().toString("mm:ss")).arg(QDateTime::fromTime_t(m_pLastUserInput->UserActiveTime_ms() / 1000).toUTC().toString("mm:ss")));

        m_pTrayIcon->setToolTip(QString(tr("Work time is %1 mins")).arg(m_pLastUserInput->UserActiveTime_ms() / (1000 * 60)));

    });

    connect(m_pLastUserInput, &UserInputWatcher::NewWorkPeriod, [=]() {
        m_nExtraWorkTime_ms = 0;
        m_bBreakTaken = false;
    });

    m_oTimer.start(100);
    m_oBeepTimer.start(1100);
}

void Widget::closeEvent(QCloseEvent *event)
{
    if(m_pTrayIcon->isVisible())
    {
        hide();
        event->ignore();
    }
}

#include "widget.h"

void MainWindow::CreateTrayIcon()
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

void MainWindow::SetTrayIcon(QString strIcon)
{
    if(strIcon != m_strSetTrayIcon && m_pTrayIcon)
    {
        QIcon icon(strIcon);
        m_pTrayIcon->setIcon(icon);
        m_pTrayIcon->setVisible(true);

        m_strSetTrayIcon = strIcon;
    }
}

void MainWindow::LoadSettings()
{
    qint32 nWorkTime_s = m_pSettingStrorage->RestoreWorkTime_s();
    UserTimeSettings::SetWorkTime_s(nWorkTime_s < 0 ? UserTimeSettings::WorkTime_s() : nWorkTime_s);

    qint32 nRestTime_s = m_pSettingStrorage->RestoreRestTime_s();
    UserTimeSettings::SetRestTime_s(nRestTime_s < 0 ? UserTimeSettings::RestTime_s() : nRestTime_s);

    qint32 nToleranceTime_s = m_pSettingStrorage->RestoreToleranceTime_s();
    UserTimeSettings::SetToleranceTime_s(nToleranceTime_s < 0 ? UserTimeSettings::ToleranceTime_s() : nToleranceTime_s);

    m_pOnTopAction->setChecked(m_pSettingStrorage->RestoreAlwaysOnTop());
    SetOnTop(m_pOnTopAction->isChecked());

    m_pOnStartUpAction->setChecked(m_pSettingStrorage->RestoreRunOnStartUp());
}

void MainWindow::CreateLayout()
{
    QVBoxLayout* pTimeLayout = new QVBoxLayout;

    // work spin box
    QHBoxLayout* pWorkLayout = new QHBoxLayout;
    QLabel* pWorkLabel = new QLabel(tr("Work time [mins]"));
    QSpinBox* pSpinWorkTime_s = new QSpinBox(this); // TODO - má tu být this? Nemá tu být některý child?
    pSpinWorkTime_s->setValue(UserTimeSettings::WorkTime_s() / 60);
    pSpinWorkTime_s->setMaximum(999);
    connect(pSpinWorkTime_s, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [&](const int &nNewValue) {
        UserTimeSettings::SetWorkTime_s(nNewValue * 60);
        m_pSettingStrorage->StoreWorkTime_s(UserTimeSettings::WorkTime_s());
    });
    pWorkLayout->addWidget(pWorkLabel);
    pWorkLayout->addWidget(pSpinWorkTime_s);

    // rest spin box
    QHBoxLayout* pRestLayout = new QHBoxLayout;
    QLabel* pRestLabel = new QLabel(tr("Rest time [mins]"));
    QSpinBox* pSpinRestTime_s = new QSpinBox(this);
    pSpinRestTime_s->setValue(UserTimeSettings::RestTime_s() / 60);
    pSpinRestTime_s->setMaximum(999);
    connect(pSpinRestTime_s, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [&](const int &nNewValue) {
       UserTimeSettings::SetRestTime_s(nNewValue * 60);
       m_pSettingStrorage->StoreRestTime_s(UserTimeSettings::RestTime_s());
    });
    pRestLayout->addWidget(pRestLabel);
    pRestLayout->addWidget(pSpinRestTime_s);

    // tolerance spin box
    QHBoxLayout* pToleranceLayout = new QHBoxLayout;
    QLabel* pToleranceLabel = new QLabel(tr("Tolerance time [s]"));
    QSpinBox* pSpinToleranceTime_s = new QSpinBox(this);
    pSpinToleranceTime_s->setValue(UserTimeSettings::ToleranceTime_s());
    pSpinToleranceTime_s->setMaximum(999);
    connect(pSpinToleranceTime_s, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [&](const int &nNewValue) {
       UserTimeSettings::SetToleranceTime_s(nNewValue);
       m_pSettingStrorage->StoreToleranceTime_s(UserTimeSettings::ToleranceTime_s());
    });
    pToleranceLayout->addWidget(pToleranceLabel);
    pToleranceLayout->addWidget(pSpinToleranceTime_s);

    // add all to vertical layout
    pTimeLayout->addLayout(pWorkLayout);
    pTimeLayout->addLayout(pRestLayout);
    pTimeLayout->addLayout(pToleranceLayout);

    QVBoxLayout* pMainLayout = new QVBoxLayout;
    pMainLayout->addLayout(pTimeLayout);

    m_pPassedToleranceBar = new QProgressBar(this);
    m_pPassedToleranceBar->setMaximum(0);
    m_pPassedToleranceBar->setMaximum(UserTimeSettings::ToleranceTime_s() * 1000);
    m_pPassedToleranceBar->setTextVisible(false);

    pMainLayout->addWidget(m_pPassedToleranceBar);

    // add label with info
    QHBoxLayout* pInfoLayout = new QHBoxLayout;
    QLabel* pLabel = new QLabel;
    pLabel->setText(tr("User idle time\nUser active time"));
    m_pTimeInfoLabel = new QLabel;
    m_pTimeInfoLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    pInfoLayout->addWidget(pLabel);
    pInfoLayout->addWidget(m_pTimeInfoLabel);

    pMainLayout->addLayout(pInfoLayout);

    QWidget* pWidget = new QWidget(this);
    pWidget->setLayout(pMainLayout);
    this->setCentralWidget(pWidget);
}

void MainWindow::CreateActions()
{
    m_pOpenAction = new QAction(tr("&Open"), this);
    connect(m_pOpenAction, &QAction::triggered, this, &MainWindow::OpenWindow);

    m_pPostponeAction = new QAction(tr("&Add 5 mins"), this);
    m_pPostponeAction->setCheckable(true);
    connect(m_pPostponeAction, &QAction::triggered, this, &MainWindow::PostponeTheBreak);

    m_pAboutAction = new QAction(tr("A&bout..."), this);
    connect(m_pAboutAction, &QAction::triggered, qApp, &QApplication::aboutQt); // NOTE - change to about App

    m_pQuitAction = new QAction(tr("Really &quit"), this);
    connect(m_pQuitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    m_pOnTopAction = new QAction(tr("Always on &top"), this);
    m_pOnTopAction->setCheckable(true);
    connect(m_pOnTopAction, &QAction::triggered, [&](bool bOnTop) {
        m_pSettingStrorage->StoreAlwaysOnTop(bOnTop);
        SetOnTop(bOnTop);
    });

    m_pOnStartUpAction = new QAction(tr("Run on &startup"), this);
    m_pOnStartUpAction->setCheckable(true);
    connect(m_pOnStartUpAction, &QAction::triggered, [&](bool bRunOnStartUp) {
        m_pSettingStrorage->StoreRunOnStartUp(bRunOnStartUp);
        SetOnStartUp(bRunOnStartUp);
    });
}

void MainWindow::CreateMenu()
{
    m_pAppMenu = menuBar()->addMenu(tr("&App"));
    m_pAppMenu->addAction(m_pPostponeAction);
    m_pAppMenu->addSeparator();
    m_pAppMenu->addAction(m_pAboutAction);
    m_pAppMenu->addSeparator();
    m_pAppMenu->addAction(m_pQuitAction);

    m_pOptionsMenu = menuBar()->addMenu(tr("&Options"));
    m_pOptionsMenu->addAction(m_pOnTopAction);
    m_pOptionsMenu->addAction(m_pOnStartUpAction);
}

void MainWindow::OpenWindow()
{
    this->setWindowState(this->windowState() & ~Qt::WindowMinimized);
    this->show();
    this->activateWindow();
}

void MainWindow::PostponeTheBreak()
{
    m_pPostponeAction->setEnabled(false);
    m_nExtraWorkTime_ms = UserTimeSettings::ExtraWorkTime_s() * 1000;
}

void MainWindow::SetOnTop(bool bOnTop)
{
    if(bOnTop)
    {
        this->setWindowFlags(Qt::WindowStaysOnTopHint);
    }
    else
    {
        this->setWindowFlags(this->windowFlags() & (~Qt::WindowStaysOnTopHint));
    }
    this->show();
    this->activateWindow();
}

void MainWindow::SetOnStartUp(bool bRunOnStartUp)
{
    QSettings oSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    if (bRunOnStartUp)
    {
        const QString strNativeBinPath = QDir::toNativeSeparators(qApp->applicationFilePath());
        oSettings.setValue(QCoreApplication::applicationName(), strNativeBinPath);
    }
    else
    {
        oSettings.remove(QCoreApplication::applicationName());
    }
}

void MainWindow::SetIconByTime()
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

MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent)
{
    this->restoreGeometry(m_pSettingStrorage->RestoreGeometry());

    m_pLastUserInput = new UserInputWatcher(new SystemInput());

    m_pTrayIcon = new QSystemTrayIcon(this);

    CreateActions();
    CreateTrayIcon();
    SetTrayIcon(":/go_icon.png");

    LoadSettings();
    CreateLayout();
    CreateMenu();

    if(QSystemTrayIcon::isSystemTrayAvailable())
    {
        qDebug() << "tray is avaible";
    }

    connect(m_pTrayIcon, &QSystemTrayIcon::activated, [&](QSystemTrayIcon::ActivationReason eReason) {
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

    connect(&m_oBeepTimer, &QTimer::timeout, [&]() {
        int nWorkTime_ms = UserTimeSettings::WorkTime_s() * 1000 + m_nExtraWorkTime_ms;
        if(m_pLastUserInput->UserActiveTime_ms() > nWorkTime_ms && m_pLastUserInput->PassedTolerance_ms() > 0)
        {
            QApplication::beep();
        }
    });

    connect(&m_oTimer, &QTimer::timeout, [&]() {

        SetIconByTime();
        m_pLastUserInput->UpdateLastUserInput();

        m_pPassedToleranceBar->setValue(m_pLastUserInput->PassedTolerance_ms() > m_pPassedToleranceBar->maximum() ? m_pPassedToleranceBar->maximum() : m_pLastUserInput->PassedTolerance_ms());

        m_pTimeInfoLabel->setText(QString("%1\n%2")
                          .arg(TimeFormat::GetMinsAndSeconds(m_pLastUserInput->UserIdleTime_ms()))
                          .arg(TimeFormat::GetMinsAndSeconds(m_pLastUserInput->UserActiveTime_ms())));

        m_pTrayIcon->setToolTip(QString(tr("Work time is %1 mins")).arg(TimeFormat::GetMins(m_pLastUserInput->UserActiveTime_ms())));

    });

    connect(m_pLastUserInput, &UserInputWatcher::NewWorkPeriod, [&]() {
        m_pPostponeAction->setEnabled(true);
        m_pPostponeAction->setChecked(false);
        m_nExtraWorkTime_ms = 0;
    });

    m_oTimer.start(100);
    m_oBeepTimer.start(1100);
}

MainWindow::~MainWindow()
{
    m_pSettingStrorage->StoreGeometry(saveGeometry());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_pTrayIcon->isVisible())
    {
        hide();
        event->ignore();
    }
}

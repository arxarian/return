#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QtWidgets>
#include <QMenu>
#include <QDebug>
#include <QDir>

#include "userinputwatcher.h"
#include "usertimesettings.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    UserInputWatcher* m_pLastUserInput;

    QLabel* m_pLabel = 0;

    QMenu* m_pAppMenu = 0;
    QMenu* m_pOptionsMenu = 0;

    QAction* m_pQuitAction = 0;
    QAction* m_pOpenAction = 0;
    QAction* m_pPostponeAction = 0;
    QAction* m_pAboutAction = 0;
    QAction* m_pOnTopAction = 0;
    QAction* m_pOnStartUpAction = 0;

    QSystemTrayIcon* m_pTrayIcon = 0;

    QTimer m_oTimer;
    QTimer m_oBeepTimer;

    QString m_strSetTrayIcon;

    QProgressBar* m_pPassedToleranceBar = 0;

    QSettings* m_pAppSettings = 0;

    bool m_bBreakTaken = false;
    qint32 m_nExtraWorkTime_ms = 0;


    void CreateTrayIcon();
    void SetTrayIcon(QString strIcon);
    void LoadSettings();
    void CreateLayout();
    void CreateActions();
    void CreateMenu();

    void SetIconByTime();

public:
    MainWindow(QMainWindow *parent = 0);
    ~MainWindow() {}

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void OpenWindow();
    void PostponeTheBreak();
    void SetOnTop(bool bOnTop);
    void SetOnStartUp(bool bRunOnStartUp);
};

#endif // WIDGET_H

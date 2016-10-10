#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QtWidgets>
#include <QMenu>
#include <QDebug>

#include "windows.h"
#include "winbase.h"
#include <mmsystem.h>

class Widget : public QWidget
{
    Q_OBJECT

    QLabel* m_pLabel;

    QSystemTrayIcon* m_pTrayIcon;
    QMenu *trayIconMenu;

    QAction *m_pQuitAction;

    QTimer m_oTimer;
    QTimer m_oBeepTimer;

    qint64 m_nPseudoLastUserInput_ms = 0;
    qint64 m_nPseudoStartLastUserInput_ms = 0;


    qint64 m_nStartUserActiveTime_ms = -1;
    qint64 m_nUserActiveTime_ms;
    qint64 m_nUserIdleTime_ms = 0;

    qint32 m_nWorkTime_s = 25 * 60;
    qint32 m_nRestTime_s = 5 * 60;
    qint32 m_nWarningTime_s = 2 * 60;
    quint32 m_nToleranceTime_s = 3;

    QString m_strSetTrayIcon;

    QSettings* m_pAppSettings;  // FIXME - free memory

    void CreateTrayIcon();
    void SetTrayIcon(QString strIcon);
    void LoadValues();
    void CreateLayout();

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // WIDGET_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QtWidgets>
#include <QMenu>
#include <QDebug>

#include "lastuserinput.h"
#include "usertimesettings.h"

class Widget : public QWidget
{
    Q_OBJECT

    QLabel* m_pLabel;

    QAction* m_pQuitAction;
    QAction* m_pOpenAction;
    QAction* m_pPostponeAction;

    QSystemTrayIcon* m_pTrayIcon;

    QTimer m_oTimer;
    QTimer m_oBeepTimer;

    QString m_strSetTrayIcon;

    QSettings* m_pAppSettings;

    void CreateTrayIcon();
    void SetTrayIcon(QString strIcon);
    void LoadValues();
    void CreateLayout();

    void SetIconByTime();

public:
    Widget(QWidget *parent = 0);
    ~Widget() {}

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void OpenWindow();
    void PostponeTheBreak();
};

#endif // WIDGET_H

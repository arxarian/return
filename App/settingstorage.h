#ifndef SETTINGSTORAGE_H
#define SETTINGSTORAGE_H

#include <QtCore>
#include <QObject>
#include <QSettings>
#include <QCoreApplication>

class SettingStorage : public QObject
{
    QSettings* m_pAppSettings = new QSettings(this);
    void StoreValue(const QString& strKey, const QVariant& vValue);
    QVariant RestoreValue(const QString &strKey, const QVariant &vDefaultValue = QVariant()) const;

public:
    SettingStorage(QObject *parent) : QObject(parent) {}

    void StoreWorkTime_s(const qint32 nTime_s);
    qint32 RestoreWorkTime_s() const;

    void StoreRestTime_s(const qint32 nTime_s);
    qint32 RestoreRestTime_s() const;

    void StoreToleranceTime_s(const qint32 nTime_s);
    qint32 RestoreToleranceTime_s() const;

    void StoreAlwaysOnTop(const bool bAlwaysOnTop);
    bool RestoreAlwaysOnTop() const;

    void StoreRunOnStartUp(const bool bRunOnStartUp);
    bool RestoreRunOnStartUp() const;

    void StoreGeometry(const QByteArray& arrGeometry);
    QByteArray RestoreGeometry() const;
};

#endif // SETTINGSTORAGE_H

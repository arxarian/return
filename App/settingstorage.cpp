#include "settingstorage.h"

void SettingStorage::StoreWorkTime_s(const qint32 nTime_s)
{
    StoreValue("work_time", nTime_s);
}

qint32 SettingStorage::RestoreWorkTime_s() const
{
    return RestoreValue("work_time", -1).toInt();
}

void SettingStorage::StoreRestTime_s(const qint32 nTime_s)
{
    StoreValue("rest_time", nTime_s);
}

qint32 SettingStorage::RestoreRestTime_s() const
{
    return RestoreValue("rest_time", -1).toInt();
}

void SettingStorage::StoreToleranceTime_s(const qint32 nTime_s)
{
    StoreValue("tolerance_time", nTime_s);
}

qint32 SettingStorage::RestoreToleranceTime_s() const
{
    return RestoreValue("tolerance_time", -1).toInt();
}

void SettingStorage::StoreAlwaysOnTop(const bool bAlwaysOnTop)
{
    StoreValue("always_on_top", bAlwaysOnTop);
}

bool SettingStorage::RestoreAlwaysOnTop() const
{
    return RestoreValue("always_on_top", false).toBool();
}

void SettingStorage::StoreRunOnStartUp(const bool bRunOnStartUp)
{
    StoreValue("run_on_startup", bRunOnStartUp);
}

bool SettingStorage::RestoreRunOnStartUp() const
{
    return RestoreValue("run_on_startup", false).toBool();
}

void SettingStorage::StoreGeometry(const QByteArray &arrGeometry)
{
    StoreValue("geometry", arrGeometry);
}

QByteArray SettingStorage::RestoreGeometry() const
{
    return RestoreValue("geometry").toByteArray();
}

void SettingStorage::StoreValue(const QString &strKey, const QVariant &vValue)
{
    m_pAppSettings->setValue(strKey, vValue);
}

QVariant SettingStorage::RestoreValue(const QString& strKey, const QVariant &vDefaultValue) const
{
    return m_pAppSettings->value(strKey, vDefaultValue);
}

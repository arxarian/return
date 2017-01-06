#ifndef PROGRAMUPDATER_H
#define PROGRAMUPDATER_H

#include <QObject>

#include <QJsonDocument>
#include <QJsonObject>

#include "urldownloader.h"

class ProgramUpdater : public QObject
{
    Q_OBJECT

    const QString m_strLatestRelaseUrl;

    QString m_strLatestVersion;

    bool IsLatestVersionNewer();

    UrlDownloader* m_pUrlDownloader = new UrlDownloader(this);

protected:
    void SetLatestVersion(const QString& strLatestVersion);

public:
    explicit ProgramUpdater(const QString strLatestReleaseUrl, QObject *parent = 0);

signals:
    void UpdateCheckFinished(bool bUpdateAvaible, QString strLatestVersion);
    void VersionInfoAvaible();

public slots:
    void CheckForUpdates(); // entry point

private slots:
    virtual void ExtractLatestVersionInfo(const QByteArray &arrUrlContent) = 0;
};

#endif // PROGRAMUPDATER_H

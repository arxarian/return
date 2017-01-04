#ifndef PROGRAMUPDATER_H
#define PROGRAMUPDATER_H

#include <QObject>

#include <QJsonDocument>
#include <QJsonObject>

#include "urldownloader.h"

class ProgramUpdater : public QObject
{
    Q_OBJECT

    const QString m_strLatestRelaseUrl = "https://api.github.com/repos/hubnerp/return/releases/latest";

    QString m_strLatestVersion;

    void DownloadVersionInfoSource();
    bool IsLatestVersionNewer();

    UrlDownloader* m_pUrlDownloader = new UrlDownloader(this);

public:
    explicit ProgramUpdater(QObject *parent = 0);

signals:
    void UpdateCheckFinished(bool bUpdateAvaible, QString strLatestVersion);
    void VersionInfoAvaible();

public slots:
    void CheckForUpdates();
    void UpdateProgram();

private slots:
    void ExtractLatestVersionInfo(const QByteArray &arrUrlContent);    // TODO - should be virtual
};

#endif // PROGRAMUPDATER_H

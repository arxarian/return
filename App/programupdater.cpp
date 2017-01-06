#include "programupdater.h"

ProgramUpdater::ProgramUpdater(const QUrl oLatestReleaseUrl, QObject *parent) : QObject(parent), m_oLatestRelaseUrl(oLatestReleaseUrl)
{
    // empty constructor
}

void ProgramUpdater::CheckForUpdates()
{
    connect(m_pUrlDownloader, &UrlDownloader::DownloadFinished, [this](QByteArray arrUrlContent) {

        ExtractLatestVersionInfo(arrUrlContent);

        bool bNewerVersionExists = IsLatestVersionNewer();

        emit UpdateCheckFinished(bNewerVersionExists, m_strLatestVersion);
    });

    m_pUrlDownloader->DownloadUrl(m_oLatestRelaseUrl);
}

bool ProgramUpdater::IsLatestVersionNewer()
{
    const QStringList arrLatestVersionParts = m_strLatestVersion.split('.');
    const QStringList arrCurrentVersionParts = QString(APP_VERSION).split('.');

    for(qint32 nPartIndex = 0; nPartIndex < qMin(arrLatestVersionParts.size(), arrCurrentVersionParts.size()); ++nPartIndex)
    {
        if(arrLatestVersionParts.at(nPartIndex).toInt() > arrCurrentVersionParts.at(nPartIndex).toInt())
        {
            return true;
        }
        else if(arrLatestVersionParts.at(nPartIndex).toInt() < arrCurrentVersionParts.at(nPartIndex).toInt())
        {
            return false;
        }
    }
    return false;
}

void ProgramUpdater::SetLatestVersion(const QString &strLatestVersion)
{
    m_strLatestVersion = strLatestVersion;
}

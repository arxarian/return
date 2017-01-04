#include "programupdater.h"

ProgramUpdater::ProgramUpdater(QObject *parent) : QObject(parent)
{
//    qDebug() << "is there a new version?";
//    DownloadVersionInfoSource();
//    CheckForUpdates();
}

void ProgramUpdater::CheckForUpdates()
{
    connect(m_pUrlDownloader, &UrlDownloader::DownloadFinished, [this](QByteArray arrUrlContent) {

        ExtractLatestVersionInfo(arrUrlContent);

        bool bNewerVersionExists = IsLatestVersionNewer();

        emit UpdateCheckFinished(bNewerVersionExists, m_strLatestVersion);
    });

    m_pUrlDownloader->DownloadUrl(m_strLatestRelaseUrl);
}

void ProgramUpdater::UpdateProgram()
{
    // TODO - move the dialog part to GUI
    // if there is a newer version, ask the user if he wants to update
    //  display a dialog with new version number and question: "do you want to download new version" and yes or no buttons
    //  if user clicks yes, open broswer with download url
    //   get download url from program updater (or url can be obtain as argument of function which displayes dialog)
    //  if user clicks no, do nothing

    // if there is no new version, do nothing
}

void ProgramUpdater::DownloadVersionInfoSource()
{
    //   start downloading the page containg info about latest version
    //    create request
    //   do not wait untile the downloading is completed (non blocking downloading)
    //   get notifaction when download is finished
    //   Extract latest version info from source
    //    return latest version number // NOTE - to whom?
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

void ProgramUpdater::ExtractLatestVersionInfo(const QByteArray& arrUrlContent)
{
    QJsonDocument oJsonDoc = QJsonDocument::fromJson(arrUrlContent);
    if(!oJsonDoc.isNull())
    {
        if(oJsonDoc.isObject())
        {
            QJsonObject oJsonObject = oJsonDoc.object();
            m_strLatestVersion = oJsonObject["tag_name"].toString();
        }
        else
        {
            qDebug() << "not an object";
        }
    }
    else
    {
        qDebug() << "invalid json";
    }
}

#include "urldownloader.h"

UrlDownloader::UrlDownloader(QObject *parent) : QObject(parent)
{

}

void UrlDownloader::DownloadUrl(const QUrl &oUrl)
{
    qDebug() << QTime::currentTime();   // DEBUG
    m_pResponse = m_oManager.get(QNetworkRequest(oUrl));
    qDebug() << QTime::currentTime();   // DEBUG

    if(m_pResponse == nullptr) return;

    connect(m_pResponse, &QNetworkReply::finished, this, &UrlDownloader::OnReplyFinished);

    connect(m_pResponse, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),
            [=](QNetworkReply::NetworkError eError)
    {
        const QMetaObject &oMetaObject = QNetworkReply::staticMetaObject;
        int nEnumIndex = oMetaObject.indexOfEnumerator("NetworkError");

        qDebug() << "error" << eError;

        emit Error(QString(oMetaObject.enumerator(nEnumIndex).valueToKey(m_pResponse->error())));
    });
}

void UrlDownloader::OnReplyFinished()
{
    if(m_pResponse->error() != QNetworkReply::NoError)
    {
        qDebug() << "cannot finished download request, return";
        return;
    }

    QByteArray arrUrlContent = m_pResponse->readAll();

    if(!arrUrlContent.isEmpty())
    {
        emit DownloadFinished(arrUrlContent);
    }
}

#include "urldownloader.h"

UrlDownloader::UrlDownloader(QObject *parent) : QObject(parent)
{
    //
}

void UrlDownloader::DownloadUrl(const QString &strUrl)
{
    m_pResponse = m_oManager.get(QNetworkRequest(QUrl(strUrl)));

    if(m_pResponse == nullptr) return;

    connect(m_pResponse, &QNetworkReply::finished, this, &UrlDownloader::OnReplyFinished);

    connect(m_pResponse,
            static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),
            [=](QNetworkReply::NetworkError eError) {
        qDebug() << "error" << eError;
    });
}

void UrlDownloader::OnReplyFinished()
{
    if(m_pResponse->error() != QNetworkReply::NoError)
    {
//        const QMetaObject &oMetaObject = QNetworkReply::staticMetaObject;
//        int nEnumIndex = oMetaObject.indexOfEnumerator("NetworkError");
//        emit Error(QString(oMetaObject.enumerator(nEnumIndex).valueToKey(m_pResponse->error())));
        qDebug() << "response error" << m_pResponse->error();
        return;
    }

    QByteArray arrUrlContent = m_pResponse->readAll();

    if(!arrUrlContent.isEmpty())
    {
        emit DownloadFinished(arrUrlContent);
    }
}

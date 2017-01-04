#ifndef URLDOWNLOADER_H
#define URLDOWNLOADER_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>

class UrlDownloader : public QObject
{
    Q_OBJECT

    QNetworkAccessManager m_oManager;
    QNetworkReply* m_pResponse;

public:
    explicit UrlDownloader(QObject *parent = 0);

    void DownloadUrl(const QString& strUrl);

signals:
    void DownloadFinished(QByteArray arrUrlContent);

private slots:
    void OnReplyFinished();
};

#endif // URLDOWNLOADER_H

#ifndef URLDOWNLOADER_H
#define URLDOWNLOADER_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QMetaEnum>

class UrlDownloader : public QObject
{
    Q_OBJECT

    QNetworkAccessManager m_oManager;
    QNetworkReply* m_pResponse;

public:
    explicit UrlDownloader(QObject *parent = 0);

public slots:
    void DownloadUrl(const QString& strUrl);

private slots:
    void OnReplyFinished();

signals:
    void DownloadFinished(QByteArray arrUrlContent);
    void Error(QString strError);
};

#endif // URLDOWNLOADER_H

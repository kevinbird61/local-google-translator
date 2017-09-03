#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QNetworkAccessManager>
#include <QHttpMultiPart>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrlQuery>
#include <QString>
#include <QVariant>
#include <QObject>
#include <QDebug>
#include <QUrl>

#define SERVER_URL "http://kevin.imslab.org:3000/translate"

class translator : public QObject
{
    Q_OBJECT
public:
    translator(QObject *parent = 0);
    void makeTrans(QString s_to, QString s_query);
    QString getServerUrl();
    void setServerUrl(QString newUrl);

public slots:
    void getReply(QNetworkReply *reply);

signals:
    void getTrans(QNetworkReply *reply);

private:
    QNetworkAccessManager manager;
    QString serverUrl;
};

#endif // TRANSLATOR_H

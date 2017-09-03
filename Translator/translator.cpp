#include "translator.h"

translator::translator(QObject *parent)
    : serverUrl(SERVER_URL)
{
    QObject::connect(&manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(getReply(QNetworkReply*)));
}

void translator::makeTrans(QString s_to, QString s_query)
{
    // initialize request body
    QUrlQuery postData;
    postData.addQueryItem("to", s_to.toStdString().c_str());
    postData.addQueryItem("q", s_query.toStdString().c_str());

    QUrl url = QUrl(serverUrl);
    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded; charset=utf-8");
    manager.post(req, postData.toString().toUtf8());
}

QString translator::getServerUrl()
{
    return serverUrl;
}

void translator::setServerUrl(QString newUrl)
{
    serverUrl = newUrl;
    qDebug() << "Server url now has changed to:" << serverUrl;
}

void translator::getReply(QNetworkReply *reply)
{
    emit getTrans(reply);
}


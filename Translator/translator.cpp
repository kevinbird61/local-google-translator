#include "translator.h"

translator::translator(QObject *parent)
{
    QObject::connect(&manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(getReply(QNetworkReply*)));
}

void translator::makeTrans(QString s_to, QString s_query)
{
    // initialize request body
    QUrlQuery postData;
    postData.addQueryItem("to", s_to.toStdString().c_str());
    postData.addQueryItem("q", s_query.toStdString().c_str());

    QUrl url = QUrl(SERVER_URL);
    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded; charset=utf-8");
    manager.post(req, postData.toString().toUtf8());
}

void translator::getReply(QNetworkReply *reply)
{
    emit getTrans(reply);
}


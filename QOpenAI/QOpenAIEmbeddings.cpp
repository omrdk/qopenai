#include "QOpenAIEmbeddings.h"

QOpenAIEmbeddings::QOpenAIEmbeddings(QObject *parent) : QOpenAI{parent} {

}

void QOpenAIEmbeddings::sendRequest() {
    QNetworkRequest request(getUrl(_endPoint));
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body.insert("input", _input);
    body.insert("model", _model);
    body.insert("user", _user);
    QJsonDocument json;
    json.setObject(body);
    QByteArray jsonBytes = json.toJson();
    QNetworkReply *reply = _networkManager->post(request, jsonBytes);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonObject response = QJsonDocument::fromJson(reply->readAll()).object();
            emit requestFinished(response);
        } else {
            emit requestError(reply->errorString());
        }
        reply->deleteLater();
    });
}

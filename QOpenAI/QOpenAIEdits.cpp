#include "QOpenAIEdits.h"

QOpenAIEdits::QOpenAIEdits(QObject *parent) : QOpenAI{parent} {

}

void QOpenAIEdits::sendRequest() {
    QNetworkRequest request(getUrl(_endPoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QJsonObject body;
    body.insert("model", _model);
    body.insert("input", _input);
    body.insert("instruction", _instruction);
    body.insert("temperature", _temperature);
    body.insert("top_p", _topP);
    body.insert("n", _n);
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

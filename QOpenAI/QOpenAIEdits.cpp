#include "QOpenAIEdits.h"

QOpenAIEdits::QOpenAIEdits(QObject *parent)
    : QOpenAI{parent}
{

}

void QOpenAIEdits::sendRequest(const QString &content) {
    QNetworkRequest request(getUrl(_endPoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QJsonObject body;
    body.insert("model", _model);
    body.insert("input", content);
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
            QByteArray response = reply->readAll();
            QJsonDocument responseJson = QJsonDocument::fromJson(response);
            QString content = responseJson.object().value("choices").toArray()[0].toObject().value("text").toString();
            emit requestFinished(content);
        } else {
            emit requestError(reply->errorString());
        }
        reply->deleteLater();
    });
}

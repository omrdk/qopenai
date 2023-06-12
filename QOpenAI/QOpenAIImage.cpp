#include "QOpenAIImage.h"

QOpenAIImage::QOpenAIImage(QObject *parent) : QOpenAI{parent} {

}

void QOpenAIImage::sendRequest() {
    QNetworkRequest request(getUrl(_endPoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QJsonObject body;
    body.insert("prompt", _prompt);
    body.insert("n", _n);
    body.insert("size", _imageSize);
    body.insert("response_format", _responseFormat);
    body.insert("user", _user);
    QJsonDocument json(body);
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

#include "QOpenAIImage.h"

QOpenAIImage::QOpenAIImage(QObject *parent)
    : QOpenAI{parent}
{

}

void QOpenAIImage::sendRequest(const QString &prompt) { // prompt is also an abs file path for image edits and variations
    QNetworkRequest request(getUrl(_endPoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QJsonObject body;
    body.insert("prompt", prompt);
    body.insert("n", _n);
    body.insert("size", _imageSize);
    body.insert("response_format", _responseFormat);
    body.insert("user", _user);
    QJsonDocument json(body);
    qDebug() << json; // - !
    QByteArray jsonBytes = json.toJson();
    QNetworkReply *reply = _networkManager->post(request, jsonBytes);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument responseJson = QJsonDocument::fromJson(response);
            for(const auto& data: responseJson.object().value("data").toArray()) {
                QString url = data.toObject().value("url").toString();
                emit requestFinished(url);
            }
        } else {
            emit requestError(reply->errorString());
        }
        reply->deleteLater();
    });
}

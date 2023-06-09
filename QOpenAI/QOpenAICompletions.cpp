#include "QOpenAICompletions.h"

QOpenAICompletions::QOpenAICompletions(QObject *parent) : QOpenAI{parent} {

}

void QOpenAICompletions::sendRequest() {
    QNetworkRequest request(getUrl(_endPoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QJsonObject body;
    body.insert("model", _model);
    body.insert("prompt", _prompt);
    body.insert("suffix", _suffix);
    body.insert("max_tokens", 7);
    body.insert("temperature", _temperature);
    body.insert("top_p", _topP);
    body.insert("n", _n);
    body.insert("stream", _stream);
    body.insert("logprobs", _logProbs);
    body.insert("echo", _echo);
    body.insert("stop", _stop);
    body.insert("presence_penalty", _presencePenalty);
    body.insert("frequency_penalty", _frequencyPenalty);
    body.insert("best_of", _bestOf);
    body.insert("logit_bias", QJsonObject::fromVariantMap(_logitBias));
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

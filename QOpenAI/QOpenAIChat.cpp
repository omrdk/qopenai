#include "QOpenAIChat.h"

QOpenAIChat::QOpenAIChat(QObject *parent) : QOpenAI{parent} {

}

void QOpenAIChat::sendRequest(const QString &content) {
    _messageModel->insertMessage(content, QOpenAIMessage::Role::USER);
    QNetworkRequest request(getUrl(_endPoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QJsonObject body;
    body.insert("model", _model);
    QJsonArray messagesBranch;
    const auto messages = _messageModel->getMessages();
    for(auto message: messages) {
        QJsonObject branch;
        branch.insert("role", message->getRoleString());
        branch.insert("content", message->getContent());
        messagesBranch.append(branch);
    }
    body.insert("messages", messagesBranch);
    body.insert("temperature", _temperature);
    body.insert("top_p", _topP);
    body.insert("n", _n);
    body.insert("stream", _stream);
    body.insert("stop", _stop);
    body.insert("max_tokens", _maxTokens);
    body.insert("presence_penalty", _presencePenalty);
    body.insert("frequency_penalty", _frequencyPenalty);
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

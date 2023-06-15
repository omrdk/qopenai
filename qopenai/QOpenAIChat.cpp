#include "QOpenAIChat.h"

QOpenAIChat::QOpenAIChat(QObject *parent) : QOpenAI{parent} {

}

QOpenAIChat::QOpenAIChat(const QString &model, QObject *parent)
    : QOpenAI{parent}, m_model(model)
{

}

void QOpenAIChat::sendRequest() {
    if(_messageModel->getMessages().empty()) {
        emit requestError("Message model doesn't contain any message!");
        return;
    }
    QNetworkRequest request(getUrl(_endPoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QJsonObject body;
    body.insert("model", m_model);
    QJsonArray messagesBranch;
    if(!m_systemMessage.isEmpty()) {
        QOpenAIMessage message;
        QJsonObject branch;
        branch.insert("role", "system");
        branch.insert("content", m_systemMessage);
        messagesBranch.append(branch);
    }
    const auto messages = _messageModel->getMessages();
    for(auto message: messages) {
        QJsonObject branch;
        branch.insert("role", message->getRoleString());
        branch.insert("content", message->getContent());
        messagesBranch.append(branch);
    }
    body.insert("messages", messagesBranch);
    body.insert("temperature", m_temperature);
    body.insert("top_p", m_topP);
    body.insert("n", m_n);
    body.insert("stream", m_stream);
    body.insert("stop", m_stop);
    body.insert("max_tokens", m_maxTokens);
    body.insert("presence_penalty", m_presencePenalty);
    body.insert("frequency_penalty", m_frequencyPenalty);
    body.insert("logit_bias", QJsonObject::fromVariantMap(m_logitBias));
    body.insert("user", m_user);
    QJsonDocument json;
    json.setObject(body);
    QByteArray jsonBytes = json.toJson();
    QNetworkReply *reply = _networkManager->post(request, jsonBytes);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonObject response = QJsonDocument::fromJson(reply->readAll()).object();
            emit requestFinished(response);
        } else {
            QMetaEnum metaEnum = QMetaEnum::fromType<QNetworkReply::NetworkError>();
            emit requestError(metaEnum.valueToKey(reply->error()));
        }
        reply->deleteLater();
    });
}

QString QOpenAIChat::getModel() const {
    return m_model;
}

void QOpenAIChat::setModel(const QString& model) {
    if (m_model != model) {
        m_model = model;
        emit modelChanged();
    }
}

float QOpenAIChat::getTemperature() const {
    return m_temperature;
}

void QOpenAIChat::setTemperature(float temperature) {
    if (m_temperature != temperature) {
        m_temperature = temperature;
        emit temperatureChanged();
    }
}

float QOpenAIChat::getTopP() const {
    return m_topP;
}

void QOpenAIChat::setTopP(float topP) {
    if (m_topP != topP) {
        m_topP = topP;
        emit topPChanged();
    }
}

int QOpenAIChat::getN() const {
    return m_n;
}

void QOpenAIChat::setN(int n) {
    if (m_n != n) {
        m_n = n;
        emit nChanged();
    }
}

bool QOpenAIChat::getStream() const {
    return m_stream;
}

void QOpenAIChat::setStream(bool stream) {
    if (m_stream != stream) {
        m_stream = stream;
        emit streamChanged();
    }
}

QString QOpenAIChat::getStop() const {
    return m_stop;
}

void QOpenAIChat::setStop(const QString& stop) {
    if (m_stop != stop) {
        m_stop = stop;
        emit stopChanged();
    }
}

int QOpenAIChat::getMaxTokens() const {
    return m_maxTokens;
}

void QOpenAIChat::setMaxTokens(int maxTokens) {
    if (m_maxTokens != maxTokens) {
        m_maxTokens = maxTokens;
        emit maxTokensChanged();
    }
}

float QOpenAIChat::getPresencePenalty() const {
    return m_presencePenalty;
}

void QOpenAIChat::setPresencePenalty(float presencePenalty) {
    if (m_presencePenalty != presencePenalty) {
        m_presencePenalty = presencePenalty;
        emit presencePenaltyChanged();
    }
}

float QOpenAIChat::getFrequencyPenalty() const {
    return m_frequencyPenalty;
}

void QOpenAIChat::setFrequencyPenalty(float frequencyPenalty) {
    if (m_frequencyPenalty != frequencyPenalty) {
        m_frequencyPenalty = frequencyPenalty;
        emit frequencyPenaltyChanged();
    }
}

QVariantMap QOpenAIChat::getLogitBias() const {
    return m_logitBias;
}

void QOpenAIChat::setLogitBias(const QVariantMap& logitBias) {
    if (m_logitBias != logitBias) {
        m_logitBias = logitBias;
        emit logitBiasChanged();
    }
}

QString QOpenAIChat::getUser() const {
    return m_user;
}

void QOpenAIChat::setUser(const QString& user) {
    if (m_user != user) {
        m_user = user;
        emit userChanged();
    }
}

QString QOpenAIChat::getSystemMessage() const {
    return m_systemMessage;
}

void QOpenAIChat::setSystemMessage(const QString& systemMessage) {
    if (m_systemMessage != systemMessage) {
        m_systemMessage = systemMessage;
        emit systemMessageChanged();
    }
}

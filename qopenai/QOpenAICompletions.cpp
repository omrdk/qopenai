#include "QOpenAICompletions.h"

QOpenAICompletions::QOpenAICompletions(QObject *parent) : QOpenAI{parent} {

}

QOpenAICompletions::QOpenAICompletions(const QString &model, QObject *parent)
    : QOpenAI{parent}, m_model(model)
{

}

void QOpenAICompletions::sendRequest() {
    QNetworkRequest request(getUrl(_endPoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QJsonObject body;
    body.insert("model", m_model);
    body.insert("prompt", m_prompt);
    body.insert("suffix", m_suffix);
    body.insert("max_tokens", m_maxTokens);
    body.insert("temperature", m_temperature);
    body.insert("top_p", m_topP);
    body.insert("n", m_n);
    body.insert("stream", m_stream);
    body.insert("logprobs", m_logProbs);
    body.insert("echo", m_echo);
    body.insert("stop", m_stop);
    body.insert("presence_penalty", m_presencePenalty);
    body.insert("frequency_penalty", m_frequencyPenalty);
    body.insert("best_of", m_bestOf);
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
            emit requestError(reply->errorString());
        }
        reply->deleteLater();
    });
}

QString QOpenAICompletions::getModel() const {
    return m_model;
}

void QOpenAICompletions::setModel(const QString& model) {
    if (m_model != model) {
        m_model = model;
        emit modelChanged();
    }
}

QString QOpenAICompletions::getPrompt() const {
    return m_prompt;
}

void QOpenAICompletions::setPrompt(const QString& prompt) {
    if (m_prompt != prompt) {
        m_prompt = prompt;
        emit promptChanged();
    }
}

QString QOpenAICompletions::getSuffix() const {
    return m_suffix;
}

void QOpenAICompletions::setSuffix(const QString& suffix) {
    if (m_suffix != suffix) {
        m_suffix = suffix;
        emit suffixChanged();
    }
}

int QOpenAICompletions::getMaxTokens() const {
    return m_maxTokens;
}

void QOpenAICompletions::setMaxTokens(int maxTokens) {
    if (m_maxTokens != maxTokens) {
        m_maxTokens = maxTokens;
        emit maxTokensChanged();
    }
}

float QOpenAICompletions::getTemperature() const {
    return m_temperature;
}

void QOpenAICompletions::setTemperature(float temperature) {
    if (m_temperature != temperature) {
        m_temperature = temperature;
        emit temperatureChanged();
    }
}

float QOpenAICompletions::getTopP() const {
    return m_topP;
}

void QOpenAICompletions::setTopP(float topP) {
    if (m_topP != topP) {
        m_topP = topP;
        emit topPChanged();
    }
}

int QOpenAICompletions::getN() const {
    return m_n;
}

void QOpenAICompletions::setN(int n) {
    if (m_n != n) {
        m_n = n;
        emit nChanged();
    }
}

bool QOpenAICompletions::getStream() const {
    return m_stream;
}

void QOpenAICompletions::setStream(bool stream) {
    if (m_stream != stream) {
        m_stream = stream;
        emit streamChanged();
    }
}

int QOpenAICompletions::getLogProbs() const {
    return m_logProbs;
}

void QOpenAICompletions::setLogProbs(int logProbs) {
    if (m_logProbs != logProbs) {
        m_logProbs = logProbs;
        emit logProbsChanged();
    }
}

bool QOpenAICompletions::getEcho() const {
    return m_echo;
}

void QOpenAICompletions::setEcho(bool echo) {
    if (m_echo != echo) {
        m_echo = echo;
        emit echoChanged();
    }
}

QString QOpenAICompletions::getStop() const {
    return m_stop;
}

void QOpenAICompletions::setStop(const QString& stop) {
    if (m_stop != stop) {
        m_stop = stop;
        emit stopChanged();
    }
}

float QOpenAICompletions::getPresencePenalty() const {
    return m_presencePenalty;
}

void QOpenAICompletions::setPresencePenalty(float presencePenalty) {
    if (m_presencePenalty != presencePenalty) {
        m_presencePenalty = presencePenalty;
        emit presencePenaltyChanged();
    }
}

float QOpenAICompletions::getFrequencyPenalty() const {
    return m_frequencyPenalty;
}

void QOpenAICompletions::setFrequencyPenalty(float frequencyPenalty) {
    if (m_frequencyPenalty != frequencyPenalty) {
        m_frequencyPenalty = frequencyPenalty;
        emit frequencyPenaltyChanged();
    }
}

int QOpenAICompletions::getBestOf() const {
    return m_bestOf;
}

void QOpenAICompletions::setBestOf(int bestOf) {
    if (m_bestOf != bestOf) {
        m_bestOf = bestOf;
        emit bestOfChanged();
    }
}

QVariantMap QOpenAICompletions::getLogitBias() const {
    return m_logitBias;
}

void QOpenAICompletions::setLogitBias(const QVariantMap& logitBias) {
    if (m_logitBias != logitBias) {
        m_logitBias = logitBias;
        emit logitBiasChanged();
    }
}

QString QOpenAICompletions::getUser() const {
    return m_user;
}

void QOpenAICompletions::setUser(const QString& user) {
    if (m_user != user) {
        m_user = user;
        emit userChanged();
    }
}


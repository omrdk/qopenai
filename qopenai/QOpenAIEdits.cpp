#include "QOpenAIEdits.h"

QOpenAIEdits::QOpenAIEdits(QObject *parent) : QOpenAI{parent} {

}

QOpenAIEdits::QOpenAIEdits(const QString &model, const QString &instruction, QObject *parent)
    : QOpenAI{parent}, m_model(model), m_instruction(instruction)
{

}

void QOpenAIEdits::sendRequest() {
    QNetworkRequest request(getUrl(_endPoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QJsonObject body;
    body.insert("model", m_model);
    body.insert("input", m_input);
    body.insert("instruction", m_instruction);
    body.insert("temperature", m_temperature);
    body.insert("top_p", m_topP);
    body.insert("n", m_n);
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

QString QOpenAIEdits::getModel() const {
    return m_model;
}

void QOpenAIEdits::setModel(const QString& model) {
    if (m_model != model) {
        m_model = model;
        emit modelChanged();
    }
}

QString QOpenAIEdits::getInput() const {
    return m_input;
}

void QOpenAIEdits::setInput(const QString& input) {
    if (m_input != input) {
        m_input = input;
        emit inputChanged();
    }
}

QString QOpenAIEdits::getInstruction() const {
    return m_instruction;
}

void QOpenAIEdits::setInstruction(const QString& instruction) {
    if (m_instruction != instruction) {
        m_instruction = instruction;
        emit instructionChanged();
    }
}

int QOpenAIEdits::getN() const {
    return m_n;
}

void QOpenAIEdits::setN(int n) {
    if (m_n != n) {
        m_n = n;
        emit nChanged();
    }
}

float QOpenAIEdits::getTemperature() const {
    return m_temperature;
}

void QOpenAIEdits::setTemperature(float temperature) {
    if (m_temperature != temperature) {
        m_temperature = temperature;
        emit temperatureChanged();
    }
}

float QOpenAIEdits::getTopP() const {
    return m_topP;
}

void QOpenAIEdits::setTopP(float topP) {
    if (m_topP != topP) {
        m_topP = topP;
        emit topPChanged();
    }
}

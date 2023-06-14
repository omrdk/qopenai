#include "QOpenAIImage.h"

QOpenAIImage::QOpenAIImage(QObject *parent) : QOpenAI{parent} {

}

QOpenAIImage::QOpenAIImage(const QString &prompt, QObject *parent)
    : QOpenAI{parent}, m_prompt(prompt)
{

}

void QOpenAIImage::sendRequest() {
    QNetworkRequest request(getUrl(_endPoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QJsonObject body;
    body.insert("prompt", m_prompt);
    body.insert("n", m_n);
    body.insert("size", m_size);
    body.insert("response_format", m_responseFormat);
    body.insert("user", m_user);
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

QString QOpenAIImage::getPrompt() const {
    return m_prompt;
}

void QOpenAIImage::setPrompt(const QString& prompt) {
    if (m_prompt != prompt) {
        m_prompt = prompt;
        emit promptChanged();
    }
}

int QOpenAIImage::getN() const {
    return m_n;
}

void QOpenAIImage::setN(int n) {
    if (m_n != n) {
        m_n = n;
        emit nChanged();
    }
}

QString QOpenAIImage::getSize() const {
    return m_size;
}

void QOpenAIImage::setSize(const QString& size) {
    if (m_size != size) {
        m_size = size;
        emit sizeChanged();
    }
}

QString QOpenAIImage::getResponseFormat() const {
    return m_responseFormat;
}

void QOpenAIImage::setResponseFormat(const QString& responseFormat) {
    if (m_responseFormat != responseFormat) {
        m_responseFormat = responseFormat;
        emit responseFormatChanged();
    }
}

QString QOpenAIImage::getUser() const {
    return m_user;
}

void QOpenAIImage::setUser(const QString& user) {
    if (m_user != user) {
        m_user = user;
        emit userChanged();
    }
}

#include "QOpenAIEmbeddings.h"

QOpenAIEmbeddings::QOpenAIEmbeddings(QObject *parent) : QOpenAI{parent} {

}

QOpenAIEmbeddings::QOpenAIEmbeddings(const QString &model, const QString &input, QObject *parent)
    : QOpenAI{parent}, m_model(model), m_input(input)
{

}

void QOpenAIEmbeddings::sendRequest() {
    QNetworkRequest request(getUrl(_endPoint));
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body.insert("model", m_model);
    body.insert("input", m_input);
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

QString QOpenAIEmbeddings::getModel() const {
    return m_model;
}

void QOpenAIEmbeddings::setModel(const QString& model) {
    if (m_model != model) {
        m_model = model;
        emit modelChanged();
    }
}

QString QOpenAIEmbeddings::getInput() const {
    return m_input;
}

void QOpenAIEmbeddings::setInput(const QString& input) {
    if (m_input != input) {
        m_input = input;
        emit inputChanged();
    }
}

QString QOpenAIEmbeddings::getUser() const {
    return m_user;
}

void QOpenAIEmbeddings::setUser(const QString& user) {
    if (m_user != user) {
        m_user = user;
        emit userChanged();
    }
}

#include "QOpenAIModerations.h"
#include "QOpenAIAuthorization.h"

QOpenAIModerations::QOpenAIModerations(QObject *parent) : QOpenAI{parent} {

}

QOpenAIModerations::QOpenAIModerations(const QString &input, QObject *parent)
    : QOpenAI{parent}, m_input(input)
{

}

void QOpenAIModerations::sendRequest() {
    QNetworkRequest request(getUrl(_endPoint));
    const auto key = QOpenAIAuthorization::Authorizer().getKey();
    request.setRawHeader("Authorization", ("Bearer " + key).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject body;
    body.insert("input", m_input);
    body.insert("model", m_model);
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

QString QOpenAIModerations::getInput() const {
    return m_input;
}

void QOpenAIModerations::setInput(const QString& input) {
    if (m_input != input) {
        m_input = input;
        emit inputChanged();
    }
}

QString QOpenAIModerations::getModel() const {
    return m_model;
}

void QOpenAIModerations::setModel(const QString& model) {
    if (m_model != model) {
        m_model = model;
        emit modelChanged();
    }
}

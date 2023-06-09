#include "QOpenAIAudio.h"
#include "QOpenAIAuthorization.h"

QOpenAIAudio::QOpenAIAudio(QObject *parent) : QOpenAI{parent} {

}

QOpenAIAudio::QOpenAIAudio(const QString &model, const QString &file, QObject *parent)
    : QOpenAI{parent}, m_model(model), m_file(file)
{

}

void QOpenAIAudio::sendRequest() {
    QUrl fileUrl(m_file);
    if(fileUrl.isLocalFile()) {
        m_file = fileUrl.toLocalFile();
    }
    if(!isPathExist(m_file)) {
        emit requestError("Provided audio file path doesn't exist!");
        return;
    }
    QNetworkRequest request(getUrl(_endPoint));
    const auto key = QOpenAIAuthorization::Authorizer().getKey();
    request.setRawHeader("Authorization", ("Bearer " + key).toUtf8());
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart modelPart;
    modelPart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
    modelPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"model\"");
    modelPart.setBody(m_model.toUtf8());
    QFileInfo audioFileInfo(m_file);
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, "audio/wav");
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"file\"; filename=\"" + audioFileInfo.fileName() + "\"");
    QFile *file = new QFile(m_file);
    file->open(QIODevice::ReadOnly);
    filePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(filePart);
    multiPart->append(modelPart);
    if(_endPoint == QOpenAI::EndPoints::Transcriptions) {
        QHttpPart languagePart;
        languagePart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
        languagePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"language\"");
        languagePart.setBody(m_language.toUtf8());
        multiPart->append(languagePart);
    }
    QNetworkReply *reply = _networkManager->post(request, multiPart);
    multiPart->setParent(reply);
    connect(reply, &QNetworkReply::finished, this, [this, file, reply]() {
        file->close();
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

QString QOpenAIAudio::getFile() const {
    return m_file;
}

void QOpenAIAudio::setFile(const QString& file) {
    if (m_file != file) {
        m_file = file;
        emit fileChanged();
    }
}

QString QOpenAIAudio::getModel() const {
    return m_model;
}

void QOpenAIAudio::setModel(const QString& model) {
    if (m_model != model) {
        m_model = model;
        emit modelChanged();
    }
}

QString QOpenAIAudio::getPrompt() const {
    return m_prompt;
}

void QOpenAIAudio::setPrompt(const QString& prompt) {
    if (m_prompt != prompt) {
        m_prompt = prompt;
        emit promptChanged();
    }
}

QString QOpenAIAudio::getResponseFormat() const {
    return m_responseFormat;
}

void QOpenAIAudio::setResponseFormat(const QString& responseFormat) {
    if (m_responseFormat != responseFormat) {
        m_responseFormat = responseFormat;
        emit responseFormatChanged();
    }
}

float QOpenAIAudio::getTemperature() const {
    return m_temperature;
}

void QOpenAIAudio::setTemperature(float temperature) {
    if (m_temperature != temperature) {
        m_temperature = temperature;
        emit temperatureChanged();
    }
}

QString QOpenAIAudio::getLanguage() const {
    return m_language;
}

void QOpenAIAudio::setLanguage(const QString &language) {
    if(m_language != language) {
        m_language = language;
        emit languageChanged();
    }
}

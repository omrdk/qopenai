#include "QOpenAIImageVariations.h"

#include <QImageReader>

QOpenAIImageVariations::QOpenAIImageVariations(QObject *parent) : QOpenAI{parent} {
}

QOpenAIImageVariations::QOpenAIImageVariations(const QString &image, QObject *parent)
    : QOpenAI{parent}, m_image(image)
{

}

void QOpenAIImageVariations::sendRequest() {
    if(!isPathExist(m_image)) {
        emit requestError("Provided image file path doesn't exist!");
        return;
    }
    QNetworkRequest request(getUrl(_endPoint));
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QFileInfo fileInfo(m_image);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"image\"; filename=\"" + fileInfo.fileName() + "\"");
    imagePart.setBody(m_image.toUtf8());
    QHttpPart nPart;
    nPart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
    nPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"n\"");
    nPart.setBody(QByteArray::number(m_n));
    QHttpPart sizePart;
    sizePart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
    sizePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"size\"");
    sizePart.setBody(m_size.toUtf8());
    QUrl fileUrl(m_image);
    if(fileUrl.isLocalFile()) {
        m_image = fileUrl.toLocalFile();
    }
    QFile *file = new QFile(m_image);
    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(imagePart);
    multiPart->append(nPart);
    multiPart->append(sizePart);
    QNetworkReply *reply = _networkManager->post(request, multiPart);
    multiPart->setParent(reply);
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

QString QOpenAIImageVariations::getImage() const {
    return m_image;
}

void QOpenAIImageVariations::setImage(const QString& image) {
    if (m_image != image) {
        m_image = image;
        emit imageChanged();
    }
}

int QOpenAIImageVariations::getN() const {
    return m_n;
}

void QOpenAIImageVariations::setN(int n) {
    if (m_n != n) {
        m_n = n;
        emit nChanged();
    }
}

QString QOpenAIImageVariations::getSize() const {
    return m_size;
}

void QOpenAIImageVariations::setSize(const QString& size) {
    if (m_size != size) {
        m_size = size;
        emit sizeChanged();
    }
}

QString QOpenAIImageVariations::getResponseFormat() const {
    return m_responseFormat;
}

void QOpenAIImageVariations::setResponseFormat(const QString& responseFormat) {
    if (m_responseFormat != responseFormat) {
        m_responseFormat = responseFormat;
        emit responseFormatChanged();
    }
}

QString QOpenAIImageVariations::getUser() const {
    return m_user;
}

void QOpenAIImageVariations::setUser(const QString& user) {
    if (m_user != user) {
        m_user = user;
        emit userChanged();
    }
}

#include "QOpenAIImageEdits.h"

QOpenAIImageEdits::QOpenAIImageEdits(QObject *parent) : QOpenAI{parent} {

}

QOpenAIImageEdits::QOpenAIImageEdits(const QString &image, const QString &prompt, QObject *parent)
    : QOpenAI{parent}, m_image(image), m_prompt(prompt)
{

}

void QOpenAIImageEdits::sendRequest() {
    if(!isPathExist(m_image)) {
        emit requestError("Provided image file path doesn't exist!");
        return;
    }
    QNetworkRequest request(getUrl(_endPoint));
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QFileInfo imageFileInfo(m_image);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"image\"; filename=\"" + imageFileInfo.fileName() + "\"");
    imagePart.setBody(m_image.toUtf8());
    QFileInfo maskFileInfo(m_mask);
    QHttpPart maskPart;
    maskPart.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");
    maskPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"mask\"; filename=\"" + maskFileInfo.fileName() + "\"");
    maskPart.setBody(m_mask.toUtf8());
    QHttpPart promptPart;
    promptPart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
    promptPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"prompt\"");
    promptPart.setBody(m_prompt.toUtf8());
    QHttpPart nPart;
    nPart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
    nPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"n\"");
    nPart.setBody(QByteArray::number(m_n));
    QHttpPart sizePart;
    sizePart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
    sizePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"size\"");
    sizePart.setBody(m_size.toUtf8());
    QFile *imageFile = new QFile(m_image);
    imageFile->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(imageFile);
    imageFile->setParent(multiPart);
    QFile *maskFile = new QFile(m_mask);
    maskFile->open(QIODevice::ReadOnly);
    maskPart.setBodyDevice(maskFile);
    maskFile->setParent(multiPart);
    multiPart->append(imagePart);
    multiPart->append(maskPart);
    multiPart->append(promptPart);
    multiPart->append(nPart);
    multiPart->append(sizePart);
    QNetworkReply *reply = _networkManager->post(request, multiPart);
    multiPart->setParent(reply);
    connect(reply, &QNetworkReply::finished, this, [this, reply, imageFile, maskFile]() {
        imageFile->close();
        maskFile->close();
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

QString QOpenAIImageEdits::getImage() const {
    return m_image;
}

void QOpenAIImageEdits::setImage(const QString& image) {
    if (m_image != image) {
        m_image = image;
        emit imageChanged();
    }
}

QString QOpenAIImageEdits::getMask() const {
    return m_mask;
}

void QOpenAIImageEdits::setMask(const QString& mask) {
    if (m_mask != mask) {
        m_mask = mask;
        emit maskChanged();
    }
}

QString QOpenAIImageEdits::getPrompt() const {
    return m_prompt;
}

void QOpenAIImageEdits::setPrompt(const QString& prompt) {
    if (m_prompt != prompt) {
        m_prompt = prompt;
        emit promptChanged();
    }
}

int QOpenAIImageEdits::getN() const {
    return m_n;
}

void QOpenAIImageEdits::setN(int n) {
    if (m_n != n) {
        m_n = n;
        emit nChanged();
    }
}

QString QOpenAIImageEdits::getSize() const {
    return m_size;
}

void QOpenAIImageEdits::setSize(const QString& size) {
    if (m_size != size) {
        m_size = size;
        emit sizeChanged();
    }
}

QString QOpenAIImageEdits::getResponseFormat() const {
    return m_responseFormat;
}

void QOpenAIImageEdits::setResponseFormat(const QString& responseFormat) {
    if (m_responseFormat != responseFormat) {
        m_responseFormat = responseFormat;
        emit responseFormatChanged();
    }
}

QString QOpenAIImageEdits::getUser() const {
    return m_user;
}

void QOpenAIImageEdits::setUser(const QString& user) {
    if (m_user != user) {
        m_user = user;
        emit userChanged();
    }
}

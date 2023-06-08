#include "QOpenAIImageVariations.h"

#include <QImageReader>

QOpenAIImageVariations::QOpenAIImageVariations(QObject *parent) : QOpenAI{parent} {
}

void QOpenAIImageVariations::sendRequest(const QString &image) {
    bool isFormatSupported = _imageEditor.checkImageFormatSupported(image);
    if(!isFormatSupported) {
        emit requestError("Image format not supported!");
        return;
    }
    _image = _imageEditor.convertToPng(image);
    QNetworkRequest request(getUrl(_endPoint));
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"image\"; filename=\"selected_image.png\"");
    imagePart.setBody(_image.toUtf8());
    QHttpPart nPart;
    nPart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
    nPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"n\"");
    nPart.setBody(QByteArray::number(_n));
    QHttpPart sizePart;
    sizePart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
    sizePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"size\"");
    sizePart.setBody(_imageSize.toUtf8());
    QFile *file = new QFile(_image);
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
            emit requestError(reply->errorString());
        }
        reply->deleteLater();
    });
}

#include "QOpenAIImageEdits.h"

QOpenAIImageEdits::QOpenAIImageEdits(QObject *parent) : QOpenAI{parent} {

}

void QOpenAIImageEdits::sendRequest() {
    QNetworkRequest request(getUrl(_endPoint));
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QFileInfo imageFileInfo(_image);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"image\"; filename=\"" + imageFileInfo.fileName() + "\"");
    imagePart.setBody(_image.toUtf8());
    QFileInfo maskFileInfo(_mask);
    QHttpPart maskPart;
    maskPart.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");
    maskPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"mask\"; filename=\"" + maskFileInfo.fileName() + "\"");
    maskPart.setBody(_mask.toUtf8());
    QHttpPart promptPart;
    promptPart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
    promptPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"prompt\"");
    promptPart.setBody(_prompt.toUtf8());
    QHttpPart nPart;
    nPart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
    nPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"n\"");
    nPart.setBody(QByteArray::number(_n));
    QHttpPart sizePart;
    sizePart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
    sizePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"size\"");
    sizePart.setBody(_imageSize.toUtf8());
    QFile *imageFile = new QFile(_image);
    imageFile->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(imageFile);
    imageFile->setParent(multiPart);
    QFile *maskFile = new QFile(_mask);
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
            emit requestError(reply->errorString());
        }
        reply->deleteLater();
    });
}

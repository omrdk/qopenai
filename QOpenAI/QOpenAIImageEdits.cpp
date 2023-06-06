#include "QOpenAIImageEdits.h"

QOpenAIImageEdits::QOpenAIImageEdits(QObject *parent)
    : QOpenAI{parent}
{

}

void QOpenAIImageEdits::sendRequest(const QString &prompt) {
    _prompt = prompt;
    QFileInfo inputFile(_image);
    _image = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/" + inputFile.completeBaseName() + "_copy.png";
    _mask = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/" + inputFile.completeBaseName() + "_mask.png";
    assert(QFileInfo::exists(_image) && "Image doesn't exist");
    assert(QFileInfo::exists(_mask) && "Mask doesn't exist");
    QNetworkRequest request(getUrl(_endPoint));
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"image\"; filename=\"copy.png\"");
    imagePart.setBody(_image.toUtf8());
    QHttpPart maskPart;
    maskPart.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");
    maskPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"mask\"; filename=\"mask.png\"");
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
            QByteArray response = reply->readAll();
            QJsonDocument responseJson = QJsonDocument::fromJson(response);
            for(const auto& data: responseJson.object().value("data").toArray()) {
                QString url = data.toObject().value("url").toString();
                emit requestFinished(url);
            }
        } else {
            qDebug() << "Network error: " << reply->error();
            emit requestError(reply->errorString());
        }
        reply->deleteLater();
    });
}

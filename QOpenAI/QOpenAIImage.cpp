#include "QOpenAIImage.h"

QOpenAIImage::QOpenAIImage(QObject *parent)
    : QOpenAI{parent}
{

}


void QOpenAIImage::sendRequest(const QString &prompt) { // prompt is also an abs file path for image edits and variations
    QNetworkRequest request(getUrl(_endPoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QJsonObject body;
    body.insert("prompt", prompt);
    body.insert("n", _n);
    body.insert("size", _imageSize);
    body.insert("response_format", _responseFormat);
    body.insert("user", _user);
    QJsonDocument json(body);
    qDebug() << json; // - !
    QByteArray jsonBytes = json.toJson();
    QNetworkReply *reply = _networkManager->post(request, jsonBytes);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument responseJson = QJsonDocument::fromJson(response);
            for(const auto& data: responseJson.object().value("data").toArray()) {
                QString url = data.toObject().value("url").toString();
                emit requestFinished(url);
            }
        } else {
            emit requestError(reply->errorString());
        }
        reply->deleteLater();
    });
}


//void QOpenAIImage::sendRequest(const QString &prompt) { // prompt is also an abs file path for image edits and variations
//    QNetworkRequest request(getUrl(_endPoint));
//    QByteArray requestBodyBytes;
//    QNetworkReply *reply = nullptr;
//    QHttpMultiPart *multiPart = nullptr;

//    switch (_endPoint) {
//    case QOpenAI::EndPoints::ImageGenerations: {
//        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
//        request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
//        requestBodyBytes = genRequestBody(prompt);
//        reply = _networkManager->post(request, requestBodyBytes);
//        break;
//    }
//    case QOpenAI::EndPoints::ImageVariations: {
//        request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
//        multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
//        QHttpPart imagePart;
//        imagePart.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");
//        imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"image\"; filename=\"image.png\"");
//        imagePart.setBody(_image.toUtf8()); // image is empty dude!
//        QHttpPart nPart;
//        nPart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain"); // text plain for numbeR?
//        nPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"n\"");
//        nPart.setBody(QByteArray::number(_n));
//        QHttpPart sizePart;
//        sizePart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain"); // text plain for numbeR?
//        sizePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"size\"");
//        sizePart.setBody(_imageSize.toUtf8());
//        QFile *file = new QFile(prompt.mid(7));
//        file->open(QIODevice::ReadOnly);
//        imagePart.setBodyDevice(file);
//        file->setParent(multiPart);
//        multiPart->append(imagePart);
//        multiPart->append(nPart);
//        multiPart->append(sizePart);
//        reply = _networkManager->post(request, multiPart);
//        multiPart->setParent(reply);
//        break;
//    }
//    case QOpenAI::EndPoints::ImageEdits: {
//        request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
//        multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
//        QHttpPart imagePart;
//        imagePart.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");
//        imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"image\"; filename=\"image.png\"");
//        imagePart.setBody(_image.toUtf8());
//        QHttpPart maskPart;
//        maskPart.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");
//        maskPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"mask\"; filename=\"image_bgremoved.png\"");
//        maskPart.setBody(_mask.toUtf8());
//        QHttpPart promptPart;
//        promptPart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
//        promptPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"prompt\"");
//        promptPart.setBody(_prompt.toUtf8());
//        QHttpPart nPart;
//        nPart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain"); // text plain for numbeR?
//        nPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"n\"");
//        nPart.setBody(QByteArray::number(_n));
//        QHttpPart sizePart;
//        sizePart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain"); // text plain for numbeR?
//        sizePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"size\"");
//        sizePart.setBody(_imageSize.toUtf8());

//        qDebug() << "File 1 ->" << prompt.mid(7);
//        QFile *file = new QFile(prompt.mid(7));
//        file->open(QIODevice::ReadOnly);
//        imagePart.setBodyDevice(file);
//        file->setParent(multiPart);
//        multiPart->append(imagePart);

//        qDebug() << "File 2 ->" << prompt.mid(7).replace("image", "image_bgremoved");
//        QFile *file2 = new QFile(prompt.mid(7).replace("image", "image_bgremoved"));
//        file2->open(QIODevice::ReadOnly);
//        maskPart.setBodyDevice(file2);
//        file2->setParent(multiPart);
//        multiPart->append(maskPart);

//        multiPart->append(promptPart);
//        multiPart->append(nPart);
//        multiPart->append(sizePart);

//        reply = _networkManager->post(request, multiPart);
//        multiPart->setParent(reply);
//        break;
//    }
//    default:
//        break;
//    }

//    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
//        if (reply->error() == QNetworkReply::NoError) {
//            QByteArray response = reply->readAll();
//            QJsonDocument responseJson = QJsonDocument::fromJson(response);
//            for(const auto& data: responseJson.object().value("data").toArray()) {
//                QString url = data.toObject().value("url").toString();
//                emit requestFinished(url);
//            }
//        } else {
//            emit requestError(reply->errorString());
//        }
//        reply->deleteLater();
//    });
//}

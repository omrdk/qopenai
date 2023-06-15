#include "QOpenAIAudio.h"

QOpenAIAudio::QOpenAIAudio(QObject *parent) : QOpenAI{parent} {

}

void QOpenAIAudio::sendRequest() {
    QNetworkRequest request(getUrl(_endPoint));
    request.setRawHeader("Authorization", ("Bearer " + OPENAI_API_KEY).toUtf8());
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart modelPart;
    modelPart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
    modelPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"model\"");
    modelPart.setBody(_model.toUtf8());
    QFileInfo audioFileInfo(_file);
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, "audio/wav");
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"file\"; filename=\"" + audioFileInfo.fileName() + "\"");
    QUrl fileUrl(_file);
    if(fileUrl.isLocalFile()) {
        _file = fileUrl.toLocalFile();
    }
    QFile *file = new QFile(_file);
    file->open(QIODevice::ReadOnly);
    filePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(filePart);
    multiPart->append(modelPart);
    QNetworkReply *reply = _networkManager->post(request, multiPart);
    multiPart->setParent(reply);
    connect(reply, &QNetworkReply::finished, this, [this, file, reply]() {
        file->close();
        qDebug() << reply->error();
        if (reply->error() == QNetworkReply::NoError) {
            QJsonObject response = QJsonDocument::fromJson(reply->readAll()).object();
            emit requestFinished(response);
        } else {
            emit requestError(reply->errorString());
        }
        reply->deleteLater();
    });
}

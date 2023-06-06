#include "QOpenAI.h"

QOpenAI::QOpenAI(QObject *parent) : _networkManager(new QNetworkAccessManager(this)), _messageModel(new QOpenAIMessageModel(this)) {
    ;
}

QString QOpenAI::getUrl(EndPoints endPoint) {
    QString url = "https://api.openai.com";
    switch (endPoint) {
    case EndPoints::Completions:
        return url + "/v1/completions";
    case EndPoints::ChatCompletions:
        return url + "/v1/chat/completions";
    case EndPoints::Edits:
        return url + "/v1/edits";
    case EndPoints::Transcriptions:
        return url + "/v1/audio/transcriptions";
    case EndPoints::Translations:
        return url + "/v1/audio/translations";
    case EndPoints::ImageGenerations:
        return url + "/v1/images/generations";
    case EndPoints::ImageEdits:
        return url + "/v1/images/edits";
    case EndPoints::ImageVariations:
        return url + "/v1/images/variations";
    }
}

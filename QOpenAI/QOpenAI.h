#ifndef QOPENAI_H
#define QOPENAI_H
#pragma once

#include <QObject>
#include <QtQml>
#include <QNetworkAccessManager>

#include "QOpenAIMessageModel.h"

#define OPENAI_API_KEY qEnvironmentVariable("OPENAI_API_KEY")

class QOpenAI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QOpenAIMessageModel* messageModel MEMBER _messageModel NOTIFY messageModelChanged)
    Q_PROPERTY(EndPoints endPoint MEMBER _endPoint NOTIFY endPointChanged)
    QML_ELEMENT

public:
    enum class EndPoints {
        Completions,
        ChatCompletions,
        Edits,
        Transcriptions,
        Translations,
        ImageGenerations,
        ImageEdits,
        ImageVariations
    };
    Q_ENUM(EndPoints)

    // enum class RequestErrors {}

    explicit QOpenAI(QObject *parent = nullptr);; // take instance in every derived class not here, because the usage may be wrong (for _networkManager)
    virtual ~QOpenAI() {};
    virtual void sendRequest(const QString& content) = 0;

    QString getUrl(EndPoints endPoint);

protected:
    QNetworkAccessManager* _networkManager = nullptr;
    QOpenAIMessageModel* _messageModel = nullptr;
    EndPoints _endPoint = EndPoints::ChatCompletions;


signals:
    void requestFinished(const QString& content);
    void requestError(const QString& error);
    void messageModelChanged();
    void endPointChanged();
};

#endif // QOPENAI_H

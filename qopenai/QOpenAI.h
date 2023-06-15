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
        ImageGenerations,
        ImageEdits,
        ImageVariations,
        Embeddings,
        Transcriptions,
        Translations,
        Moderations
    };
    Q_ENUM(EndPoints)

    explicit QOpenAI(QObject *parent = nullptr);
    virtual ~QOpenAI() {};
    virtual void sendRequest() = 0;

    QString getUrl(EndPoints endPoint);

protected:
    QNetworkAccessManager* _networkManager = nullptr;
    QOpenAIMessageModel* _messageModel = nullptr;
    EndPoints _endPoint = EndPoints::ChatCompletions;

signals:
    void requestFinished(const QJsonObject& response);
    void requestError(const QString& error);
    void messageModelChanged();
    void endPointChanged();
};

#endif // QOPENAI_H

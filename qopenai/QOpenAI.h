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
    Q_PROPERTY(EndPoints endPoint READ getEndPoint WRITE setEndPoint NOTIFY endPointChanged)
    QML_ELEMENT

public:
    enum class EndPoints {
        Completions,
        ChatCompletions,
        Edits,
        ImageGenerations,
        ImageEdits,
        ImageVariations,
        Transcriptions,
        Translations,
        Embeddings,
        Moderations,
        Undefined
    };
    Q_ENUM(EndPoints)

    explicit QOpenAI(QObject *parent = nullptr);
    virtual ~QOpenAI() {};
    virtual void sendRequest() = 0;

    QOpenAIMessageModel* getMessageModel() const;

    EndPoints getEndPoint() const;
    void setEndPoint(EndPoints endPoint);

    QString getUrl(EndPoints endPoint);
    bool isPathExist(const QString& path);

protected:
    QNetworkAccessManager* _networkManager = nullptr;
    QOpenAIMessageModel* _messageModel = nullptr;
    EndPoints _endPoint = EndPoints::Undefined;

signals:
    void requestFinished(const QJsonObject& response);
    void requestError(const QString& error);
    void messageModelChanged();
    void endPointChanged();
};

#endif // QOPENAI_H

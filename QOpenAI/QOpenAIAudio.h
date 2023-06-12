#ifndef QOPENAIAUDIO_H
#define QOPENAIAUDIO_H
#pragma once

#include "QOpenAI.h"

class QOpenAIAudio : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString file MEMBER _file NOTIFY fileChanged);
    Q_PROPERTY(QString model MEMBER _model NOTIFY modelChanged);
    Q_PROPERTY(QString prompt MEMBER _prompt NOTIFY promptChanged);
    Q_PROPERTY(QString responseFormat MEMBER _responseFormat NOTIFY responseFormatChanged);
    Q_PROPERTY(float temperature MEMBER _temperature NOTIFY temperatureChanged);
    QML_ELEMENT

public:
    explicit QOpenAIAudio(QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest() override;

private:
    QString _file = "";
    QString _model = "";
    QString _prompt = "";
    QString _responseFormat = "";
    float _temperature = 1.0;

signals:
    void fileChanged();
    void modelChanged();
    void promptChanged();
    void responseFormatChanged();
    void temperatureChanged();
    void languageChanged();
    void audioRecorderChanged();
};

#endif // QOPENAIAUDIO_H

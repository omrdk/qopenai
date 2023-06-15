#ifndef QOPENAIAUDIO_H
#define QOPENAIAUDIO_H
#pragma once

#include "QOpenAI.h"

class QOpenAIAudio : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString file READ getFile WRITE setFile NOTIFY fileChanged)
    Q_PROPERTY(QString model READ getModel WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QString prompt READ getPrompt WRITE setPrompt NOTIFY promptChanged)
    Q_PROPERTY(QString responseFormat READ getResponseFormat WRITE setResponseFormat NOTIFY responseFormatChanged)
    Q_PROPERTY(float temperature READ getTemperature WRITE setTemperature NOTIFY temperatureChanged)
    QML_ELEMENT

public:
    explicit QOpenAIAudio(QObject *parent = nullptr);
    explicit QOpenAIAudio(const QString& model, const QString& file, QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest() override;

    QString getFile() const;
    void setFile(const QString& file);

    QString getModel() const;
    void setModel(const QString& model);

    QString getPrompt() const;
    void setPrompt(const QString& prompt);

    QString getResponseFormat() const;
    void setResponseFormat(const QString& responseFormat);

    float getTemperature() const;
    void setTemperature(float temperature);

private:
    QString m_file = "";
    QString m_model = "whisper-1";
    QString m_prompt = "";
    QString m_responseFormat = "json";
    float m_temperature = 1.0;

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

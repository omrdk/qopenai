#ifndef QOPENAICOMPLETIONS_H
#define QOPENAICOMPLETIONS_H
#pragma once

#include "QOpenAI.h"

class QOpenAICompletions : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString model READ getModel WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QString prompt READ getPrompt WRITE setPrompt NOTIFY promptChanged)
    Q_PROPERTY(QString suffix READ getSuffix WRITE setSuffix NOTIFY suffixChanged)
    Q_PROPERTY(int maxTokens READ getMaxTokens WRITE setMaxTokens NOTIFY maxTokensChanged)
    Q_PROPERTY(float temperature READ getTemperature WRITE setTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(float topP READ getTopP WRITE setTopP NOTIFY topPChanged)
    Q_PROPERTY(int n READ getN WRITE setN NOTIFY nChanged)
    Q_PROPERTY(bool stream READ getStream WRITE setStream NOTIFY streamChanged)
    Q_PROPERTY(int logProbs READ getLogProbs WRITE setLogProbs NOTIFY logProbsChanged)
    Q_PROPERTY(bool echo READ getEcho WRITE setEcho NOTIFY echoChanged)
    Q_PROPERTY(QString stop READ getStop WRITE setStop NOTIFY stopChanged)
    Q_PROPERTY(float presencePenalty READ getPresencePenalty WRITE setPresencePenalty NOTIFY presencePenaltyChanged)
    Q_PROPERTY(float frequencyPenalty READ getFrequencyPenalty WRITE setFrequencyPenalty NOTIFY frequencyPenaltyChanged)
    Q_PROPERTY(int bestOf READ getBestOf WRITE setBestOf NOTIFY bestOfChanged)
    Q_PROPERTY(QVariantMap logitBias READ getLogitBias WRITE setLogitBias NOTIFY logitBiasChanged)
    Q_PROPERTY(QString user READ getUser WRITE setUser NOTIFY userChanged)
    QML_ELEMENT

public:
    explicit QOpenAICompletions(QObject *parent = nullptr);
    explicit QOpenAICompletions(const QString& model, QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest() override;

    QString getModel() const;
    void setModel(const QString& model);

    QString getPrompt() const;
    void setPrompt(const QString& prompt);

    QString getSuffix() const;
    void setSuffix(const QString& suffix);

    int getMaxTokens() const;
    void setMaxTokens(int maxTokens);

    float getTemperature() const;
    void setTemperature(float temperature);

    float getTopP() const;
    void setTopP(float topP);

    int getN() const;
    void setN(int n);

    bool getStream() const;
    void setStream(bool stream);

    int getLogProbs() const;
    void setLogProbs(int logProbs);

    bool getEcho() const;
    void setEcho(bool echo);

    QString getStop() const;
    void setStop(const QString& stop);

    float getPresencePenalty() const;
    void setPresencePenalty(float presencePenalty);

    float getFrequencyPenalty() const;
    void setFrequencyPenalty(float frequencyPenalty);

    int getBestOf() const;
    void setBestOf(int bestOf);

    QVariantMap getLogitBias() const;
    void setLogitBias(const QVariantMap& logitBias);

    QString getUser() const;
    void setUser(const QString& user);

private:
    QString m_model = "text-davinci-003";
    QString m_prompt = "";
    QString m_suffix = "";
    int m_maxTokens = 16;
    float m_temperature = 1.0;
    float m_topP = 1.0;
    int m_n = 1;
    bool m_stream = false;
    int m_logProbs = 0;
    bool m_echo = false;
    QString m_stop = "";
    float m_presencePenalty = 0.0;
    float m_frequencyPenalty = 0.0;
    int m_bestOf = 1;
    QVariantMap m_logitBias = {};
    QString m_user = "";

signals:
    void modelChanged();
    void promptChanged();
    void suffixChanged();
    void maxTokensChanged();
    void temperatureChanged();
    void topPChanged();
    void nChanged();
    void streamChanged();
    void logProbsChanged();
    void echoChanged();
    void stopChanged();
    void presencePenaltyChanged();
    void frequencyPenaltyChanged();
    void bestOfChanged();
    void logitBiasChanged();
    void userChanged();
};

#endif // QOPENAICOMPLETIONS_H

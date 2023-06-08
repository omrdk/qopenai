#ifndef QOPENAICOMPLETIONS_H
#define QOPENAICOMPLETIONS_H
#pragma once

#include "QOpenAI.h"

class QOpenAICompletions : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString model MEMBER _model NOTIFY modelChanged);
    Q_PROPERTY(QString prompt MEMBER _prompt NOTIFY promptChanged);
    Q_PROPERTY(QString suffix MEMBER _suffix NOTIFY suffixChanged);
    Q_PROPERTY(int maxTokens MEMBER _maxTokens NOTIFY maxTokensChanged);
    Q_PROPERTY(float temperature MEMBER _temperature NOTIFY temperatureChanged);
    Q_PROPERTY(float topP MEMBER _topP NOTIFY topPChanged);
    Q_PROPERTY(int n MEMBER _n NOTIFY nChanged);
    Q_PROPERTY(bool stream MEMBER _stream NOTIFY streamChanged);
    Q_PROPERTY(int logProbs MEMBER _logProbs NOTIFY logProbsChanged);
    Q_PROPERTY(bool echo MEMBER _echo NOTIFY echoChanged);
    Q_PROPERTY(QString stop MEMBER _stop NOTIFY stopChanged);
    Q_PROPERTY(float presencePenalty MEMBER _presencePenalty NOTIFY presencePenaltyChanged);
    Q_PROPERTY(float frequencyPenalty MEMBER _frequencyPenalty NOTIFY frequencyPenaltyChanged);
    Q_PROPERTY(int bestOf MEMBER _bestOf NOTIFY bestOfChanged);
    Q_PROPERTY(QVariantMap logitBias MEMBER _logitBias NOTIFY logitBiasChanged);
    Q_PROPERTY(QString user MEMBER _user NOTIFY userChanged);
    QML_ELEMENT

public:
    explicit QOpenAICompletions(QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest(const QString& prompt) override;;

private:
    QString _model = "";
    QString _prompt = "";
    QString _suffix = "";
    int _maxTokens = 0;
    float _temperature = 0.0;
    float _topP = 0.0;
    int _n = 1;
    bool _stream = false;
    int _logProbs = 0;
    bool _echo = false;
    QString _stop = "";
    float _presencePenalty = 0.0;
    float _frequencyPenalty = 0.0;
    int _bestOf = 1;
    QVariantMap _logitBias = {};
    QString _user = "";

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

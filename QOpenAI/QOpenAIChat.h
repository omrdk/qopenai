#ifndef QOPENAICHAT_H
#define QOPENAICHAT_H

#include "QOpenAI.h"

class QOpenAIChat : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString model MEMBER _model NOTIFY modelChanged);
    Q_PROPERTY(float temperature MEMBER _temperature NOTIFY temperatureChanged);
    Q_PROPERTY(float topP MEMBER _topP NOTIFY topPChanged);
    Q_PROPERTY(int n MEMBER _n NOTIFY nChanged);
    Q_PROPERTY(bool stream MEMBER _stream NOTIFY streamChanged);
    Q_PROPERTY(QString stop MEMBER _stop NOTIFY stopChanged);
    Q_PROPERTY(int maxTokens MEMBER _maxTokens NOTIFY maxTokensChanged);
    Q_PROPERTY(float presencePenalty MEMBER _presencePenalty NOTIFY presencePenaltyChanged);
    Q_PROPERTY(float frequencyPenalty MEMBER _frequencyPenalty NOTIFY frequencyPenaltyChanged);
    Q_PROPERTY(QVariantMap logitBias MEMBER _logitBias NOTIFY logitBiasChanged);
    Q_PROPERTY(QString user MEMBER _user NOTIFY userChanged);
    Q_PROPERTY(QString systemMessage MEMBER _systemMessage NOTIFY systemMessageChanged);
    QML_ELEMENT

public:
    explicit QOpenAIChat(QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest(const QString& content) override;

private:
    QString _model = "";
    float _temperature = 1.0;
    float _topP = 1.0;
    int _n = 1;
    bool _stream = false;
    QString _stop = "";
    int _maxTokens = 2048;
    float _presencePenalty = 0.0;
    float _frequencyPenalty = 0.0;
    QVariantMap _logitBias = {};
    QString _user = "";
    QString _systemMessage = "";

signals:
    void modelChanged();
    void temperatureChanged();
    void topPChanged();
    void nChanged();
    void streamChanged();
    void stopChanged();
    void maxTokensChanged();
    void presencePenaltyChanged();
    void frequencyPenaltyChanged();
    void logitBiasChanged();
    void userChanged();
    void systemMessageChanged();
};

#endif // QOPENAICHAT_H

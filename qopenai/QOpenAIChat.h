#ifndef QOPENAICHAT_H
#define QOPENAICHAT_H

#include "QOpenAI.h"

class QOpenAIChat : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString model READ getModel WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(float temperature READ getTemperature WRITE setTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(float topP READ getTopP WRITE setTopP NOTIFY topPChanged)
    Q_PROPERTY(int n READ getN WRITE setN NOTIFY nChanged)
    Q_PROPERTY(bool stream READ getStream WRITE setStream NOTIFY streamChanged)
    Q_PROPERTY(QString stop READ getStop WRITE setStop NOTIFY stopChanged)
    Q_PROPERTY(int maxTokens READ getMaxTokens WRITE setMaxTokens NOTIFY maxTokensChanged)
    Q_PROPERTY(float presencePenalty READ getPresencePenalty WRITE setPresencePenalty NOTIFY presencePenaltyChanged)
    Q_PROPERTY(float frequencyPenalty READ getFrequencyPenalty WRITE setFrequencyPenalty NOTIFY frequencyPenaltyChanged)
    Q_PROPERTY(QVariantMap logitBias READ getLogitBias WRITE setLogitBias NOTIFY logitBiasChanged)
    Q_PROPERTY(QString user READ getUser WRITE setUser NOTIFY userChanged)
    Q_PROPERTY(QString systemMessage READ getSystemMessage WRITE setSystemMessage NOTIFY systemMessageChanged)
    QML_ELEMENT

public:
    explicit QOpenAIChat(QObject *parent = nullptr);
    explicit QOpenAIChat(const QString& model, QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest() override;

    QString getModel() const;
    void setModel(const QString& model);

    float getTemperature() const;
    void setTemperature(float temperature);

    float getTopP() const;
    void setTopP(float topP);

    int getN() const;
    void setN(int n);

    bool getStream() const;
    void setStream(bool stream);

    QString getStop() const;
    void setStop(const QString& stop);

    int getMaxTokens() const;
    void setMaxTokens(int maxTokens);

    float getPresencePenalty() const;
    void setPresencePenalty(float presencePenalty);

    float getFrequencyPenalty() const;
    void setFrequencyPenalty(float frequencyPenalty);

    QVariantMap getLogitBias() const;
    void setLogitBias(const QVariantMap& logitBias);

    QString getUser() const;
    void setUser(const QString& user);

    QString getSystemMessage() const;
    void setSystemMessage(const QString& systemMessage);

private:
    QString m_model = "";
    float m_temperature = 1.0;
    float m_topP = 1.0;
    int m_n = 1;
    bool m_stream = false;
    QString m_stop = "";
    int m_maxTokens = 2048;
    float m_presencePenalty = 0.0;
    float m_frequencyPenalty = 0.0;
    QVariantMap m_logitBias = {};
    QString m_user = "";
    QString m_systemMessage = "";

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
    void userMessageChanged();
};

#endif // QOPENAICHAT_H

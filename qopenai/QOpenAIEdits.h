#ifndef QOPENAIEDIT_H
#define QOPENAIEDIT_H

#include "QOpenAI.h"

class QOpenAIEdits : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString model READ getModel WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(QString input READ getInput WRITE setInput NOTIFY inputChanged)
    Q_PROPERTY(QString instruction READ getInstruction WRITE setInstruction NOTIFY instructionChanged)
    Q_PROPERTY(int n READ getN WRITE setN NOTIFY nChanged)
    Q_PROPERTY(float temperature READ getTemperature WRITE setTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(float topP READ getTopP WRITE setTopP NOTIFY topPChanged)
    QML_ELEMENT

public:
    explicit QOpenAIEdits(QObject *parent = nullptr);
    explicit QOpenAIEdits(const QString& model, const QString& instruction, QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest() override;

    QString getModel() const;
    void setModel(const QString& model);

    QString getInput() const;
    void setInput(const QString& input);

    QString getInstruction() const;
    void setInstruction(const QString& instruction);

    int getN() const;
    void setN(int n);

    float getTemperature() const;
    void setTemperature(float temperature);

    float getTopP() const;
    void setTopP(float topP);

private:
    QString m_model = "";
    QString m_input = "";
    QString m_instruction = "";
    int m_n = 1;
    float m_temperature = 1.0;
    float m_topP = 1.0;

signals:
    void modelChanged();
    void inputChanged();
    void instructionChanged();
    void nChanged();
    void temperatureChanged();
    void topPChanged();
};

#endif // QOPENAIEDIT_H

#ifndef QOPENAIEDIT_H
#define QOPENAIEDIT_H

#include "QOpenAI.h"

class QOpenAIEdits : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString model MEMBER _model NOTIFY modelChanged);
    Q_PROPERTY(QString input MEMBER _input NOTIFY inputChanged);
    Q_PROPERTY(QString instruction MEMBER _instruction NOTIFY instructionChanged);
    Q_PROPERTY(int n MEMBER _n NOTIFY nChanged);
    Q_PROPERTY(float temperature MEMBER _temperature NOTIFY temperatureChanged);
    Q_PROPERTY(float topP MEMBER _topP NOTIFY topPChanged);
    QML_ELEMENT

public:
    explicit QOpenAIEdits(QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest() override;

private:
    QString _model = "";
    QString _input = "";
    QString _instruction = "";
    int _n = 1;
    float _temperature = 1.0;
    float _topP = 1.0;

signals:
    void modelChanged();
    void inputChanged();
    void instructionChanged();
    void nChanged();
    void temperatureChanged();
    void topPChanged();

};

#endif // QOPENAIEDIT_H

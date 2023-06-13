#ifndef QOPENAIMODERATIONS_H
#define QOPENAIMODERATIONS_H

#include "QOpenAI.h"

class QOpenAIModerations : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString input MEMBER _input NOTIFY inputChanged);
    Q_PROPERTY(QString model MEMBER _model NOTIFY modelChanged);
    QML_ELEMENT
public:
    explicit QOpenAIModerations(QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest() override;

private:
    QString _input = "";
    QString _model = "";

signals:
    void inputChanged();
    void modelChanged();

};

#endif // QOPENAIMODERATIONS_H

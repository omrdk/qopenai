#ifndef QOPENAIEMBEDDINGS_H
#define QOPENAIEMBEDDINGS_H

#include "QOpenAI.h"

class QOpenAIEmbeddings : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString model MEMBER _model NOTIFY modelChanged);
    Q_PROPERTY(QString input MEMBER _input NOTIFY inputChanged);
    Q_PROPERTY(QString user MEMBER _user NOTIFY userChanged);
    QML_ELEMENT

public:
    explicit QOpenAIEmbeddings(QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest() override;

private:
    QString _model = "";
    QString _input = "";
    QString _user = "";

signals:
    void modelChanged();
    void inputChanged();
    void userChanged();
};

#endif // QOPENAIEMBEDDINGS_H

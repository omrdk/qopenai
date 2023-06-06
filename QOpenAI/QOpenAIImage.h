#ifndef QOPENAIIMAGE_H
#define QOPENAIIMAGE_H
#pragma once

#include "QOpenAI.h"

class QOpenAIImage : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString prompt MEMBER _prompt NOTIFY promptChanged);
    Q_PROPERTY(QString image MEMBER _image NOTIFY imageChanged);
    Q_PROPERTY(QString mask MEMBER _mask NOTIFY maskChanged);
    Q_PROPERTY(int n MEMBER _n NOTIFY nChanged);
    Q_PROPERTY(QString imageSize MEMBER _imageSize NOTIFY imageSizeChanged);
    Q_PROPERTY(QString responseFormat MEMBER _responseFormat NOTIFY responseFormatChanged);
    Q_PROPERTY(QString user MEMBER _user NOTIFY userChanged);
    QML_ELEMENT

public:
    explicit QOpenAIImage(QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest(const QString& prompt) override;

private:
    QString _prompt = "";
    QString _image = "";
    QString _mask = "";
    int _n = 1;
    QString _imageSize = "";
    QString _responseFormat = "";
    QString _user = "";

signals:
    void promptChanged();
    void imageChanged();
    void maskChanged();
    void nChanged();
    void imageSizeChanged();
    void responseFormatChanged();
    void userChanged();
};

#endif // QOPENAIIMAGE_H

#ifndef QOPENAIIMAGEEDITS_H
#define QOPENAIIMAGEEDITS_H

#include "QOpenAI.h"

class QOpenAIImageEdits : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString image MEMBER _image NOTIFY imageChanged);
    Q_PROPERTY(QString mask MEMBER _mask NOTIFY maskChanged);
    Q_PROPERTY(QString prompt MEMBER _prompt NOTIFY promptChanged);
    Q_PROPERTY(int n MEMBER _n NOTIFY nChanged);
    Q_PROPERTY(QString imageSize MEMBER _imageSize NOTIFY imageSizeChanged);
    Q_PROPERTY(QString responseFormat MEMBER _responseFormat NOTIFY responseFormatChanged);
    Q_PROPERTY(QString user MEMBER _user NOTIFY userChanged);
    QML_ELEMENT
public:
    explicit QOpenAIImageEdits(QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest() override;

private:
    QString _image = "";
    QString _mask = "";
    QString _prompt = "";
    int _n = 1;
    QString _imageSize = "";
    QString _responseFormat = "";
    QString _user = "";

signals:
    void imageChanged();
    void maskChanged();
    void promptChanged();
    void nChanged();
    void imageSizeChanged();
    void responseFormatChanged();
    void userChanged();

};

#endif // QOPENAIIMAGEEDITS_H

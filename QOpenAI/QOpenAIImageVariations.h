#ifndef QOPENAIIMAGEVARIATIONS_H
#define QOPENAIIMAGEVARIATIONS_H

#include "QOpenAI.h"
#include "ImageEditor.h"

class QOpenAIImageVariations : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString image MEMBER _image NOTIFY imageChanged);
    Q_PROPERTY(int n MEMBER _n NOTIFY nChanged);
    Q_PROPERTY(QString imageSize MEMBER _imageSize NOTIFY imageSizeChanged);
    Q_PROPERTY(QString responseFormat MEMBER _responseFormat NOTIFY responseFormatChanged);
    Q_PROPERTY(QString user MEMBER _user NOTIFY userChanged);
    QML_ELEMENT

public:
    explicit QOpenAIImageVariations(QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest(const QString& image) override;;

private:
    QString _image = "";
    int _n = 1;
    QString _imageSize = "";
    QString _responseFormat = "";
    QString _user = "";

    ImageEditor _imageEditor;

signals:
    void imageChanged();
    void nChanged();
    void imageSizeChanged();
    void responseFormatChanged();
    void userChanged();
};

#endif // QOPENAIIMAGEVARIATIONS_H

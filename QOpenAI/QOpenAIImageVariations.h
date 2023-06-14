#ifndef QOPENAIIMAGEVARIATIONS_H
#define QOPENAIIMAGEVARIATIONS_H

#include "QOpenAI.h"

class QOpenAIImageVariations : public QOpenAI
{
    Q_OBJECT
    Q_PROPERTY(QString image READ getImage WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(int n READ getN WRITE setN NOTIFY nChanged)
    Q_PROPERTY(QString size READ getSize WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QString responseFormat READ getResponseFormat WRITE setResponseFormat NOTIFY responseFormatChanged)
    Q_PROPERTY(QString user READ getUser WRITE setUser NOTIFY userChanged)
    QML_ELEMENT

public:
    explicit QOpenAIImageVariations(QObject *parent = nullptr);
    explicit QOpenAIImageVariations(const QString &image, QObject *parent = nullptr);

    Q_INVOKABLE void sendRequest() override;

    QString getImage() const;
    void setImage(const QString& image);

    int getN() const;
    void setN(int n);

    QString getSize() const;
    void setSize(const QString& size);

    QString getResponseFormat() const;
    void setResponseFormat(const QString& responseFormat);

    QString getUser() const;
    void setUser(const QString& user);

private:
    QString m_image = "";
    int m_n = 1;
    QString m_size = "1024x1024";
    QString m_responseFormat = "url";
    QString m_user = "";

signals:
    void imageChanged();
    void nChanged();
    void sizeChanged();
    void responseFormatChanged();
    void userChanged();

};

#endif // QOPENAIIMAGEVARIATIONS_H
